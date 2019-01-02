CFLAGS = -Wall
CC = gcc

OBJECT=$(CC) $< -c -I include -o $@

main: bin/main.o
	$(CC) $^ -o $@

bin/main.o: src/main.c | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/