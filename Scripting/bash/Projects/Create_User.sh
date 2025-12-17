#!/bin/bash

if [[ $USER != root ]] 
then 
    echo "Access Denied"
    exit 1
fi 

if [[ $# == 0 ]]
then 
    echo "Please Provide a Username"
    exit 1
fi 

User=$1
shift

useradd $User
pass=$( tr -dc a-zA-Z0-9 </dev/urandom | head -c 10 )
echo "$User:$pass" | chpasswd

echo "User Created Succesfully"
echo "Username: $User"
echo "Comment: $@"
echo "Password: $pass"
echo "Host: $HOSTNAME"
echo
