#!/bin/bash

# USE WHEN READING RANDOM VALUES FROM A FILE
#rm -rf rand_file.txt

# touch rand_file.txt
# echo Generating rand numbers
# for i in $(seq 400000000 );
# do
#     shuf -i 0-100 -n 1 >> rand_file.txt
# done

echo Compiling program
make matrix

echo Running
./main 60000 10000 60000 10000



