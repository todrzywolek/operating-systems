#!/bin/bash

iterations=1000000
size=10000
buffer=100

echo ---------------------------------------------------------------------
echo Running prog 4 - Array copy and saving result is file >> results.txt

echo Running file Array copy with no compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make array_copy
./main $iterations $size $buffer >> results.txt

echo Running file Array copy with O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make array_copy
./main $iterations $size $buffer >> results.txt

echo Running file Array copy with O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make array_copy
./main $iterations $size $buffer >> results.txt

echo Running file Array copy with O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make array_copy
./main $iterations $size $buffer >> results.txt

echo Finishing prog 4
echo ------------------------------------------- >> results.txt
echo --------------------------------------------------------------------