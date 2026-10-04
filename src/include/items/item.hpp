#pragma once
#include "raylib.h"

// lowk I just locked in. So that's I the code here looks completely different from my other code + I came back after a while of just not working on the project
class Item {
    public:
        int id;
        const char *name;
        const char *description;
        const char *imagePath;
        Texture2D image;
        int maxStackSize;

        Item(int id, const char *name, const char *description, const char *imagePath, Texture2D image, int maxStackSize) : id(id), name(name), description(description), imagePath(imagePath), image(image), maxStackSize(maxStackSize) {};
        ~Item();
};

struct Items {
    Item* rock() {
        return new Item{1, "Rock", "It's a fuckass boulder even though it's just called a rock", "assets/world/rock/rock.png", {}, 9999};
    }
};