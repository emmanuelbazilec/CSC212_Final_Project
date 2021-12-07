#include "LlLColList.h"
#include <iostream>

// Default constructor
LlLColList::LlLColList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    this->row = 0;

    this->prev = nullptr;
    this->next = nullptr;
}

// Overloaded constructor with row
LlLColList::LlLColList(int row){
    this->head = nullptr;
    this->tail = nullptr;
    this->listsize = 0;
    this->row = row;

    this->prev = nullptr;
    this->next = nullptr;
}

// Destructor
LlLColList::~LlLColList(){

}

// Prepends list with column index, data tuple
void LlLColList::push_front(int col, int data){
    LlLDataNode* temp = new LlLDataNode(col, data);
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

// Appends list with column index, data tuple
void LlLColList::push_back(int col, int data){
    LlLDataNode* temp = new LlLDataNode(col, data);
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

// Inserts column, data tuple into sorted position in list
void LlLColList::insert(int col, int data){
    LlLDataNode* temp = head;
    while (temp != nullptr){
        if (temp->col >= col){
            break;
        }
        temp = temp->next;
    }
    if (temp == nullptr){
        push_back(col, data);
        return;
    }
    else if (temp->col == col){
        if (temp->data + data != 0)
            temp->data += data;
        else
            del(temp);
        return;
    }
    else if (temp == head){
        push_front(col, data);
        return;
    }
    LlLDataNode* newnode = new LlLDataNode(col, data);
    temp->prev->next = newnode;
    newnode->prev = temp->prev;
    newnode->next = temp;
    temp->prev = newnode;
    this->listsize += 1;
} 

// Deletes node from list
void LlLColList::del(LlLDataNode* a_node){
    if (listsize == 1){
        this->head = nullptr;
        this->tail = nullptr;
        this->listsize = 0;
        delete a_node;
        return;
    }
    else if (a_node == head){
        head = head->next;
        this->listsize -= 1;
        return;
    }
    else if (a_node == tail){
        this->tail = tail->prev;
        this->tail->next = nullptr;
        a_node = nullptr;
        this->listsize -= 1;
        return;
    }
    a_node->prev->next = a_node->next;
    a_node->next->prev = a_node->prev;
    this->listsize -= 1;

}

// Prints list to console
void LlLColList::print_list(){
    LlLDataNode* temp = head;
    if (listsize == 0){
        std::cout << "empty list" << std::endl;
        return;
    }
    while (temp != nullptr){
        std::cout << "row: " << row << " col: " << temp->col << " data: " << temp->data << "\n";
        temp = temp->next;
    }
}

// Setter for row
void LlLColList::set_row(int row){
    this->row = row;
}