#!/bin/bash

x=2
y=4

let mul=$x*$y # Use let for arithmetic operations
echo "$x*$y=$mul"
echo "$x+$y=$(($x+$y))"
