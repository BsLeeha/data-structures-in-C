# data-structures-in-C
a small library with implementations of data structures in C

# Running test
* Clone the repo
* Run `autoconf --install` to generate build system files
* Run `./configure && make` to configure and build the project
* Run `make test` to test the file
* Run `make clean` to clean object files
* Run `rm -r !(configure.ac|Makefile.am|src) && cd src && rm -r !(headers|implementations|tests|Makefile.am) && cd ..` to clean useless files
