#include "LlLDataNode.h"

class LlLColList{
    private:
        // ColList values
        LlLDataNode* head;
        LlLDataNode* tail;
        int listsize;
        int row;

        // RowNode values
        LlLColList* next;
        LlLColList* prev;

    public:
        // Constructors

        // Default constructor
        LlLColList();

        // Constructor that takes input row value
        LlLColList(int row);

        // Destructor
        ~LlLColList();

        // List methods

        // Prepends column, data tuple node to front of list
        void push_front(int col, int data);

        // Appends column, data tuple node to tail of list
        void push_back(int col, int data);

        // Inserts column, data tuple to the correct sorted spot in list
        void insert(int col, int data);

        // Deletes node in list
        void del(LlLDataNode* a_node);

        // Prints list contents to console
        void print_list(); 

        // Node methods
        void set_row(int row);

        // Friend class declarations
        friend class LlLList;
        
};