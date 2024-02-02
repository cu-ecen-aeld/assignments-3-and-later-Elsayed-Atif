#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 filesdir searchstr"
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "Error: $1 is not a directory"
    exit 1
fi

files=$(find "$1" -type f)
num_files=$(echo "$files" | wc -l)

if [ "$num_files" -eq 0 ]; then
    echo "Error: no files found in $1"
    exit 1
fi

num_matches=$(grep -r "$2" "$1" | wc -l)

echo "The number of files are $num_files and the number of matching lines are $num_matches"