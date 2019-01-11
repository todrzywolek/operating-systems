#!/bin/bash

make

# NUM_OF_CLIENTS - number of clients that want to cut
NUM_OF_CLIENTS=5

# CUTS_PER_CLIENT - number of cuts each client want to have in barber
CUTS_PER_CLIENT=5

./client $NUM_OF_CLIENTS $CUTS_PER_CLIENT