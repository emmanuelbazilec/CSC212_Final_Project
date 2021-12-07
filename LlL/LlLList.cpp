#include "LlLList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

// Default constructor
LlLList::LlLList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    
    this->ROWS = 0;
    this->COLS = 0;
}

// Constructor for matrix operations that sets ROWS and COLS
LlLList::LlLList(int ROWS, int COLS){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    
    this->ROWS = ROWS;
    this->COLS = COLS;
}

// Converts and returns and int value of a CLA
int CLAtoInt(char* argv){
    int val;
    std::istringstream inVal(argv);
    inVal >> val;
    return val;
}

// Gets filename string from CLA and preppends a directory depending on whether
// the file is being read or written to
std::string getFname(char* argv, bool IO){
    std::string fname = {};
    if (IO == true){
        fname += "./SpMfile/";
    }
    else if (IO == false){
        fname += "./CmpSpMfile/LlL";
    }
    fname += argv;
    return fname;
}

// Constructor that automatically constructs a list from CLAs
LlLList::LlLList(char* fname, char* ROWS, char* COLS){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    this->ROWS = CLAtoInt(ROWS);
    this->COLS = CLAtoInt(COLS);
    this->fname = getFname(fname, true);
    // read from file
    std::ifstream readfile;
    readfile.open(getFname(fname, true));
    int temp;
    for (int i = 0 ; i < CLAtoInt(ROWS) ; i++){
        LlLColList* temp2 = new LlLColList(i);
        for (int j = 0 ; j < CLAtoInt(COLS) ; j++){
            readfile >> temp;
            if (temp != 0){
                temp2->push_back(j, temp);
            }
        }
        if (temp2->listsize != 0){
            push_back(temp2);
        }
        else{
            delete temp2;
        }
    }
    readfile.close();
}

