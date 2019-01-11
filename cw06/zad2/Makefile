CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

all: barber

barber: bin/barber.o \
		bin/posix_sems.o \
		bin/queue.o
	$(CC) $^ -o $@

client: bin/client.o \
		bin/sys_v_sems.o \
		bin/queue.o
	$(CC) $^ -o $@

bin/barber.o: src/barber.c \
			include/posix_sems.h \
			include/queue.h | bin
	$(OBJECT)

bin/client.o: src/client.c \
			include/posix_sems.h \
			include/queue.h | bin
	$(OBJECT)

bin/posix_sems.o: src/posix_sems.c \
				include/posix_sems.h | bin
	$(OBJECT)

bin/queue.o: src/queue.c \
				include/queue.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ barber client