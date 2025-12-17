#!/bin/bash

num=10
name=Vatsal
decimal=5.10

echo "the number is $num"
echo "the name is $name"
echo "the decimal is $decimal"

hname=$(hostname)
uname=$(whoami)
path=$(pwd)
items=$(ls)

echo "This os named $hname is owned by $uname who is working in $path with $items files"

# Variables can also be changed during runtime
name=Learner

# To assign Constant Variables in bash 
readonly var=Const_Var # This variable can't be changed
