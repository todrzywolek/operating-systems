CC = gcc
OPT = -Wall
OBJ = $(CC) $^ -o $@ $(OPT)

all: main parent

main: main.c
	$(OBJ)
	
parent: parent.c
	$(OBJ)

.PHONY: clean
clean:
	rm -f *.o main parent