<h1 align="center"> CSC212 Final Project: Sparse Matrices Using Linked Lists </h1>

<h2 align="center"> Fall 2021 </h2>

<h3 align="center"> Contributers: Michael Sherlock, Ben LaForge </h3>


### **Data Structure: Sparse Matrix**

An integer sparse matrix is a 2-Dimensional integer array in which most of the elements are non-information (like 0).  Storing and operating on sparse requires allocating storage and parsing through many 0 values that could be ignored, therefore it is beneficial to store sparse matrices in a compressed form which only requires storage for the number of non-zero values and their coordinates.  This project covers two ways of storing a sparse matrix in compressed form: Coordinate list (COO), and List of lists (LlL).  The Coordinate lit structure stores the data in (row, col, data) tuple nodes in a single or doubly linked list.  List of lists stores lists representing a column with (col, data) tuple nodes in another list representing rows in a (row, column_list*) tuple, allowing for improved time efficiency when accessing or searching for a value in the matrix. 

### **File Descriptions**

#### 1. /SpMfile/ and /CmpSpMfile/ directories 

The SpMfile directory is designated for sparse matrix files to be read from are stored
- 01example: example 3 x 4 matrix
- 02exmaple: example 3 x 4 matrix
- 03example: example 3 x 4 matrix
- 04example: example 4 x 2 matrix
- 05example: example 100 x 100 block-diagonal matrix
- 06example: example 100 x 100 block-diagonal matrix


The CmpSpMfile directory stores matrices in compressed form.

---

#### 2. ClearDir.py

Short python program to clear the CmpSpMfile directory if it gets too cluttered.

---

#### 3. /COO/ directory

This file contains the class declaration and methods for constructing the coordinate list object.

- 'COONode.h': Header file for the COONode class containing overloaded constructors for ease of assignment in other classes.  The Nodes store integer tuples of row_idx, col_idx, and data.
- 'COONode.cpp': supporting file for COONode.h implementing constructors and methods.
- 'COOList.h': Header file for the COOList class containing class declaration and methods for COOList objects.  These methods will be detailed in the COO.cpp section.
- 'COOList.cpp': Supporting file for COOList.h implementing all methods. 

---

#### 4. /LlL/ directory

This file contains the class elcaration and methods for onstructing the lit of lists object.

- 'LlLDataNode.h': Header file for the LlLDataNode class containing overloaded constructors for assignment in other classes. The Nodes store integer tuples of column_index and data.
- 'LlLDataNode.cpp': Supporting file for LlLDataNode.h implementing constructors and methods.
- 'LlLColList.h': Header file for the LlLColList class containing overloaded contructor for assignment in other classes.  The Nodes store integer and class pointers of row number and column_list.
- 'LlLColList.cpp': Supporting file for LlLColList.h implementing constructors and methods.
- 'LlLList.h': Header file for the main LlLList class to build and store list of lists structured matrices.  Also contains method declarations.
- 'LlLList.cpp': Supporting file for LlLList.h that implements all methods for the list of lists data strucutre.  These methods will be detaile in the LlL.cpp section.

---

#### 5. COO.cpp

This file is the a driver function of the coordinate class providing for a space to construct and operate on coordinate lists.
commands that work in main driver file (COO.cpp):

- 'COOList list_name(argv[1], argv[2], argv[3]);'

- Stores and reads a sparse matrix from file
- argv[1] is the filename.txt for the file to read from SpMfile directory
- argv[2] is the number of rows
- argv[3] is the number of columns

---

- 'list_name.print_list();'

- Prints data stored in list class to console

---

- 'list_name.writeFile(argv[4]);'

- Writes the data stored in the class to a file in the CmpSpMfile directory
- argv[4] is the filename.txt for the file to write to in the CmpSpMfile directory

---

- 'COOList sum_list_name = first_list.add(second_list);'

- Returns the resulting matrix of addition on two sparse matrices if possible

---

- 'COOList trans_list_name = first_list.transpose();'

- Returns a transpose matrix of first_list

---

- 'COOList product_list_name = first_list.multiply(second_list);'

- Returns the resulting matrix from the multiplication of first_list and second_list
  if possible

---

#### 6. LlL.cpp

This file is the a driver function of the coordinate class providing for a space to construct and operate on list of lists.

commands that work in main driver file (LlL.cpp):

- 'LlLList list_name(argv[1], argv[2], argv[3]);'

- Stores and reads a sparse matrix from file
- argv[1] is the filename.txt for the file to read from SpMfile directory
- argv[2] is the number of rows
- argv[3] is the number of columns

---

- 'LlLList list_name(argv[1]);'

- Reads from a compressed matrix file and stores it in LlL format
- argv[1] is the filename.txt for the file to read from CmpSpMfile directory

---

- 'list_name.print_list();'

- Prints data stored in list class to console

---

- 'list_name.writeFile(argv[4]);'

- Writes the data stored in the class to a file in the CmpSpMfile directory
- argv[4] is the filename.txt for the file to write to in the CmpSpMfile directory

---

- 'LlLList sum_list_name = first_list.add(second_list);'

- Returns the resulting matrix of addition on two sparse matrices if possible

---

- 'LlLList trans_list_name = first_list.transpose();'

- Returns a transpose matrix of first_list

---

- 'LlL product_list_name = first_list.multiply(second_list);'

- Returns the resulting matrix from the multiplication of first_list and second_list
  if possible

### **How to Compile and Run**

This project does not use a GUI, instead it relies on command line arguments for input and will spit out .txt files as an output.  Download the project, create a .txt file containing the sparse matrices you are using into the SpMfile directory.  Now just update the main functions of COO.cpp and LlL.cpp to take in however many CLAs you want and what you want the to do with the lists that are created.  

### **Contribution**

Michael Sherlock:
* Implementation of List of Lists 
* Researched Sparse Matrices
* Worked on Presentation

Benjamin Laforge:
* Implementation of Coordinate Lists
* Researched Sparse Matrices
* Organized Prezentation
* Organizer of Group Meeting




