#!/bin/bash

# USE WHEN READING RANDOM VALUES FROM A FILE
#rm -rf rand_file.txt

# touch rand_file.txt
# echo Generating rand numbers
# for i in $(seq 400000000 );
# do
#     shuf -i 0-100 -n 1 >> rand_file.txt
# done

echo ---------------------------------------------------------------------
echo Running prog 3 - Matrix add and saving result is file >> results.txt

echo Running file Matrix add with no compiler optimization
make clean
echo NO OPTIMIZATION >> results.txt
OPT=-O0 make matrix
./main 60000 10000 60000 10000 >> results.txt

echo Running file Matrix add with O1 compiler optimization
make clean
echo O1 OPTIMIZATION >> results.txt
OPT=-O1 make matrix
./main 60000 10000 60000 10000 >> results.txt

echo Running file Matrix add with O2 compiler optimization
make clean
echo O2 OPTIMIZATION >> results.txt
OPT=-O2 make matrix
./main 60000 10000 60000 10000 >> results.txt

echo Running file Matrix add with O3 compiler optimization
make clean
echo O3 OPTIMIZATION >> results.txt
OPT=-O3 make matrix
./main 60000 10000 60000 10000 >> results.txt

echo Finishing prog 3
echo ------------------------------------------- >> results.txt
echo --------------------------------------------------------------------



