#!/bin/bash

# Check if both arguments are provided
if [ -z "$1" ] || [ -z "$2" ]; then
    echo "Error: Both filepath and text string need to be provided."
    exit 1
fi

# Assigning arguments to variables for better readability
writefile="$1"
writestr="$2"

# Extracting directory path from writefile
dirpath=$(dirname "$writefile")

# Create directory if it does not exist
if [ ! -d "$dirpath" ]; then
    mkdir -p -- "$dirpath"
fi

# Attempt to write $writestr into $writefile
echo "$writestr" > "$writefile"

# Check if writing was successful or not
if [ $? -eq 0 ]; then
    echo "Text has been successfully written to $writefile."
else 
    echo "Error: Could not write to $writefile."
    exit 1
fi 