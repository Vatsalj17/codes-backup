#!/bin/bash

function fun {
    echo hi
}

fun

#or 
 
fun2() {
    echo hello
}

fun2

#--------------------------------------------------------------

add() {
    a=$1
    b=$2
    let sum=$a+$b 
    echo "The sum of $a and $b is $sum"
}

add 1 3 
