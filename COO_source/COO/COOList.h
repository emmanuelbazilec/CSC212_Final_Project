#include "COONode.h"
#include <string>

class COOList{
    private:
        COONode* head;
        COONode* tail;
        int listsize;

        std::string fname;
        std::string ofname;
        int ROWS;
        int COLS;
    
    public:
        // Constructors:
        COOList();
        // To set rows and cols for operations
        COOList(int ROWS, int COLS);
        // To take in CLAs and construct list 
        COOList(char* fname, char* ROWS, char* COLS);
        // To read from condensed form file
        COOList(char* inname);
        // Destructor
        ~COOList();

        // Operations:

        // Appends a tuple to tail of list
        void push_back(int row, int col, int data);

        // Prepends a tuple to head of list
        void push_front(int row, int col, int data);

        // Deletes a node in list
        void del(COONode* a_node);

        // Inserts data into the correct location in list
        void insert(int row, int col, int data);

        // Matrix Operations

        // Returns a list containing the sum of two lists
        COOList add(COOList a_list);

        // Returns a list containing the transpose of a list
        COOList transpose();

        // Returns a list containing the product of a list
        COOList multiply(COOList a_list);
 

        // Outputs:

        // returns the size of the list
        int get_size();
        // print list for debugging
        void print_list();
        // write list to file
        void writeFile(char* ofname);
};