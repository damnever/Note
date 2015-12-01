#!/bin/bash

#
# TODO: now, just a simple version, open terminal and show todo.
#
# MORE: *somethings should improve, rather than vim*
#  support command:
#    - todoadd <num>
#    - todoremove <num>
#    - todoupdate <num>
#    XXX

_FILE=~/.dsh/todo.md


todo() {
    columns="$(tput cols)"
    gtd="GET THINGS DONE!!!"
    printf "\n%*s\n" $(( (${#gtd} + columns) / 2)) "$gtd"
    printf "%${columns}s\n\n" | tr " " "-"
    cat "${_FILE}"
    echo
    printf "%${columns}s\n" | tr " " "-"
}

todoedit() {
    vim "${_FILE}"
}

# todoadd() {
    # read content
    # echo "" >> "${_FILE}"
    # echo "${content}" >> "${_FILE}"
# }

# todoremove() {
# }

# todoupdate() {
# }

todo
