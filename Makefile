all: build_main

build_main:
	g++ -o main main.cpp Button.cpp Transformed.cpp -lsfml-system -lsfml-window -lsfml-graphics
