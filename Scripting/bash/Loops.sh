#!/bin/bash

for i in 1 2 3; do
	echo $i
done
#or
#for i in {1..5}
#do
#    echo $i
#done

for i in sham raju baburao; do
	echo $i
done

arr=(12 56 zzzz ":)")

len=${#arr[*]}

for ((i = 0; i < $len; i++)); do
	echo "arr[$i] = ${arr[$i]}"
done

#while loop
count=0
num=10

while [[ $count -lt $num ]]; do
	echo "count = $count, num = $num"
	let count++
done

#until loop
a=10
until [[ $a -eq 1 ]]
do 
    echo "This loop will stop, a = $a"
    a=`expr $a - 1`
done
