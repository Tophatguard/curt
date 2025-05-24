
_phony: game run

game: src/main.cpp
	g++ src/main.cpp -lraylib -o build/game

run: build/game
	./build/game