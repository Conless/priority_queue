#!/bin/bash
prefix="./data/"
name=("one" "two" "three" "four" "five")

test() {
    cppfile=$prefix${name[$1-1]}"/code.cpp"
    outfile=$prefix${name[$1-1]}"/answer.txt"
    cp -f $cppfile "./src/main.cpp"
    ./scripts/build.sh
    time valgrind ./bin/priority_queue_run -s --leak-check=full >test.out
    diff test.out $outfile
}

test 1
