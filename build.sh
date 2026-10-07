
if [ ! -d "build" ]; then
	mkdir build
fi


TARGET=./build/mathgraph
OPTIONS=-"std=c11 -g -Wall -Wpedantic"

gcc $OPTIONS -o $TARGET src/main.c src/lexer.c src/lexer.h
