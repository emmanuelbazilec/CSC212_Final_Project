#include "COONode.h"
#include <iostream>

// Default construcor
COONode::COONode(){
    this->row = 0;
    this->col = 0;
    this->data = 0;
    this->next = nullptr;
    this->prev = nullptr;
}

// Overloaded constructor that takes in data
COONode::COONode(int data){
    this->row = 0;
    this->col = 0;
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

// Overloaded constructor that takes in row index, column index, and data tuples
COONode::COONode(int row, int col, int data){
    this->row = row;
    this->col = col;
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

// Overloaded constructor that takes in row index, column index, and data tuples as well as a pointer to the next node
COONode::COONode(int row, int col, int data, COONode* next){
    this->row = row;
    this->col = col;
    this->data = data;
    this->next = next;
    this->prev = nullptr;
}

// Destructor
COONode::~COONode(){
    
}

// Prints node for debugging
void COONode::printNode(){
    std::cout << "row: " << row << "\ncol: " << col << "\ndata: " << data << "\nat" << &data << "\nnext: " << next << "\n";
}