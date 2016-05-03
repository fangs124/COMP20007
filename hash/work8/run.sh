#!/bin/bash
#
# COMP200007 Design of Algorithms 
# Test speed of different hash tables 
#
# Author: Andrew Turpin
# Thu  9 May 2013 06:48:03 EST
#

m=15667    # table size (prime)
nI=10000   # number of keys to generate for inserting
nS=100000  # number of keys to generate for searching
p=0        # base of skewness for search keys

file1=t3
file2=t4

for p in 0 0.1 0.01 0.001 0.0001 0.00001
do
    R --slave --args $nI $nS $p $file1 $file2 < dataGen.r  # generate data

        # run the four chaining tables
    for tableType in a c
    do
        for mtf in 0 1
        do
            for i in 1 2 3 4 5   # repeat each test 5 times
            do
                echo -n "$tableType$mtf $p "
                ./testHash $tableType $mtf $m $file1 $file2
            done
        done
    done

        # run the double hashing table
    for i in 1 2 3 4 5   # repeat each test 5 times
    do
        echo -n "d $p "
        ./testHash d 0 $m $file1 $file2
    done
done
