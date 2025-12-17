#!/bin/bash

echo "Choose an option amongst these --"
echo "a) See current date and time"
echo "b) See username"
echo "c) Check the Path" 
echo "d) List all files"
echo "e) See the hostname"

read -p "Make Selection: " choice

case $choice in 
    a) date;;
    b) whoami;;
    c) pwd;;
    d) ls;;
    e) hostname;;
    *) echo "Invalid Selection!"
esac
