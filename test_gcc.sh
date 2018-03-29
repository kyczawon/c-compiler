#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi


echo "    -----   Force Builidng Compiler    -----    "
echo " "
# make -B all
echo " "

    echo "  --   Performing Test   --  "
    tmp="test/tmp"
    rm ${tmp}

    mips-linux-gnu-gcc -S ./test/test.c -o ./test/test3.s

    mips-linux-gnu-gcc -pedantic -std=c89 -O0 -S ./test/test.c -o ./test/test_ref.s
    
    mips-linux-gnu-gcc -Wall -static -o test/tmp test/test3.s ./test/test_driver.c
    
    qemu-mips test/tmp

    GOT=$?

    if [[ $GOT -eq 0 ]] ; then 
        echo "Test, Pass"
    else 
        echo "Test, Fail, Expected 0, got $GOT"
    fi 

    echo " "
    

    

        


     
