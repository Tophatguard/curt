
_phony: clean always game run

always:
	mkdir -p build

game: src/main.cpp
	g++ -g -I src/include src/main.cpp src/include/*/*.cpp -lraylib -o build/game

run: build/game
	./build/game

clean:
	rm -rf build