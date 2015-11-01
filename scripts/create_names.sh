#!/bin/bash

## This script generate a file with the proper number of root files

## Count the number of files
numfiles=$(ls |wc -l)

##save the name of the file
name=$(find -type f -print | grep '_1.root')

## extrat the relevant part of the string
a1=${name%_*}

a2=${a1#*/}

## Display if some files are missing from the list

seq "$numfiles" | while read -r i; do
    [[ -f $a2"_$i.root" ]] || echo $a2"_$i.root is missing"
done

for ((a=1; a < numfiles-1 ; a++))
do
   echo $a2"_$a.root"   
done
