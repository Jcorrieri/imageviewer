#!/usr/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Usage: ./run.sh <image.ext>"
	exit 1
fi

filename_ext="main.cpp"
arg=$1
filename=${filename_ext%%'.'*}

outname="sfml-app"

g++ -c -Wall "$filename_ext"
g++ "$filename.o" -o "$outname" -lsfml-graphics -lsfml-window -lsfml-system

./"$outname" "$arg"
