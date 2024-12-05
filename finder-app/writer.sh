#!/bin/bash

if [ $# -lt 2 ]
then
    echo "NOK: Incorrect number of arguments."
    echo "Arguments must be passed as per below order:"
    echo "  1. File Path."
    echo "  2. String to be searched in the given file path."
    exit 1
else
    filePath="$1"
    echo "file path: ${filePath}"
    writestr="$2"
    echo "str: ${writestr}"     

    WRITEDIR=/tmp/aeld-data
    if [[ -d "$WRITEDIR" ]]
    then
        echo "OK: dir present" # directory present
    else        
        result0=$(mkdir ${WRITEDIR})  # create directory if not exists                        
        result0=$(chmod 777 ${WRITEDIR})
        echo "result 0 : $?"
    fi

    if [ ${#writestr} == 0 ]
    then
        echo "NOK: write cannot proceed due to empty string."
        exit 0
    else        
        echo "OK: Not empty string, proceeding with write."

        if [ -f ${filePath} ]
        then
            result1=$(echo "" > ${filePath}) # overwrite file with empty string
            echo "result 1 : $?"
        else
            DIR="$(dirname "${filePath}")"
            if [[ -d "$DIR" ]]
            then
                echo "OK: dir present" # directory present
            else        
                result2=$(mkdir ${DIR})  # create directory if not exists                        
                result2=$(chmod 777 ${DIR})
                echo "result 2 : $?"
            fi
            result3=$(touch ${filePath}) # create empty file
            echo "result 3 : $?"
        fi 

        result4=$(echo ${writestr} > ${filePath}) # overwrite file with given string
    fi

    if [ $? -eq 0 ]
    then
        echo "Success: file write completed."
        exit 0
    else
        echo "Failure: couldnot perform file write."
        exit 1
    fi
fi

