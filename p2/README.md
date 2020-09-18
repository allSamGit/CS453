# Project 2 /Multi-threaded Mergesort {#mainpage}

* Class: CS453/552 [Operating Systems] Section 2

## Overview

This C language application uses multiple threads to speed up mergesort.
The application take in command line arguments for the number of elements,
the number of threads to generate, and an optional seed value for the
random numbers generator, creating elements to sort.

## Manifest

mergersort.c - file contains the implementation of the multi-threaded mergersort
mergersortTest.c - file contains the main method
timing.c - file contains methods to time the execution of the multi-threaded mergersort
Makefile - build the program 
README.md - contains instruction on how to build the program

## Building the project

cd /p2 - change directory to the project directory (p2)

make -run make command in the project directory (p2) to build the project

cd multi-threaded - change directory to multi-threaded directory

./mergesort - run program with command line arguments of number of elements
	      number of threads, and optional random seed (e.g ./mergesort 10 1)

	      Usage: ./mergesort <input size> <cutoff level> [<seed>]

## Features and usage

The main feature of this program, is limiting the number of threads that
the program can generate. This is done via a command line argument.

## Testing

Onyx node49
Number of Cores: 4
Number of elements: 100,000,000

TABLE OF TIMES AND SPEEDUPS

Threads | Run Times | Speedups after each thread                             |Speedups compare to 1 thread run time   
1	|    11.16  |    11.16 - 0 = 11.16 			             |	  11.16 - 0 = 11.16
2	|    6.11   |    11.16 - 6.11 = 5.05				     |	  11.16 - 6.11 = 5.49
3	|    6.12   |    6.11 - 6.12 = -0.01 (no speedup, when down by 0.01) |	  11.16 - 6.12 = 5.48	
4	|    3.73   |    6.12 - 3.73 = 2.39				     |	  11.16 - 3.73 = 7.87
5	|    3.59   |    3.73 - 3.59 = 0.14                                  | 	  11.16 - 3.59 = 8.01
6	|    3.65   |    3.59 - 3.65 = -0.06 (no speedup, when down by 0.06) |	  11.16 - 3.65 = 7.95
7	|    3.60   |    3.65 - 3.60 = 0.05				     |	  11.16 - 3.60 = 8
8	|    3.63   |    3.60 - 3.63 = -0.03 (no speedup, when down by 0.03) |    11.16 - 3.63 = 7.97


Tested the multi-threaded mergesort, by varying the number of thread (from 1 to 8)
on n = 100000000 elements. The table above show the run times and the speedups
form thread 1 to 8. I got better result on the onyx node than on the onyx server.

##Discussion

One of the issue I encountered during the development and testing of this
program was developing the program without modifying the serial_mergersort
function. Another issue I encountered was where to call the merge function.
Another was how to stop the generation of new threads, using the user input
number of threads. I had to research how to work with pthreads, how to
create pthreads, send multiple arguments to it function and join them.
The kinds of errors I got was logical errors, which lead to segfaults. To fix
these errors I debug my code and change the logic of functions.

The part of the project I found challenging, was setting up the recursive
multi-threaded mergesort and not modifying the serial_mergesort function. What
clicked for me was how to create pthreads, send multiple arguments to it function
and join them.
