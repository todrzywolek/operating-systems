CFLAGS = -Wall
CC = gcc

OBJECT=$(CC) $< -c -I include -o $@

main: bin/main.o \
		bin/generate.o \
		bin/utils.o \
		bin/sort.o \
		bin/my_copy.o \
		bin/time_counter.o
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
			 include/utils.h \
			 include/time_counter.h | bin
	$(OBJECT)

bin/my_copy.o: src/my_copy.c \
			 include/my_copy.h \
			 bin/utils.o \
			 include/utils.h \
			 include/time_counter.h | bin
	$(OBJECT)

bin/time_counter.o: src/time_counter.c \
			 include/time_counter.h | bin
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
	echo "Test 1 - copy $(M1)\nRozmiar: $(SIZE1)"    >> $@
	./$^ copy $(FILE1) $(FILE1).$(M1) $(SIZE1) $(M1) >> $@
	echo "\nTest 2 - copy $(M1)\nRozmiar: $(SIZE2)"  >> $@
	./$^ copy $(FILE2) $(FILE2).$(M1) $(SIZE2) $(M1) >> $@
	echo "\nTest 3 - copy $(M1)\nRozmiar: $(SIZE3)"  >> $@
	./$^ copy $(FILE3) $(FILE3).$(M1) $(SIZE3) $(M1) >> $@
	echo "\nTest 4 - copy $(M1)\nRozmiar: $(SIZE4)"  >> $@
	./$^ copy $(FILE4) $(FILE4).$(M1) $(SIZE4) $(M1) >> $@
	echo "\nTest 5 - copy $(M2)\nRozmiar: $(SIZE1)"  >> $@
	./$^ copy $(FILE1) $(FILE1).$(M2) $(SIZE1) $(M2) >> $@
	echo "\nTest 6 - copy $(M2)\nRozmiar: $(SIZE2)"  >> $@
	./$^ copy $(FILE2) $(FILE2).$(M2) $(SIZE2) $(M2) >> $@
	echo "\nTest 7 - copy $(M2)\nRozmiar: $(SIZE3)"  >> $@
	./$^ copy $(FILE3) $(FILE3).$(M2) $(SIZE3) $(M2) >> $@
	echo "\nTest 8 - copy $(M2)\nRozmiar: $(SIZE4)"  >> $@
	./$^ copy $(FILE4) $(FILE4).$(M2) $(SIZE4) $(M2) >> $@
	echo "\nTest 9 - copy $(M1)\nRozmiar: $(SIZE5)"  >> $@
	./$^ copy $(FILE5) $(FILE5).$(M1) $(SIZE5) $(M1) >> $@
	echo "\nTest 10 - copy $(M1)\nRozmiar: $(SIZE6)" >> $@
	./$^ copy $(FILE6) $(FILE6).$(M1) $(SIZE6) $(M1) >> $@
	echo "\nTest 11 - copy $(M1)\nRozmiar: $(SIZE7)" >> $@
	./$^ copy $(FILE7) $(FILE7).$(M1) $(SIZE7) $(M1) >> $@
	echo "\nTest 12 - copy $(M1)\nRozmiar: $(SIZE8)" >> $@
	./$^ copy $(FILE8) $(FILE8).$(M1) $(SIZE8) $(M1) >> $@
	echo "\nTest 13 - copy $(M2)\nRozmiar: $(SIZE5)" >> $@
	./$^ copy $(FILE5) $(FILE5).$(M2) $(SIZE5) $(M2) >> $@
	echo "\nTest 14 - copy $(M2)\nRozmiar: $(SIZE6)" >> $@
	./$^ copy $(FILE6) $(FILE6).$(M2) $(SIZE6) $(M2) >> $@
	echo "\nTest 15 - copy $(M2)\nRozmiar: $(SIZE7)" >> $@
	./$^ copy $(FILE7) $(FILE7).$(M2) $(SIZE7) $(M2) >> $@
	echo "\nTest 16 - copy $(M2)\nRozmiar: $(SIZE8)" >> $@
	./$^ copy $(FILE8) $(FILE8).$(M2) $(SIZE8) $(M2) >> $@
	echo "\nTest 17 - sort $(M1)\nRozmiar: $(SIZE1)" >> $@
	./$^ sort $(FILE1).$(M1) $(SIZE1) $(M1) >> $@
	echo "\nTest 18 - sort $(M1)\nRozmiar: $(SIZE2)" >> $@
	./$^ sort $(FILE2).$(M1) $(SIZE2) $(M1) >> $@
	echo "\nTest 19 - sort $(M1)\nRozmiar: $(SIZE3)" >> $@
	./$^ sort $(FILE3).$(M1) $(SIZE3) $(M1) >> $@
	echo "\nTest 20 - sort $(M1)\nRozmiar: $(SIZE4)" >> $@
	./$^ sort $(FILE4).$(M1) $(SIZE4) $(M1) >> $@
	echo "\nTest 21 - sort $(M2)\nRozmiar: $(SIZE1)" >> $@
	./$^ sort $(FILE1).$(M2) $(SIZE1) $(M2) >> $@
	echo "\nTest 22 - sort $(M2)\nRozmiar: $(SIZE2)" >> $@
	./$^ sort $(FILE2).$(M2) $(SIZE2) $(M2) >> $@
	echo "\nTest 23 - sort $(M2)\nRozmiar: $(SIZE3)" >> $@
	./$^ sort $(FILE3).$(M2) $(SIZE3) $(M2) >> $@
	echo "\nTest 24 - sort $(M2)\nRozmiar: $(SIZE4)" >> $@
	./$^ sort $(FILE4).$(M2) $(SIZE4) $(M2) >> $@
	echo "\nTest 25 - sort $(M1)\nRozmiar: $(SIZE5)" >> $@
	./$^ sort $(FILE5).$(M1) $(SIZE5) $(M1) >> $@
	echo "\nTest 26 - sort $(M1)\nRozmiar: $(SIZE6)" >> $@
	./$^ sort $(FILE6).$(M1) $(SIZE6) $(M1) >> $@
	echo "\nTest 27 - sort $(M1)\nRozmiar: $(SIZE7)" >> $@
	./$^ sort $(FILE7).$(M1) $(SIZE7) $(M1) >> $@
	echo "\nTest 28 - sort $(M1)\nRozmiar: $(SIZE8)" >> $@
	./$^ sort $(FILE8).$(M1) $(SIZE8) $(M1) >> $@
	echo "\nTest 29 - sort $(M2)\nRozmiar: $(SIZE5)" >> $@
	./$^ sort $(FILE5).$(M2) $(SIZE5) $(M2) >> $@
	echo "\nTest 30 - sort $(M2)\nRozmiar: $(SIZE6)" >> $@
	./$^ sort $(FILE6).$(M2) $(SIZE6) $(M2) >> $@
	echo "\nTest 31 - sort $(M2)\nRozmiar: $(SIZE7)" >> $@
	./$^ sort $(FILE7).$(M2) $(SIZE7) $(M2) >> $@
	echo "\nTest 32 - sort $(M2)\nRozmiar: $(SIZE8)" >> $@
	./$^ sort $(FILE8).$(M2) $(SIZE8) $(M2) >> $@

.PHONY: clean
clean:
	rm -rf bin/ *.dat