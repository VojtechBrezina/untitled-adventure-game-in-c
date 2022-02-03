#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

gcc -Wall -pedantic -iquote . src/main.c -O2 -o build/game