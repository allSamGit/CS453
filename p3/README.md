## Thread-safe Library

* Author: Saman Rastgar
* Class: CS453 [Operating Systems] 

## Overview

This project will focus on creating a thread-safe version of an existing list library.

## Manifest

Item.c - Item C file
Item.h - Item header file
pc.c - single queue implementation 
pc-mq.c - multiple queue implementation
wrapper-library/ThreadsafeBoundList.c - thread safe linked-list 
wrapper-library/ThreadsafeBoundList.h - ThreadsafeBoundList header file
wrapper-library/Makefile - build wrapper library
backpack.sh - test implementation of the single queue implementation
test-pc-mq.sh - multiple queue test script
test-pc.sh - single queue test script
Makefile - build the program 
README.md - contain information about this program
script - script to test pc

## Building the project

In order to build the project please make sure you are in the correct directory:
* cd into the correct directory called "p1" with the foolowing command: 
[user@onyx ]$ cd p3

* Once you are in the directory enter the following command:
[user@onyx p3]$ make

* Once the project is built an executable called "pc" will be created: run
* the executable with the following command in order to open the shell:
[user@onyx p3]$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../list/lib:./lib
[user@onyx p3]$ ./pc <poolsize> <#items/producer> <#producers> <#consumers> <sleep interval(microsecs)>

* To test the program with the test-pc.sh script i create a script called "script":
* The script exports the library; run it like this:
[user@onyx p3]$ make

* To test the program to check if all tests have passed, run the following command:
[user@onyx p3]$ ./backpack.sh
 
## Features and usage

Using the pc-mq version of this program users can specify the number of
queues to use in the simulation. The queues are access in a round-robin
fashion.

## Testing

I used the test script, test-pc.sh to test the pc version of this program and the backpack.sh
to make sure I passed all the tests.

### Known Bugs

I have not come across any bugs.

## Reflection and Self Assessment

I did not encounter any major issues during the development and testing of this project. 
The kinds of errors I got were logical errors. For example: calling thread
safe method in a thread safe method causes a deadlock; which was one the things discussed in 
class and issues I came across during the implementation. To fix these errors I removed the 
thread safe method and replaced them with the non thread safe method.
What I found challenging, was allocating space for structures. What finally
clicked for me was how to create a wrapper in order to make a program thread safe
and how C implementation of a monitor works.
 
## Sources used

The OS book for this class: http://pages.cs.wisc.edu/~remzi/OSTEP/

In class lectures about the project
