CFLAGS = -Wall -I include
CC = gcc
OBJECT=$(CC) $< -c $(CFLAGS) -o $@

main_a: bin/main.o lib/libmatrix.a bin/time_counter.o
	$(CC) $^ -L ./lib -I include -o $@

main_so: bin/main.o lib/libmatrix.so bin/time_counter.o
	LD_LIBRARY_PATH=/home/Projects/studia/operating-systems/cw01/ex2
	export LD_LIBRARY_PATH
	$(CC) $(CFLAGS) $^ -o $@

bin/main.o: \
		src/main.c \
		include/matrix.h \
		include/time_counter.h | bin
	$(OBJECT)

lib/libmatrix.a: bin/matrix.o | lib
	ar -rcs $@ $^

lib/libmatrix.so: bin/matrix.o | lib
	$(CC) -fPIC $(CFLAGS) $^ -shared -o $@

bin/matrix.o: \
		src/matrix.c \
		include/matrix.h | bin
	$(CC) $< -fPIC -c $(CFLAGS) -o $@

bin/time_counter.o: \
		src/time_counter.c \
		include/time_counter.h | bin
	$(OBJECT)

bin:
	mkdir bin

lib:
	mkdir lib

.PHONY: clean
clean:
	rm -rf bin/ lib/ main_a main_so

