#pragma once

#include "raylib.h"
#include <vector>
#include <sstream>
using namespace std;

inline class Player {
    public:
        char *image;
        Texture2D startingPlayerImage;
        Vector4 moveKeys;
        float moveSpeed;
        bool moving = false;
    
    private:
        std::string path;

        Texture2D playerNorth;
        Texture2D playerSouth;
        Texture2D playerEast;
        Texture2D playerWest;
        

    public:

        void init();

        void Unload();

        void move(float& xToMove, float& yToMove);
        void draw(int x, int y);
} Player;

inline class Hotbar {
    private:
        vector<vector<int>> items;
        int size;
        stringstream ss;
        Texture2D image;
        Texture2D rockImage;
        Texture2D selectedImage;
        Font comic_sans;
    public:
        void init(int newSize);
        int selectedSlot = 0;

        void Unload();
        
        void add(int slot, int itemID, int amount);
        void removeItemFromSlot(int slot, int amount);
        int getItemIDInSlot(int slot);
        int getItemAmount(int slot);
        void draw();
} Hotbar;

inline class Inventory {
    private:
        vector<vector<vector<int>>> items;
        stringstream ss;
        Texture2D image;
        Texture2D rockImage;
        Texture2D selectedImage;
        Font comic_sans;
    public:
        bool open = false;
        void init(int sizeX, int sizeY);
        int selectedSlot = 0;

        void Unload();

        void clear();

        void add(int slotX, int slotY, int itemID, int amount);
        void removeItemFromSlot(int slotX, int slotY, int amount);
        int getItemIDInSlot(int slotX, int slotY);
        int getItemAmount(int slotX, int slotY);
        void draw();
} Inventory;