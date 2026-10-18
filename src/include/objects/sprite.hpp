#pragma once

#include "raylib.h"
#include <vector>
#include <iostream>
using namespace std;

struct Sprite {
    float x, y, rotation, size;
    Texture2D texture;
};

inline class Sprites {
    public:
    vector<Sprite> sprites;
    void add(Sprite sprite) {
        sprites.push_back(sprite);
    }
    void draw() {
        for (int i = 0; i < sprites.size(); i++) {
            Sprite cSprite = sprites[i];
            DrawTextureEx(cSprite.texture, {cSprite.x, cSprite.y}, cSprite.rotation, cSprite.size, WHITE);
        }
    }
} Sprites;