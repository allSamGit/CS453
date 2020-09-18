## Shell Part 1

* Author:Saman Rastgar
* Class: CS453 [Operating Systems] 

CONTENTS.md contains a litst of all the files given to us in order to 
finish the project 

## Overview

Shell Part 1 is the first programming project in CS453 and has us work with a simple
shell which we will extend its functionality and implement basic commands like cd and exit.

## Manifest

mydash.c -contains the main method for the shell to work
mydash.h -contains the header file for mydash.c
error.c -contains functions to report errors
parse.c -contains functions to parse the user's input
Makefile -Makefile in order to be able to build the project
mydash -executable created after make, in order to run the shell

## Building the project

In order to build the project please make sure you are in the correct directory:
* cd into the correct directory called "p1" with the foolowing command: 
[user@onyx ]$ cd p1 

* Once you are in the directory enter the following command:
[user@onyx p1] make

* Once the project is built an executable called "mydash" will be created: run
* the executable with the following command in order to open the shell:
[user@onyx p1] ./mydash

* Result:

mydash>

* Enter commands to test the shell's functionality

In order to produce doxygen docs run the following command:
[user@onyx p1] doxygen doxygen-config
 
## Features and usage

This application already contains a few built-in commands and also accepts other
commands and their arguments like: ls, ls -l and so on. 

The main features in this shell application are the "exit" command, in order
to exit the shell and the the "cd" command in order to change directory once
the shell is running.

If you were to just press the enter key, the shell will just display other prompt.
If you were to enter empty spaces and then press the enter key the shell will
return another prompt as well.

The shell handles EOF as well and the shell terminates normally when receiving
"ctrl-d" input from the user.

The prompt of the shell is "mydash>" which can be changed it to whatever name
we want it to be.

We can print out the version of the project by using the following command:
[user@onyx p1] ./mydash -v

## Testing

In order to test the application I would test the program by compiling it 
and running in order to figure out any bugs I had in the code. I took 
advantage of the test cases provided by the project itself.
After failing a few of those I had to go back to the code itself and fix a few
lines in order to make sure I was getting the correct output.
Used Valgring for testing as well.
I did not create a testing plan.

### Valgrind

I used Valgrind pretty often in order to test if by code was healthy and had a
good structure. It has helped figure out how to solve a segmentation fault error
I ran my shell: because of this issue the shell would not even start.
After fixing this issues I ended up getting a bunch of error when issuing the exit
command on the shell and a (core dumped) error at the end. With Valgrid check I was
able to figure what was causing the problem.

### Known Bugs

Valgrind states that there is a memory leak: I could check most of the memory bugs by 
running the test on the part of program needs more memory and I decided to allocate more space for my cmd
lines. 

## Reflection and Self Assessment

This project was very interesting. I definitely had to go back and brush up on 
a few C language concepts because I could not remember them very well. The class 
environemnt is very fun for bringing back those concepts we learned in CS253.
I spent a lot of time on making my functions work well each other in order 
for me to get the result i wanted. 
"Make clean" and "make" was very useful becuase it helped me figured out how to
manage a few conceptual errors i encountered.

I did spend a lot of time at first trying to figure how to start and even figure
out how structure my c files. 
I also spent some time dealing with readline() and trying to integrated it correctly 
for the project to work as it should. I also used the GNU readline library to 
become more familiar with what I was doing.
 
## Sources used

The OS book for this class: http://pages.cs.wisc.edu/~remzi/OSTEP/

Got help in the computer lab from the TAs


I also used The GNU Readline libray to get familiar with what I was doing: https://tiswww.case.edu/php/chet/readline/rltop.html

In class lectures about the project

