#!/bin/bash

echo "first argument is $1"
echo "second argument is $2"

echo "all the arguments are $@"
echo "total number of arguments are $#"

for val in $@
do 
    echo "The argument is $val"
done

#to shift arguments 
shift
echo "Argurments after shifting: $@"
