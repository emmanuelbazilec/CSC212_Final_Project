#include "COOList.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

// Default construcor
COOList::COOList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->ROWS = 0;
    this->COLS = 0;
    this->listsize = 0;
}

// To set rows and cols for operations
COOList::COOList(int ROWS, int COLS){
    this->head = nullptr;
    this->tail = nullptr;
    this->ROWS = ROWS;
    this->COLS = COLS;
    this->listsize = 0;
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
        fname += "./CmpSpMfile/COO";
    }
    fname += argv;
    return fname;
}

// To take in CLAs and construct list 
COOList::COOList(char* fname, char* ROWS, char* COLS){
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
        for (int j = 0 ; j < CLAtoInt(COLS) ; j++){
            readfile >> temp;
            if (temp != 0){
                push_back(i, j, temp);
            }
        }
    }
    readfile.close();
}

// To read from condensed form file
COOList::COOList(char* inname){
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
    int size, temp, temprow, tempcol, tempdata;
    readfile.open(outname);
    readfile >> temp;
    this->ROWS = temp;
    readfile >> temp;
    this->COLS = temp;
    readfile >> size;
    COONode* tempnode;
    for (int i = 0 ; i < size ; i++){
        readfile >> temprow;
        readfile >> tempcol;
        readfile >> tempdata;
        push_back(temprow, tempcol, tempdata);
    }
    readfile.close();
    std::remove("./CmpSpMfile/tempfile.txt");
}

COOList::~COOList(){

}

