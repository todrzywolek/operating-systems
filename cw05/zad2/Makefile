CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

all: server client

server: bin/server.o bin/queue_utils.o
	$(CC) $^ -o $@ -lrt

bin/server.o: src/server.c \
			include/queue_utils.h | bin
	$(OBJECT)

client: bin/client.o bin/queue_utils.o
	$(CC) $^ -o $@ -lrt

bin/client.o: src/client.c \
			include/queue_utils.h | bin
	$(OBJECT)

bin/queue_utils.o: src/queue_utils.c \
				include/queue_utils.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ main server client