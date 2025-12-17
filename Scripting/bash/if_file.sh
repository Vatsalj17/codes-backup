#!/bin/bash

read -p "Enter the file name: " file

if [[ -f $file ]]
then 
    echo "The file exist"
fi 

if [[ ! -f $file ]] 
then 
    echo "File does not exists"
fi 

read -p "Enter the directory name: " dir

if [[ -d $dir ]]  
then 
    echo "The dircectory exists"
else 
    echo "This directory does not exists"
fi
