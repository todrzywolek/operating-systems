#!/bin/bash

echo Removing old results
rm -rf results.txt

echo Creating new results file
touch results.txt
echo Ackermann results >> results.txt

echo Running ackermann with no compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make ackermann
./main 3 14 >> results.txt

echo Running ackermann with compiler optimization O1
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make ackermann
./main 3 14 >> results.txt

echo Running ackermann with compiler optimization O2
make clean
echo \nO2 OPTIMIZATION >> results.txt
OPT=-O2 make ackermann
./main 3 14 >> results.txt

echo Running ackermann with compiler optimization O3
make clean
echo \nO3 OPTIMIZATION >> results.txt
OPT=-O3 make ackermann
./main 3 14 >> results.txt

echo \n\nFile read/write results >> results.txt

echo Running file read/write with no compiler optimization
make clean
echo \nNO OPTIMIZATION >> results.txt
OPT=-O0 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O1 compiler optimization
make clean
echo \nO1 OPTIMIZATION >> results.txt
OPT=-O1 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O2 compiler optimization
make clean
echo \nO2 OPTIMIZATION >> results.txt
OPT=-O2 make file_rw
./main 500000 >> results.txt

echo Running file read/write with O3 compiler optimization
make clean
echo \nO3 OPTIMIZATION >> results.txt
OPT=-O3 make file_rw
./main 500000 >> results.txt