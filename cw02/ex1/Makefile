CFLAGS = -Wall
CC = gcc

OBJECT=$(CC) $< -c -I include -o $@

main: bin/main.o \
		bin/generate.o \
		bin/utils.o
	$(CC) $^ -o $@

bin/main.o: src/main.c \
			include/generate.h | bin
	$(OBJECT)

bin/generate.o: src/generate.c \
				include/generate.h \
				bin/utils.o \
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