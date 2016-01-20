#!/bin/bash

# TODO, good enough.
# add to .bashrc `. ./path/to/todo.sh`

_FILE=~/.dsh/todo.md


todo() {
    columns="$(tput cols)"
    gtd="GET THINGS DONE! IF IT HURTS, DO IT MORE AND OFTEN!"
    printf "\n%*s\n" $(( (${#gtd} + columns) / 2)) "$gtd"
    printf "%${columns}s\n\n" | tr " " "-"
    cat "${_FILE}"
    echo
    printf "%${columns}s\n" | tr " " "-"
}

todoedit() {
    vim "${_FILE}"
}


todo
