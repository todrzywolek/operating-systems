#!/bin/bash

RECORDS=6000
SIZE=512

./main generate dane2.dat $RECORDS $SIZE

./main copy dane2.dat dane2.dat.sys $RECORDS $SIZE sys
./main copy dane2.dat dane2.dat.lib $RECORDS $SIZE lib

./main sort dane2.dat.sys $RECORDS $SIZE sys
./main sort dane2.dat.lib $RECORDS $SIZE lib