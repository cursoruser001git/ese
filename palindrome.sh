#!/bin/bash

read -p "Enter a string: " input

# Reverse the input
reversed=$(echo "$input" | rev)

# Compare
if [ "$input" == "$reversed" ]; then
  echo "The string is a palindrome."
else
  echo "The string is not a palindrome."
fi
