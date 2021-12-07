#include <iostream>
#include "LlL/LlLList.h"

int main(int arc, char* argv[]){
    // Compiled with g++ LlL.cpp ./LlL/LlLDataNode.cpp ./LlL/LlLColList.cpp ./LlL/LlLList.cpp -o LlL.out
    // CLAs used:
    // ./LlL.out 05example.txt 100 100 05out.txt 06example.txt 100 100 06out.txt sumout.txt productout.txt LlLproductout.txt transout.txt
    
    // Constructing lists from sparse files
    LlLList a_list(argv[1], argv[2], argv[3]);
    LlLList b_list(argv[5], argv[6], argv[7]);
    // LlLList c_list(argv[9], argv[10], argv[11]);
    // LlLList d_list(argv[13], argv[14], argv[15]);

    // Writing condensed lists to file
    a_list.write_file(argv[4]);
    b_list.write_file(argv[8]);
    // c_list.write_file(argv[12]);
    // d_list.write_file(argv[16]);

    // Demonstrating addition
    LlLList sum_list = a_list.add(b_list);
    sum_list.write_file(argv[9]);

    // Demonstrating multiplication
    LlLList product_list = a_list.multiply(b_list);
    product_list.write_file(argv[10]);

    // Demonstrating reading from condensed file
    LlLList from_confile(argv[11]);
    std::cout << "List loaded from file: " << std::endl;
    from_confile.print_list();

    // Demonstrating transpose
    LlLList trans_list = b_list.transpose();
    trans_list.write_file(argv[12]);
}