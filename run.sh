#/bin/bash

if [[ $1 = "-h" || $1 = "--help" ]]
then
    echo "Usage: ./run.sh -[h] <.min program>"
    echo "Options:"
    echo "\t -h | --help \t Print this help message"
    exit
fi

if [ ! -f ./src/minilang.out ]
then
    make
fi

./src/minilang.out $@
