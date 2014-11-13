#!/bin/sh
#!/bin/bash

typeset -i tests=0

function try {
    let tests+=1;
    description="$1";
}

function assert {
    if [[ "$1" == "$2" ]]; then
        printf "\033[32m.\033[0m"
    else
        printf "\033[31m\nFAIL: $description\033[0m: '$1' != '$2'\n";
        exit 1
    fi
}

try "Execute"
    result=`./stmr --eval "alfred"` 2> /dev/null
    assert $result "alfr"

try "Execute: short flag"
    result=`./stmr -e "alfred"` 2> /dev/null
    assert $result "alfr"

try "Execute: no arguments"
    code=0
    ./stmr --eval 2> /dev/null || code=$?
    assert $code 1

try "Execute: no arguments: short flag"
    code=0
    ./stmr -e 2> /dev/null || code=$?
    assert $code 1

try "Help"
    code=0
    ./stmr --help > /dev/null 2>&1 || code=$?
    assert $code 0

try "Help: short flag"
    code=0
    ./stmr -h > /dev/null 2>&1 || code=$?
    assert $code 0

try "Version"
    code=0
    ./stmr --version > /dev/null 2>&1 || code=$?
    assert $code 0

try "Version: short flag"
    code=0
    ./stmr -v > /dev/null 2>&1 || code=$?
    assert $code 0

echo "\033[32m\n(✓) Passed $tests assertions without errors\033[0m";

exit 0
