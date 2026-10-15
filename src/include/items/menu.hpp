#pragma once

#include "raylib.h"

class menu {
    public:
        int x, y, width, height;
        Texture2D cornerTexture;
        Texture2D sideTexture;
        Texture2D centerTexture;
        Texture2D sideYTexture;
        bool destroyed = false;
        menu(int x, int y, int width, int height, Texture2D corner, Texture2D side, Texture2D sideY, Texture2D center) : x(x), y(y), width(width), height(height), cornerTexture(corner), sideTexture(side), centerTexture(center), sideYTexture(sideY) {}
        void Draw(float x, float y, int width, int height);
};