
if [ ! -d "build" ]; then
	mkdir build
fi

gcc -g -o ./build/mathgraph src/main.c src/lexer.c src/lexer.h
