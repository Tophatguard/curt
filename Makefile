
_phony: clean always game run

always:
	mkdir build

game: src/main.cpp
	g++ src/main.cpp -lraylib -o build/game

run: build/game
	./build/game

clean:
	rm -rf build