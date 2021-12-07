class LlLDataNode{
    private:
        int col;
        int data;
        LlLDataNode* next;
        LlLDataNode* prev;

    public:
        // Constructors

        // Default constructor
        LlLDataNode();

        // Constructor that takes in column index and data tuple
        LlLDataNode(int col, int data);

        // Destructor
        ~LlLDataNode();

        // Output methods

        // Prints node for debugging purposes
        void print_node();

        // Friend class declarations
        friend class LlLColList;
        friend class LlLList;

};