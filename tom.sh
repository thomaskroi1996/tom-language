#!/bin/bash
# this checks if a filename is provided
if [ -z "$1" ]; then
    echo "Usage: ./tom <filename.tom>"
    exit 1
fi

# get filename, extension not needed
NAME=$(basename "$1" .tom)

# first we transpile to cpp
if ./tom_transpiler "$1" "$NAME.cpp"; then
    # then we build cpp file to binary
    if g++ -O3 "$NAME.cpp" -o "$NAME"; then
        rm "$NAME.cpp"
        echo "successfully compiled: ./$NAME"
    else
        echo "error: g++ failed to compile the generated code."
        exit 1
    fi
else
    echo "error: the engine failed or was not found."
    exit 1
fi
