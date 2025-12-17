#!/bin/bash

mkdir folder_for_files
cd folder_for_files

for i in {1..10}
do 
    touch file$i 
done