// Returns the size of the list
int LlLList::get_size(){
    LlLColList* temp = head;
    int counter = 0;
    while (temp != nullptr){
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            counter += 1;
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    return counter;
}

// Constructor to create an object from a compressed file
LlLList::LlLList(char* inname){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    this->fname = inname;
    // read from file
    std::string fname = "./CmpSpMfile/";
    fname += inname;
    std::ifstream readfile;
    readfile.open(fname);

    // Create a temp file to avoid comments
    std::string line;
    std::string outname = "./CmpSpMfile/tempfile.txt";
    std::ofstream outfile(outname);
    while (getline(readfile, line)){
        if (line[0] != '/' && line.size() != 0){
            outfile << line << "\n";
        }
    }
    readfile.close();
    outfile.close();

    // Build the list
    int size;
    int temp;
    int curRow;
    int temp2;
    LlLColList* coltemp;
    readfile.open(outname);
    readfile >> temp;
    this->ROWS = temp;
    readfile >> temp;
    this->COLS = temp;
    readfile >> size;
    for (int i = 0 ; i <= size ; i++){
        readfile >> temp;
        if (i == 0){
            curRow = temp;
            coltemp = new LlLColList(temp);
            readfile >> temp;
            readfile >> temp2;
            coltemp->push_back(temp, temp2);
            continue;
        }
        if (temp != curRow){
            push_back(coltemp);
            curRow = temp;
            coltemp = new LlLColList(temp);
            readfile >> temp;
            readfile >> temp2;
            coltemp->push_back(temp, temp2);
            continue;
        }
        else{
            readfile >> temp;
            readfile >> temp2;
            coltemp->push_back(temp, temp2);
        }

    }
    readfile.close();
    std::remove("./CmpSpMfile/tempfile.txt");
}

// Destructor
LlLList::~LlLList(){

}

// Appends a ColList object to the tail of the list
void LlLList::push_back(LlLColList* a_col){
    LlLColList* temp = a_col;
    if (tail != nullptr){
        this->tail->next = temp;
        temp->prev = tail;
    }
    this->tail = temp;
    if (head == nullptr){
        this->head = tail;
    }
    this->listsize += 1;
}

// Prepends a column list to front of list
void LlLList::push_front(LlLColList* a_col){
    LlLColList* temp = a_col;
    if (head != nullptr){
        this->head->prev = temp;
        temp->next = head;
    }
    this->head = temp;
    if (tail == nullptr){
        this->tail = head;
    }
    this->listsize += 1;
}

// Inserts data into the array at the given row and column
void LlLList::insert(int row, int col, int data){
    if (row >= ROWS || col >= COLS){
        return;
    }
    LlLColList* temp = head;
    while (temp != nullptr){
        if (temp->row >= row)
            break;
        temp = temp->next;
    }
    if (temp == nullptr){
        temp = new LlLColList(row);
        temp->push_back(col, data);
        push_back(temp);
        return;
    }
    else if (temp->row == row){
        temp->insert(col, data);
        if (temp->listsize == 0)
            del(temp);
        return;
    }
    else if (temp == head){
        temp = new LlLColList(row);
        temp->push_back(col, data);
        push_front(temp);
        return;
    }
    LlLColList* newrow = new LlLColList(row);
    newrow->push_back(col, data);
    temp->prev->next = newrow;
    newrow->prev = temp->prev;
    newrow->next = temp;
    temp->prev = newrow;
    this->listsize += 1;
}

// deletes a row in the list
void LlLList::del(LlLColList* a_col){
    if (listsize == 1){
        this->head = nullptr;
        this->tail = nullptr;
        this->listsize = 0;
        delete a_col;
        return;
    }
    else if (a_col == head){
        head = head->next;
        this->listsize -= 1;
        return;
    }
    else if (a_col == tail){
        this->tail = tail->prev;
        this->tail->next = nullptr;
        a_col = nullptr;
        this->listsize -= 1;
        return;
    }
    a_col->prev->next = a_col->next;
    a_col->next->prev = a_col->prev;
    this->listsize -= 1;
}

// Prints data stored in list to console
void LlLList::print_list(){
    LlLColList* temp = head;
    while(temp != nullptr){
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            std::cout << "row: " << temp->row << " col: " << temp2->col << " data: " << temp2->data << "\n";
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}

// Writes data to an output file
void LlLList::write_file(char* ofname){
    std::string outfname = getFname(ofname, false);
    std::fstream writefile;
    writefile.open(outfname, std::ios::out);
    LlLColList* temp = head;
    writefile << "// matrix dimensions ROWS x COLS:\n" << ROWS << " " << COLS << "\n\n";
    writefile << "// listsize:\n" << get_size() << "\n\n"; 
    writefile << "// condensed form:\n// row col data\n";
    while (temp != nullptr){
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            writefile << temp->row << " " << temp2->col << " " << temp2->data << "\n";
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    temp = head;
    writefile << "\n \n// expanded form:\n";
    for (int i = 0 ; i < ROWS ; i++){
        
        if (temp == nullptr){
            for (int j = 0 ; j < COLS ; j++){
                writefile << "0 ";
            }
            writefile << "\n";
            continue;
        }
        LlLDataNode* temp2 = temp->head;
        for (int j = 0 ; j < COLS ; j++){
            if (temp != nullptr && temp2 != nullptr){
                if (temp->row == i && temp2->col == j){
                    writefile << temp2->data << " ";
                    temp2 = temp2->next;
                    continue;
                }
            }
            writefile << "0 ";
        }
        temp = temp->next;
        writefile << "\n";
    }
    writefile.close();
}

// Addition operation

LlLList LlLList::add(LlLList a_list){
    LlLList sum(ROWS, COLS);
    // Check whether or not matrix dimensions allow for addition
    if (ROWS != a_list.ROWS || COLS != a_list.COLS){
        std::cout << "DIMENSION ERROR FOR ADDITIONS" << std::endl;
        return sum;
    }

    // clone list to preserve original data
    LlLColList* temp = head;
    while (temp != nullptr){
        LlLColList* newrow = new LlLColList(temp->row);
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            newrow->push_back(temp2->col, temp2->data);
            temp2 = temp2->next;
        }
        sum.push_back(newrow);
        temp = temp->next;
    }

    // iterate through second list and insert into sum
    temp = a_list.head;
    while (temp != nullptr){
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            sum.insert(temp->row, temp2->col, temp2->data);
            temp2 = temp2->next;
        }
        
        temp = temp->next;
    }

    return sum;
}

// Returns the result of a transposed matrix
LlLList LlLList::transpose(){
    LlLList transList(COLS, ROWS);

    LlLColList* temp = head;

    while (temp != nullptr){
        LlLDataNode* temp2 = temp->head;
        while (temp2 != nullptr){
            transList.insert(temp2->col, temp->row, temp2->data);
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    return transList;
}

// Returns the resulting matrix from the multiplicaion of two matrices
LlLList LlLList::multiply(LlLList a_list){
    LlLList product(ROWS, a_list.COLS);
    if(COLS != a_list.ROWS){
        std::cout << "DIMENSION ERROR FOR MULTIPLICATION" << std::endl;
        return product;
    }

    // Create a transpose list
    LlLList a_trans = a_list.transpose();

    LlLColList* temp = head;
    
    while (temp != nullptr){
        LlLColList* coltemp = new LlLColList(temp->row);
        LlLColList* temp2 = a_trans.head;

        while (temp2 != nullptr){
            LlLDataNode* a_temp = temp->head;
            LlLDataNode* a_temp2 = temp2->head;
            int sum = 0;
            while (a_temp != nullptr && a_temp2 != nullptr){
                if (a_temp->col < a_temp2->col){
                    a_temp = a_temp->next;
                }
                else if (a_temp->col > a_temp2->col){
                    a_temp2 = a_temp2->next;
                }
                else{
                    sum += a_temp->data * a_temp2->data;
                    a_temp = a_temp->next;
                    a_temp2 = a_temp2->next;
                }
            }
            if (sum != 0){
                coltemp->push_back(temp2->row, sum);
            }
            temp2 = temp2->next;
        }
        if (coltemp->listsize != 0){
            product.push_back(coltemp);
        }
        temp = temp->next;
    }
    return product;
}