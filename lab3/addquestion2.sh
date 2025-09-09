#!/bin/bash

echo "$# numbers are given by user"

sum=0

while [ $# != 0 ]
do 
	sum=$((sum + $1))
	shift
done

echo "The sum of the numbers entered by the user is $sum"


