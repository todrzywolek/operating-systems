CFLAGS = -Wall
CC = gcc

OBJECT=$(CC) $< -c -I include -o $@

main: bin/main.o \
		bin/generate.o \
		bin/utils.o \
		bin/sort.o \
		bin/my_copy.o
	$(CC) $^ -o $@

bin/main.o: src/main.c \
			include/generate.h \
			include/sort.h \
			include/my_copy.h | bin
	$(OBJECT)

bin/generate.o: src/generate.c \
				include/generate.h \
				bin/utils.o \
				include/utils.h | bin
	$(OBJECT)

bin/utils.o: src/utils.c \
			 include/utils.h | bin
	$(OBJECT)

bin/sort.o: src/sort.c \
			 include/sort.h \
			 bin/utils.o \
			 include/utils.h | bin
	$(OBJECT)

bin/my_copy.o: src/my_copy.c \
			 include/my_copy.h \
			 bin/utils.o \
			 include/utils.h | bin
	$(OBJECT)

bin:
	mkdir bin

# tests
FILE1=dane1.dat
FILE2=dane2.dat
FILE3=dane3.dat
FILE4=dane4.dat
FILE5=dane5.dat
FILE6=dane6.dat
FILE7=dane7.dat
FILE8=dane8.dat

SIZE1=4 10000
SIZE2=512 500
SIZE3=4096 15
SIZE4=8192 10
SIZE5=4 20000
SIZE6=512 800
SIZE7=4096 20
SIZE8=8192 20

M1=sys
M2=lib

wyniki.txt: main
	./$^ generate $(FILE1) $(SIZE1)
	./$^ generate $(FILE2) $(SIZE2)
	./$^ generate $(FILE3) $(SIZE3)
	./$^ generate $(FILE4) $(SIZE4)
	./$^ generate $(FILE5) $(SIZE5)
	./$^ generate $(FILE6) $(SIZE6)
	./$^ generate $(FILE7) $(SIZE7)
	./$^ generate $(FILE8) $(SIZE8)

.PHONY: clean
clean:
	rm -rf bin/ *.dat