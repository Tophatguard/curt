#pragma once

#include <string>
#include "raylib.h"
#include "../global/assets.hpp"
using namespace std;

class Block {
    public:
        bool mined = false;
        char *image;
        int health = 3;
        float ogHealth = (float)health;
        Sound hitSound;
        // Stands for image Texture
        Texture2D imaget;
        Texture2D selectedImage;
        bool inffix = false;
        bool infhit1 = false, infhit2 = false;
        Texture2D break1;
        Texture2D break2;
        string path;
        // DO NOT USE plllEAASSee
        int x, y;
    Block(Texture2D image, Texture2D selectedImage);
    void collide(float& camx, float& camy, int WIDTH, int HEIGHT);
    void draw();
    void destroy();
    ~Block();
};

inline struct RegisteredBlocks {
    // TODO: create more blocks
    Block* rock() {
        return new Block(Assets.rock, Assets.rockSelected);
    }
    Block* grass() {
        return new Block(Assets.grass, Assets.grassSelected);
    }

} RegisteredBlocks;