#!/bin/bash

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

cases="./test/test_cases"
results="./test/test_results"
mkdir -p "$results"

echo " "
echo "    -----   Force Builidng Compiler    -----    "
make -B all
echo " "

 COUNT=0
 PASSED=0

for testfile in ${cases}/* ; do 

    testname=${testfile:18}
    testdir=${results}/${testname}
    mkdir -p "$testdir"

    rm ${testdir}/${testname} 2>/dev/null

    $compiler -S ${testfile}/${testname}.c -o ${testdir}/${testname}.s

    mips-linux-gnu-gcc -pedantic -std=c89 -O0 -S ${testfile}/${testname}.c -o ${testdir}/${testname}_ref.s
    
    mips-linux-gnu-gcc -static -o ${testdir}/${testname} ${testdir}/${testname}.s ${cases}/${testname}/${testname}_driver.c

    timeout 2 qemu-mips ${testdir}/${testname}

    GOT=$?
   

    if [[ $GOT -eq 0 ]] ; then 
        echo "$testname, Pass"
        ((COUNT++))
        ((PASSED++))
    elif [[ $GOT -eq 124 ]] ; then 
        echo "$testname, Fail, Timeout exception"
        ((COUNT++))
    else 
        echo "$testname, Fail, Expected 0, got $GOT"
        ((COUNT++))
    fi 

    echo " "
    
done

echo "Passed $PASSED out of $COUNT tests"
    

        


     
