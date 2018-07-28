# compiler
CC = gcc

# compiler flags
# -g adds debug information to the executable file
# -Wall turns on most, but not all, compiler warnings 
CFLAGS = -g

DIR = ./implementations
# target entry: "default" or "all"
default : entry

# create executable file lee: these object files needed
entry: main.o print.o list.o stack.o queue.o set.o chtb.o bitree.o
	$(CC) $(CFLAGS) -o lee main.o print.o list.o stack.o queue.o set.o chtb.o bitree.o -lm

# main.o generate
main.o: $(DIR)/main.c
	$(CC) $(CFLAGS) -c $(DIR)/main.c

print.o: $(DIR)/print.c
	$(CC) $(CFLAGS) -c $(DIR)/print.c

list.o: $(DIR)/list.c
	$(CC) $(CFLAGS) -c $(DIR)/list.c

stack.o: $(DIR)/stack.c
	$(CC) $(CFLAGS) -c $(DIR)/stack.c

queue.o: $(DIR)/queue.c
	$(CC) $(CFLAGS) -c $(DIR)/queue.c

set.o: $(DIR)/set.c
	$(CC) $(CFLAGS) -c $(DIR)/set.c

chtb.o: $(DIR)/chtb.c
	$(CC) $(CFLAGS) -c $(DIR)/chtb.c

bitree.o: $(DIR)/bitree.c
	$(CC) $(CFLAHS) -c $(DIR)/bitree.c
# make clean
# exe: executable file
# .o: object file
# .~: backup file
clean: 
	rm *.o lee





