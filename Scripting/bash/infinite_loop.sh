#!/bin/bash

n=0
while true
do 
    touch file$n
    (( n++ ))
done
