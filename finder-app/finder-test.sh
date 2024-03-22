#!/bin/sh
# Tester script for assignment 1 and assignment 2
# Author: Siddhant Jajoo

set -e
set -u

NUMFILES=10
WRITESTR=AELD_IS_FUN
WRITEDIR=/tmp/aeld-data
username=$(cat /etc/finder-app/conf/username.txt) # Updated path

if [ $# -lt 3 ]; then
    echo "Using default value ${WRITESTR} for string to write"
    if [ $# -lt 1 ]; then
        echo "Using default value ${NUMFILES} for number of files to write"
    else
        NUMFILES=$1
    fi  
else
    NUMFILES=$1
    WRITESTR=$2
    WRITEDIR=/tmp/aeld-data/$3
fi

MATCHSTR="The number of files are ${NUMFILES} and the number of matching lines are ${NUMFILES}"

echo "Writing ${NUMFILES} files containing string ${WRITESTR} to ${WRITEDIR}"

# Use the "writer" utility assuming it's in the PATH
for i in $(seq 1 $NUMFILES); do
    writer "$WRITEDIR/${username}$i.txt" "$WRITESTR" # Assume 'writer' is in PATH
done

OUTPUTSTRING=$(finder.sh "$WRITEDIR" "$WRITESTR" | tee /tmp/assignment4-result.txt) # Assume 'finder.sh' is in PATH

# Remove temporary directories
rm -rf /tmp/aeld-data

set +e
echo ${OUTPUTSTRING} | grep "${MATCHSTR}"

if [ $? -eq 0 ]; then
    echo "Success"
    exit 0
else
    echo "Failed: expected ${MATCHSTR} in ${OUTPUTSTRING} but ..."
fi
