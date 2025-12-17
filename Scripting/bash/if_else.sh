#!/bin/bash

read -p "Enter you marks: " marks
if [[ $marks -gt 40 ]] 
then
    echo "You are Pass"
else
    echo "You are Fail"
fi
