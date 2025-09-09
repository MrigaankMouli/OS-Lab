#!/bin/bash

echo "Enter the word"
read word

rev_word=$(echo "$word" | rev)

if [ $rev_word = $word ]
then
	echo "$word is a palindrome"
else
	echo "$word is not a palindrome"
fi

