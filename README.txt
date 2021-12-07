Class to read and store sparse matrices from file in a Coordinate List format.

commands that work in main driver file (COO.cpp):

COOList list_name(argv[1], argv[2], argv[3]);

- Stores and reads a sparse matrix from file
- argv[1] is the filename.txt for the file to read from SpMfile directory
- argv[2] is the number of rows
- argv[3] is the number of columns

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

list_name.print_list();

- Prints data stored in list class to console

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

list_name.writeFile(argv[4]);

- Writes the data stored in the class to a file in the CmpSpMfile directory
- argv[4] is the filename.txt for the file to write to in the CmpSpMfile directory

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

COOList sum_list_name = first_list.add(second_list);

- Returns the resulting matrix of addition on two sparse matrices if possible

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

COOList trans_list_name = first_list.transpose();

- Returns a transpose matrix of first_list

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

COOList product_list_name = first_list.multiply(second_list);

- Returns the resulting matrix from the multiplication of first_list and second_list
  if possible
