#include "world.hpp"
#include "../logger/logger.hpp"
#include <iostream>
using namespace std;

void World::createBlockAt(int x, int y, Block* interactable) {
    Logger.log("created Object!");
    interactable->x = x;
    interactable->y = y;
    cout << "r: " << interactable->path << endl
         << "x: " << interactable->x << endl
         << "y: " << interactable->y << endl;
    Blocks.emplace_back(interactable);
}