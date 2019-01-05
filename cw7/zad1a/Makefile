CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

main: bin/main.o \
		bin/producer.o
	$(CC) $^ -o $@ -lpthread

bin/main.o: src/main.c \
			include/producer.h | bin
	$(OBJECT)

bin/producer.o: src/producer.c \
				include/producer.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/