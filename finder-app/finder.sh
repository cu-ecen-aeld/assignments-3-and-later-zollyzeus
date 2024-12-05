#!/bin/bash



if [ $# -lt 2 ]
then
    echo "NOK: Incorrect number of arguments."
    echo "Arguments must be passed as per below order:"
    echo "  1. File Directory Path."
    echo "  2. String to be searched in the given directory path."
    exit 1
else
    filesdir="$1"
    echo "dir: ${filesdir}"
    searchstr="$2"
    echo "str: ${searchstr}"

    if [[ -d "$filesdir" ]]
    then
        echo "OK: dir present"
        fileCount=$(find "$filesdir" -type f | wc -l)        
        echo "file count : ${fileCount}"
        if [ ${#searchstr} == 0 ]
        then
            echo "NOK: Search cannot proceed due to empty string."
            exit 0
        else
            echo "OK: Not empty string, proceeding with search."
            matchCount=$(grep -r "$searchstr" "$filesdir")            
            echo "match count : ${matchCount}"
            if [ ! ${#matchCount} == 0  ]
            then
                echo "The number of files are ${fileCount} and the number of matching lines are ${fileCount}"
                exit 0
            else
                echo "Failure: couldnot find any reference of ${searchstr} under ${filesdir}"
                exit 1
            fi
        fi
    else
        echo "NOK: Directory path doesnot exist."
        exit 1
    fi
fi

