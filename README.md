# data-structures-in-C
A small library with implementation of data structures in C.

Implemented data structures:

* Linked List(Circular linked list, double linked list)
* Stack
* Queue
* Binary Tree
* Chained Hash Table
* Set
* Graph

# Running test
* Clone the repo
* Run `autoreconf --install` to generate build system files
* Run `./configure && make` to configure and build the project
* Run `make test` to test the file
* Run `make clean` to clean object files
* Run `rm -r !(configure.ac|Makefile.am|src|README.md) && cd src && rm -r !(headers|implementations|tests|Makefile.am|main.c) && cd ..` to clean useless files
