#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

cases="./test/test_cases"
results="./test/test_results"
mkdir -p "$results"

echo "    -----   Force Builidng Compiler    -----    "
echo " "
make -B all
echo " "

for testfile in ${cases}/* ; do 

    testname=${testfile:18}
    testdir=${results}/${testname}
    mkdir -p "$testdir"

    echo "  --   Performing ${testname} Test   --  "

    mips-linux-gnu-gcc -S ${testfile}/${testname}.c -o ${testdir}/${testname}.s
    
    mips-linux-gnu-gcc -static -o ${testdir}/${testname} ${testdir}/${testname}.s ${cases}/${testname}/${testname}_driver.c
    
    qemu-mips ${testdir}/${testname}

    GOT=$?

    if [[ $GOT -eq 0 ]] ; then 
        echo "$testname, Pass"
    else 
        echo "$testname, Fail, Expected 0, got $GOT"
    fi 

    echo " "
    
done

    

        


     
