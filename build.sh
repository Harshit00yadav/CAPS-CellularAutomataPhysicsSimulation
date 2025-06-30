#!/bin/sh

gcc -o build/app src/main.c -lSDL2
echo "Build complete"
if [[ "$1" == "run" ]]; then
	./build/app
else
	echo "Done."
fi
