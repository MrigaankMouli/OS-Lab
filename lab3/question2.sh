#!/bin/bash

echo "Enter the value of n"
read n

x=0
count=0
echo "The first $n odd numbers are"
while [ $count -lt $n ]
do 
	flag=$((x%2))
	if [ $flag -eq 1 ]
	then 
		echo "$x"
		count=$((count+1))
	fi
x=$((x+1))
done


