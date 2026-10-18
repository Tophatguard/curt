#pragma once

#include "raylib.h"
#include <vector>
using namespace std;

class menu {
    public:
        float x, y, width, height;
        Texture2D cornerTexture;
        Texture2D sideTexture;
        Texture2D centerTexture;
        Texture2D sideYTexture;
        char *Title;
        char *Description;
        bool destroyed = false;
        bool visible = true;

        void init(float x, float y, int width, int height, Texture2D corner, Texture2D side, Texture2D sideY, Texture2D center, char *Title, char *Description);
        void Draw();
};

inline class Menus {
    public:
        vector<menu> menus;
        void add(menu Menu);
        void DrawAll();
} Menus;