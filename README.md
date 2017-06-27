# Hexadoku-Validator
16x16 Sudoku which is also called as Hexadoku is similar to conventional 9x9 Sudoku, but has 16 x 16 grids.
This program is written using different numbers of threads. The threads in the program perform validation check over filled Sudoku and time required by them is calculated.

Single Thread Program named hexadoku01.c :
In the program where single thread is used, it has only main program that will read the filled Sudoku and perform the duplicity and out of order check over it. It will first perform this validation check over every rows, then over every column and then over every grid. If the Sudoku fails to satisfy the condition of validity then an output will display that the input Sudoku is invalid. If all the conditions for a valid Sudoku are met then the output will display that the Sudoku is valid.

3 – Threads Program named hexadoku03.c :
In this program, one threads checks for the validity of 16 rows, one thread checks validity of 16 columns and one thread checks validity of 16  4x4 sub-grids. Hence there are total 3 threads that will validate the Sudoku.

18 – Threads Program named hexadoku18.c :
In this program, one threads checks for the validity of 16 rows, one thread checks validity of 16 columns and 16 threads to check validity of 16 4x4 sub-grids. Hence there are total 3 threads that will validate the Sudoku.

48 – Threads Program named hexadoku48.c :
In this program, separate thread is used to check validity for every row, every column and every grid. As there are 16 rows, 16 columns and 16 4x4 sub-grids, there would be total 48 threads.

The above code also records the execution time and prints with the output. Which can be used to compare the performance and efficiency of programs with different number of threads.


EXECUTION:
There are 4 source codes as mentioned above, and to compile them a make file (check Appendences) is written.
Go to the directory containing all source codes, Sudoku solution in text file and  make file.
To compiles all the source codes:
$ make

To execute  a source code:
$ ./hexadokuXX  valid_test.txt
 The format should contain executable code name and the text file name which has Hexadoku solution as shown above the XX is replaced by 01, 03, 18 and 48.
 
