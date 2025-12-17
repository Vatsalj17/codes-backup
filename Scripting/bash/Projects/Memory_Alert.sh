#!/bin/bash

occupied=$( df -h | grep sda2 | awk '{print $5}' | tr -d % )
limit=60

to=vatsal.unix17@gmail.com

if [[ $occupied -gt limit ]]
then 
    echo "The space is almost full:- $occupied%" | mail -s "MEMORY FULL" $to
else 
    echo "Enough space left"
fi
