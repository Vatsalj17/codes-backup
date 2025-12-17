BEGIN{
    print "Start of file"
}
{
    if($NF>50000)
        $(NF+1)=High
    else
        $(NF+1)=Low

    print $0
}
END{
    print "End of the file"
}
