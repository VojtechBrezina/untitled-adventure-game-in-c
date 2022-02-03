#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

gcc -Wall -pedantic -iquote . src/main.c -o build/game