// Appends a row, column, data tuple to the tail of the list
void COOList::push_back(int row, int col, int data){
    COONode* temp = new COONode(row, col, data);
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

// Prepends a row, column, data tuple to the head of the list
void COOList::push_front(int row, int col, int data){
    COONode* temp = new COONode(row, col, data);
    if (head != nullptr){
        this->head->prev = temp;
        temp->next = tail;
    }
    this->head = temp;
    if (tail == nullptr){
        this->tail == head;
    }
    this->listsize += 1;
}

// Inserts a row, column, data tuple into the list
void COOList::insert(int row, int col, int data){
    COONode* temp = head;
    while (temp != nullptr){
        if (temp->row > row){
            break;
        }
        if (temp->row >= row && temp->col >= col){
            break;
        }
        temp = temp->next;
    }
    if (temp == nullptr){
        push_back(row, col, data);
        return;
    }
    else if (temp->col == col && temp->row == row){
        if (temp->data + data != 0){
            temp->data += data;
        }
        else{
            del(temp);
        }
        return;
    }
    else if (temp == head){
        push_front(row, col, data);
        return;
    }
    COONode* newnode = new COONode(row, col, data);
    temp->prev->next = newnode;
    newnode->prev = temp->prev;
    newnode->next = temp;
    temp->prev = newnode;
    this->listsize += 1;
}


// Deletes a node in the list
void COOList::del(COONode* a_node){
    COONode* temp = head;
    while (&temp->data != &a_node->data){
        temp = temp->next;
    }
    if (temp == head){
        this->head = head->next;
        this->listsize -= 1; 
        return;
    }
    temp->prev->next = temp->next;
    if (temp == tail){
        this->listsize -= 1;
        this->tail = tail->prev;
        return;
    }
    temp->next->prev = temp->prev;
    this->listsize -= 1;
}

// Prints the lit to console
void COOList::print_list(){
    COONode* temp = head;
    while (temp != nullptr){
        std::cout << "row: " << temp->row << " col: " << temp->col << " data: " << temp->data << "\n";
        temp = temp->next;
    } 
}

// Writes the data stored in the list to a file with filename "COO + ofname" in the CmpSpMfile directory
void COOList::writeFile(char* ofname){
    std::string outfname = getFname(ofname, false);
    std::fstream writefile;
    writefile.open(outfname, std::ios::out);
    COONode* temp = head;
    writefile << "// matrix dimensions ROWS x COLS:\n" << ROWS << " " << COLS << "\n\n";
    writefile << "// listsize:\n" << get_size() << "\n\n";  
    writefile << "// condensed form:\n// row col data\n";
    while (temp != nullptr){
        writefile << temp->row << " " << temp->col << " " << temp->data << "\n";
        temp = temp->next;
    }
    temp = head;
    writefile << "\n \n// expanded form:\n";
    for (int i = 0 ; i < ROWS ; i++){
        for (int j = 0 ; j < COLS ; j++){
            if (temp != nullptr){
                if (temp->row == i && temp->col == j){
                    writefile << temp->data << " ";
                    temp = temp->next;
                    continue;
                }
            }
            writefile << "0 ";
        }
        writefile << "\n";
    }
    writefile.close();
}

// Finds the size of the list
int COOList::get_size(){
    COONode* temp = head;
    int counter = 0;
    while (temp != nullptr){
        counter += 1;
        temp = temp->next;
    }
    return counter;
}

// Returns a list containing the sum of two lists
COOList COOList::add(COOList a_list){
    COOList sumList(ROWS, COLS);
    if (ROWS != a_list.ROWS || COLS != a_list.COLS){
        std::cout << "DIMENSION ERROR FOR ADDITION" << std::endl;
        return sumList;
    }

    // Create a copy of this list to preserve data
    COONode* temp = head;
    while (temp != nullptr){
        sumList.push_back(temp->row, temp->col, temp->data);
        temp = temp->next;
    } 

    // iterate through second list and insert into sum
    temp = a_list.head;
    while (temp != nullptr){
        sumList.insert(temp->row, temp->col, temp->data);
        temp = temp->next;
    }

    return sumList;
}

// Returns a list containing the transpose of a list
COOList COOList::transpose(){
    COOList transList(COLS, ROWS);

    // Create a duplicate list to preserve the original matrix
    COONode* temp = head;
    COOList tempList(ROWS, COLS);
    while (temp != nullptr){
        tempList.push_back(temp->row, temp->col, temp->data);
        temp = temp->next;
    }

    // Search through the tempList to find the lowest col and row
    while(tempList.listsize > 0){
        COONode* smallest = tempList.head;
        temp = tempList.head;
        while(temp != nullptr){
            if (temp->col < smallest->col){
                smallest = temp;
            }
            else if (temp->col == smallest->col && temp->row < smallest->row){
                smallest = temp;
            }
            temp = temp->next;
        }
        transList.push_back(smallest->col, smallest->row, smallest->data);
        tempList.del(smallest);
    }
    return transList;
}

// Returns a list containing the product of a list
COOList COOList::multiply(COOList a_list){
    COOList productList(ROWS, a_list.COLS);
    if(COLS != a_list.ROWS){
        std::cout << "DIMENSION ERROR FOR MULTIPLICATION" << std::endl;
        return productList;
    }

    // Create a transpose list
    COOList a_trans = a_list.transpose();

    COONode* temp = head;
    
    while (temp != nullptr){
        //current row
        int curRow = temp->row;

        COONode* a_temp = a_trans.head;
        while (a_temp != nullptr){
            // current col is a_temp->row because it is transposed
            int curCol = a_temp->row;
            COONode* temp1 = temp;
            COONode* temp2 = a_temp;
            int sum = 0;

            while (temp1 != nullptr && temp2 != nullptr && temp1->row == curRow && temp2->row == curCol){
                if (temp1->col < temp2->col){
                    temp1 = temp1->next;
                }
                else if (temp1->col > temp2->col){
                    temp2 = temp2->next;
                }
                else{
                    sum += temp1->data * temp2->data;
                    temp1 = temp1->next;
                    temp2 = temp2->next;
                }
            }
            if (sum != 0){
                productList.push_back(curRow, curCol, sum);
            }
            a_temp = a_temp->next;
        }
        temp = temp->next;
    }
    return productList; 
}