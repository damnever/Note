#!/bin/bash

mkgopath() {
    export GOPATH=${GOPATH}:$(pwd)
    echo "GOPATH=${GOPATH}"
}

mkgoproject() {
    if [[ $# -eq 0 ]]; then
        echo "ERROR: project name is required!"
        return
    fi
    mkdir -p $1/{src,pkg,bin}
    cd $1
    mkgopath
    cd src/
    echo "CURENT_DIR=$(pwd)"
}
