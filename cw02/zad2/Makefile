CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

main: bin/main.o \
		bin/utils.o
	$(CC) $^ -o $@

bin/main.o: src/main.c \
			include/utils.h | bin
	$(OBJECT)

bin/utils.o: src/utils.c \
				include/utils.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/