CC = gcc
OPT = -Wall
OBJ = $(CC) $^ -o $@ $(OPT)

all: child parent

child: child.c
	$(OBJ)

parent: parent.c
	$(OBJ)

.PHONY: clean
clean:
	rm -f *.o