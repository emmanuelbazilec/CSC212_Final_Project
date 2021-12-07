#include <iostream>
#include "COO/COOList.h"

int main(int argc, char* argv[]){
    // used to compile
    // g++ COO.cpp ./COO/COONode.cpp ./COO/COOList.cpp -o COO.out
    
    // used the following CLAs to run this main
    // ./COO.out 05example.txt 100 100 05out.txt 06example.txt 100 100 06out.txt sumout.txt transout.txt productout.txt COOsumout.txt
    
    // Initializing first list
    COOList a_list(argv[1], argv[2], argv[3]);
    // std::cout << "b_list: " << std::endl;
    // b_list.print_list();
    a_list.writeFile(argv[4]);
    
    // Initializing second list
    COOList b_list(argv[5], argv[6], argv[7]);
    // std::cout << "c_list: " << std::endl;
    // c_list.print_list();
    b_list.writeFile(argv[8]);
    
    // Example of sum functionality
    COOList sum_list = a_list.add(b_list);
    // std::cout << "sum_list: " << std::endl;
    // sum_list.print_list();
    sum_list.writeFile(argv[9]);
    
    // Example of transpose functionality
    COOList transList = a_list.transpose();
    // std::cout << "c_list transpose: " << std::endl;
    // transList.print_list();
    transList.writeFile(argv[10]);
    
    // Example of multiply functionality
    COOList productList = b_list.multiply(a_list);
    // productList.print_list();
    productList.writeFile(argv[11]);

    // Example of read from file functionality
    COOList cmplist(argv[12]);
    std::cout << "List loaded from file: " << std::endl;
    cmplist.print_list();

}