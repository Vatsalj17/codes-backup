#!/bin/bash

: << 'comment'
file="/home/Learner/Codes/C/Beginner C/NewWords.txt"

n=1
for i in $(cat "$file")
do 
    echo "$n - $i"
    (( n++ ))
done

while read myvar
do 
    echo "The word is $myvar"
done < "$file"
comment

#Extracting data from a csv file
while IFS="," read val1 val2 val3
do 
    echo "The id is $val1. The name is $val2. The age is $val3"
done < test.csv

#or
#To ignore the first line
cat test.csv | awk 'NR!=1 {print}' | while IFS="," read val1 val2 val3
do 
    echo "The id is $val1. The name is $val2. The age is $val3"
done 
