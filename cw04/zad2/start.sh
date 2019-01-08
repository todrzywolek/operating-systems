#!/bin/bash

make

# L - num of signals parent should send to child
L=4

# Type - signal send mode
#   1 - sends SIGUSR1 and SIGUSR2 to child process using 'kill' asynchronously
#   2 - sends SIGUSR1 and SIGUSR2 to child process using 'kill' after receiveing confirmation from child
#   3 - sends SIGRTMIN and (SIGRTMIN+1) to child process using 'kill' after receiveing confirmation from child
Type=1

./parent $L $Type