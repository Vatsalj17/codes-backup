#!/bin/bash

str="Hello World!"

# Length of a string 
echo "Length of str is ${#str}"

# Printing string in Uppercase
echo "Uppercase: ${str^^}"

# Printing string in Lowercase
echo "Lowercase: ${str,,}"

# Replace a patterns in string
echo "Replaced world with username: ${str/World/$(whoami)}"

# Slicing a string
echo "Sliced string from 3rd index to 5 characters forward: ${str:3:5}"
