CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

main: bin/main.o \
		bin/producer.o \
		bin/common.o \
		bin/consumer.o
	$(CC) $^ -o $@ -lpthread

bin/main.o: src/main.c \
			include/producer.h \
			include/common.h | bin
	$(OBJECT)

bin/producer.o: src/producer.c \
				include/producer.h \
				bin/common.o | bin
	$(OBJECT)

bin/consumer.o: src/consumer.c \
				include/consumer.h \
				bin/common.o | bin
	$(OBJECT)

bin/common.o: src/common.c \
				include/common.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/