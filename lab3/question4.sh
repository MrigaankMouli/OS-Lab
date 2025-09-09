#!/bin/bash

echo "Enter any number:"
read n

fact=1
x=$n
while [ $x -gt 0 ]
do 
	fact=$((fact*x))
	x=$((x-1))
done
echo "The factorial of $n is $fact"

