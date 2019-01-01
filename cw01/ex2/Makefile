CFLAGS = -Wall
CC = gcc
OBJECT=$(CC) $< -c -I include -o $@

main: bin/main.o libackermann_static
	$(CC) bin/main lib/libackermann.a -I include -o $@

bin/main.o: \
		src/main.c \
		include/ackermann.h | bin
	$(OBJECT)

.PHONY: libackermann_static
libackermann_static: bin/ackermann.o
	ar rcs lib/libackermann.a ackermann.o | lib

bin/ackermann.o: \
		src/ackermann.c \
		include/ackermann.h | bin
	$(OBJECT)

bin:
	mkdir bin

lib:
	mkdir lib

.PHONY: clean
clean:
	rm -rf bin/

