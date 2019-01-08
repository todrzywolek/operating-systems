#!/bin/bash

MATRIX_COLS=60000
MATRIX_ROWS=10000

echo Running Matrix add program >> results.txt

# Static linking
echo Static library linking >> results.txt
echo
echo No compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make main_a
./main_a $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make main_a
./main_a $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make main_a
./main_a $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make main_a
./main_a $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt
echo
echo ----------------------------------------------------------------------------- >> results.txt
echo -----------------------------------------------------------------------------

# Shared lib
echo Shared library linking >> results.txt
echo
echo No compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make main_so
./main_so $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make main_so
./main_so $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make main_so
./main_so $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make main_so
./main_so $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt
echo
echo ----------------------------------------------------------------------------- >> results.txt
echo -----------------------------------------------------------------------------

# Dynamic lib
echo Dynamic library linking >> results.txt
echo
echo No compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make dll_main
./dll_main $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make dll_main
./dll_main $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make dll_main
./dll_main $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt

echo O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make dll_main
./dll_main $MATRIX_COLS $MATRIX_ROWS $MATRIX_COLS $MATRIX_ROWS >> results.txt
echo
echo ----------------------------------------------------------------------------- >> results.txt
echo -----------------------------------------------------------------------------