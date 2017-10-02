#!/bin/bash

#Testing the output.
clear
gcc -Wall merge.c -o a.out
./a.out |gnomon

echo (((a+b)*(~c))>(~d))>e -n

rm a.out