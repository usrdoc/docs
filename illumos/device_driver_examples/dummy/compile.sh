#!/bin/bash

# To compile on a 64 bit illumos machine

gcc -D_KERNEL -m64 -mcmodel=kernel -c dummy.c
ld -r -o dummy dummy.o
