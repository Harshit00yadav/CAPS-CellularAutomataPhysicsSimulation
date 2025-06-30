#!/bin/sh

if [ ! -d "./build" ]; then
	echo "making build directory"
	mkdir build
fi
if [ -d "./build" ]; then
	echo "./build directory exists."
	gcc -o build/app src/main.c -lSDL2
	echo "Build complete"
fi
if [[ "$1" == "run" ]]; then
	./build/app
else
	echo "Done."
fi
