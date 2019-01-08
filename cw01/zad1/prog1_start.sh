#!/bin/bash

echo --------------------------------------------------------------------
echo Running prog 1 - Ackermann and saving result is file >> results.txt

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
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make ackermann
./main 3 14 >> results.txt

echo Running ackermann with compiler optimization O3
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make ackermann
./main 3 14 >> results.txt

echo Finishing prog 1
echo ------------------------------------------- >> results.txt
echo --------------------------------------------------------------------