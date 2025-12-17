#!/bin/bash

read -p "Enter the site name:- " site

echo "Checking..."
ping -c 1 $site &> /dev/null

if [[ $? -eq 0 ]] # $? :- tells that if last entered command was successful or not
then 
    echo "Connection successful with the site $site"
else 
    echo "Connection failed!"
fi
