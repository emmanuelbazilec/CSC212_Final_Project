#include "LlLColList.h"
#include <string>

class LlLList{
    private:
        LlLColList* head;
        LlLColList* tail;
        int listsize;

        std::string fname;
        std::string ofname;
        int ROWS;
        int COLS;

    public:
        // Constructors and Destructor
        LlLList();
        // To set rows and cols for operations
        LlLList(int ROWS, int COLS);
        // To take in CLAs and construct list
        LlLList(char* fname, char* ROWS, char* COLS);
        // To read list from file
        LlLList(char* inname);
        // Default Destructor
        ~LlLList();

        // List Operations

        // Appends column list to tail
        void push_back(LlLColList* a_col); 
        // Prepends column list to head
        void push_front(LlLColList* a_col);
        // Inserts data point into list in sorted location
        void insert(int row, int col, int data);
        // Deletes a row from the list
        void del(LlLColList* a_col);
        
        // Matrix Operations

        // Returns the result of matrix addition
        LlLList add(LlLList a_list);
        // Returns the result of transposing a matrix
        LlLList transpose();
        // Returns the product of two matrices
        LlLList multiply(LlLList a_list);
        
        // Output Methods

        // Prints list contents to console
        void print_list();
        // Returns the size of the list
        int get_size();
        // writes list to file
        void write_file(char* ofname);
};