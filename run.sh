#/bin/bash

if [[ $1 = "-h" || $1 = "--help" ]]
then
    echo "Usage: ./run.sh -[ch] <.min program>"
    echo "Options:"
    echo "\t -c | --clean \t Clean the project after running"
    echo "\t -h | --help \t Print this help message"
    exit
fi

if [ ! -f ./src/minilang ]
then
    if [ ! -f build.sh ]
    then
	    echo "ERROR: Missing build.sh script"
	    exit
    fi
    ./build.sh > /dev/null
fi

if [[ $1 == "-c" || $1 == "--clean" ]]
then
    ./src/minilang $2
    make clean -C ./src &> /dev/null
else
    ./src/minilang $1
fi