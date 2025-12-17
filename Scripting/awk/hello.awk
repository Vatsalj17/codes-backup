#!/bin/awk -f

function add(x, y) {
    print x+y
}

#begin
BEGIN{
    print "Hello World!"
    name = "Vatsal"
    num = 10
    arr[0] = 0
    arr[1] = 1

    marks["english"] = "too bad"
    marks["maths"] = 60

    #for loop
    for(subject in marks) 
        print "Marks in " subject, marks[subject]

    for (i = 0; i < 10; i++)
        print i

    #while loop
    count = 5
    while (count < 10) {
        print count
        count++
    }
}

#Patter and action
{}

#End
END{
    add(arr[0], arr[1])
    print "Bye"
}
