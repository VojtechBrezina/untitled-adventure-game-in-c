#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

gcc -Wall -pedantic -DNDEBUG -iquote . src/*.c -O2 -o build/game && \
gcc -g -fsanitize=address -iquote . src/*.c -Og -o build/game-d >/dev/null 2>/dev/null
# ^ if succesful, create a debug build