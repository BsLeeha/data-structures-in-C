# compiler
CC = gcc

# compiler flags
# -g adds debug information to the executable file
# -Wall turns on most, but not all, compiler warnings 
CFLAGS = -g

IMPDIR = ./implementations
TESTDIR = ./tests
# target entry: "default" or "all"
default : entry

# create executable file lee: these object files needed
entry: main.o print.o list.o stack.o queue.o set.o chtb.o bitree.o
	$(CC) $(CFLAGS) -o lee main.o print.o list.o stack.o queue.o set.o chtb.o bitree.o -lm

# main.o generate
main.o: $(TESTDIR)/main.c
	$(CC) $(CFLAGS) -c $(TESTDIR)/main.c

print.o: $(IMPDIR)/print.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/print.c

list.o: $(IMPDIR)/list.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/list.c

stack.o: $(IMPDIR)/stack.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/stack.c

queue.o: $(IMPDIR)/queue.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/queue.c

set.o: $(IMPDIR)/set.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/set.c

chtb.o: $(IMPDIR)/chtb.c
	$(CC) $(CFLAGS) -c $(IMPDIR)/chtb.c

bitree.o: $(IMPDIR)/bitree.c
	$(CC) $(CFLAHS) -c $(IMPDIR)/bitree.c
# make clean
# exe: executable file
# .o: object file
# .~: backup file
clean: 
	rm *.o lee





