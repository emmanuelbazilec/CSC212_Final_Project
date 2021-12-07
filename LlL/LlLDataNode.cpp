#include <iostream>
#include "LlLDataNode.h"

// Default constructor
LlLDataNode::LlLDataNode(){
    this->col = 0;
    this->data = 0;
    this->next = nullptr;
    this->prev = nullptr;
}

// Constructor that takes in column index and data tuple
LlLDataNode::LlLDataNode(int col, int data){
    this->col = col;
    this->data = data;
    this->next = nullptr;
    this->prev = nullptr;
}

// Destructor
LlLDataNode::~LlLDataNode(){

}

// Prints node content to console for debugging purposes
void LlLDataNode::print_node(){ 
    std::cout << "col: " << col << " data: " << data << "\n";
}