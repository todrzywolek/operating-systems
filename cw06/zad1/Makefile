CFLAGS = -Wall -c -I include
CC = gcc

OBJECT=$(CC) $< $(CFLAGS) -o $@

barber: bin/barber.o \
		bin/sys_v_sems.o \
		bin/queue.o
	$(CC) $^ -o $@

bin/barber.o: src/barber.c \
			include/sys_v_sems.h \
			include/queue.h | bin
	$(OBJECT)

bin/sys_v_sems.o: src/sys_v_sems.c \
				include/sys_v_sems.h | bin
	$(OBJECT)

bin/queue.o: src/queue.c \
				include/queue.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ barber