#!/bin/bash

echo "Enter the value of a, b and c"
read a
read b
read c


d=$(((b * b) - (4 * a * c)))
sqrt_d=$(echo "scale=0;sqrt($d)" | bc -l)
case $d in

-*)
	echo "The roots are imaginary"
	;;
0)
	root=$(((-1 * b) / (2 * a) ))
	echo "The root is $root"
	;;
*)
	root1=$((((-1 * b) - sqrt_d) / (2 * a))) 
	root2=$((((-1 * b) + sqrt_d) / (2 * a)))
	echo "The roots are $root1 and $root2"
esac
