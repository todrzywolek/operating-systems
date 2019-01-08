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

# tests
FILE1=1.tt
FILE2=2.tt
FILE3=3.tt
FILE4=4.tt
FILE5=5.tt
FILE6=6.tt
FILE7=7.tt
FILE8=8.tt

SIZE1=4 10000
SIZE2=512 500
SIZE3=4096 15
SIZE4=8192 10
SIZE5=4 20000
SIZE6=512 800
SIZE7=4096 20
SIZE8=8192 20

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
	rm -rf bin/ *.tt