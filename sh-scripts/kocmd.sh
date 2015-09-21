#!/bin/bash

# Kill command(program).
# Example:
#    kocmd python test.py
# List args(http://tldp.org/LDP/abs/html/internalvariables.html#ARGLIST)

# kocmd() {
name=""
index=1

for arg in "$*"
do
    if [ 1 -eq $index ]; then
        name+="$arg"
    else
        name+=" $arg"
    fi
    index+=1
done

kill -9 $(ps -aux | grep "$name" | awk '{print $2}' | head -n 1)
# }