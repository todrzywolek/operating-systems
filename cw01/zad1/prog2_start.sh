#!/bin/bash

echo -------------------------------------------------------------------------
echo Running prog 2 - File read/write and saving result is file >> results.txt

echo Running file read/write with no compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make file_rw
./main 500000 >> results.txt

echo Finishing prog 2
echo ------------------------------------------- >> results.txt
echo --------------------------------------------------------------------