#pragma once

#include "../objects/block.hpp"
#include <memory>
#include <vector>
#include <sstream>
using namespace std;

inline class World {
    private:
        // TODO: gain sanity back
        stringstream convert;
    public:
        vector<unique_ptr<Block>>Blocks;
        void createBlockAt(int x, int y, Block* interactable);
        void createInteractibleAt(int x, int y, Block &interactable);
} World;