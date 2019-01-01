#!/bin/bash
touch rand_file.txt
for i in `seq 1 10`;
do
    shuf -i 0-100 -n 1 >> rand_file.txt
done  