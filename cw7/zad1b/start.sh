#!/bin/bash

make

PRODUCERS_NUM=1
CONSUMERS_NUM=8
BUFFER_SIZE=100
SOURCE_FILE=arguments.txt

# reference length, each line from text is compared with this length
REFERENCE_LENGTH=2

# instruction how source file lines need to be compared with reference length
#   allowed values:
#       1 - print source file lines greater than reference length
#       2 - print source file lines equal reference length
#       3 - print source file lines lower than reference length
COMPARE_MODE=2

# setup program logging level
#   allowed values:
#       1 - info logging level - prints lines that match compare mode
#       2 - debug logging level - prints status and reports work for all program threads
LOGGING_LEVEL=2

# program finish condition
#   allowed values:
#       nk > 0 - program finishes after nk seconds, 
#       nk = 0 - program finishes after reaching end of source file
nk=0

./main $PRODUCERS_NUM $CONSUMERS_NUM $BUFFER_SIZE $SOURCE_FILE $REFERENCE_LENGTH $COMPARE_MODE $LOGGING_LEVEL $nk