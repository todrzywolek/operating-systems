#!/bin/bash

echo Removing old results
rm -rf results.txt

echo Creating new results file
touch results.txt

sh prog1_start.sh
sh prog2_start.sh
sh prog3_start.sh
sh prog4_start.sh

Finished all