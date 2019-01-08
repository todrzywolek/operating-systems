CFLAGS = -Wall
CC = gcc

CC_OPT = $(OPT)
OBJECT=$(CC) $< -c -I include $(CC_OPT) -o $@

ackermann: bin/main_ackermann.o \
	 		bin/ackermann.o \
			bin/time_counter.o
	$(CC) $^ $(CC_OPT) -o main

bin/main_ackermann.o: \
		src/main_ackermann.c \
		include/ackermann.h \
		include/time_counter.h | bin
	$(OBJECT)

bin/ackermann.o: \
		src/ackermann.c \
		include/ackermann.h | bin
	$(OBJECT)

file_rw: bin/file_rw.o \
		bin/time_counter.o
	$(CC) $^ $(CC_OPT) -o main

bin/file_rw.o: \
		src/file_rw/file_rw.c \
		include/time_counter.h | bin
	$(OBJECT)

matrix: bin/matrix.o \
		bin/time_counter.o
	$(CC) $^ $(CC_OPT) -o main

bin/matrix.o: \
		src/matrix/matrix.c \
		include/time_counter.h | bin
	$(OBJECT)

array_copy: bin/array_copy.o \
		bin/time_counter.o
	$(CC) $^ $(CC_OPT) -o main

bin/array_copy.o: \
		src/array_copy/array_copy.c \
		include/time_counter.h | bin
	$(OBJECT)

bin/time_counter.o: \
		src/time_counter.c \
		include/time_counter.h | bin
	$(OBJECT)

bin:
	mkdir bin

.PHONY: clean
clean:
	rm -rf bin/ rand_file.txt file.txt results.txt main