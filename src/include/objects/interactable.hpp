#pragma once

#include "raylib.h"
#include <string>
using namespace std;

// TODO: add an on right click function

class Interactable {
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
    void init();
    void collide(float& camx, float& camy, int WIDTH, int HEIGHT);
    void draw();

    ~Interactable();
};

inline struct Interactables {
    // TODO: create more interactables
} Interactables;