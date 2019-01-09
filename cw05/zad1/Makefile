CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

all: server

server: bin/server.o bin/queue_utils.o
	$(CC) $^ -o $@

bin/server.o: src/server.c \
			include/queue_utils.h | bin
	$(OBJECT)

bin/queue_utils.o: src/queue_utils.c \
				include/queue_utils.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ main server