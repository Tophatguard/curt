#pragma once

#include "raylib.h"

class menu {
    public:
        int x, y, width, height;
        Texture2D topLeftCorner;
        Texture2D topRightCorner;
        Texture2D bottomLeftCorner;
        Texture2D bottomRightCorner;
        menu(int x, int y, int width, int height, Texture2D tlc, Texture2D trc, Texture2D blc, Texture2D brc) : x(x), y(y), width(width), height(height), topRightCorner(trc), topLeftCorner(tlc), bottomLeftCorner(blc), bottomRightCorner(brc) {}
        void Draw();
};