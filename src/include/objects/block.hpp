#pragma once

#include <string>
#include "raylib.h"
#include "../global/assets.hpp"
#include "sprite.hpp"
#include <chrono>
#include <thread>
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
        string name;
    
        // DO NOT USE plllEAASSee
        int x, y;
    Block(Texture2D image, Texture2D selectedImage, string name) {
        // Stands for image Texture
        this->imaget = image;
        this->selectedImage = selectedImage;
        this->hitSound = Assets.hit;
        this->break1 = Assets.break1;
        this->break2 = Assets.break2;
        this->name = name;
    }
    void collide(float& camx, float& camy, int WIDTH, int HEIGHT);
    void draw();
    void destroy();
    ~Block();
};

inline void (*onDestroy_ptr)(Block *self, string name) = nullptr;

inline void onDestroy(Block *self, string name) {
    TraceLog(LOG_INFO, name.c_str());
    if (name == "uranium") {
        Sound sound = LoadSound("sounds/boom.mp3");
        TraceLog(LOG_INFO, "goob");
        Sprite sprite;
        sprite.x = 0;
        sprite.y = 0;
        sprite.size = 999;
        sprite.texture = LoadTexture("images/global/debug/boom.png");
        sprite.rotation = 0;
        Sprites.add(sprite);
        PlaySound(sound);
        this_thread::sleep_for(chrono::seconds(10));
        while (true) {
            CloseWindow();
        }
    }
};

inline struct RegisteredBlocks {
    // TODO: create more blocks
    Block* rock() {
        return new Block(Assets.rock, Assets.rockSelected, "rock");
    }
    Block* grass() {
        return new Block(Assets.grass, Assets.grassSelected, "grass");
    }
    Block* uranium() {
        return new Block(Assets.uranium, Assets.uraniumSelected, "uranium");
    }

} RegisteredBlocks;