class COONode{
    private:
        int row;
        int col;
        int data;
        COONode* next;
        COONode* prev;

    public:
        // Default constructor
        COONode();
        // Destructor
        ~COONode();

        // Overloaded constructor that takes in data
        COONode(int data);

        // Overloaded constructor that takes in row index, column index, and data tuples
        COONode(int row, int col, int data);

        // Overloaded constructor that takes in row index, column index, and data tuples as well as a pointer to the next node
        COONode(int row, int col, int data, COONode* next);

        // Prints node for debugging
        void printNode();

        // Friend class declaration
        friend class COOList;
};  