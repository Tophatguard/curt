#include "raylib.h"
#include "include/animals/player.hpp"
#include "include/global/camera.hpp"
#include "include/window/window.hpp"
#include "include/logger/logger.hpp"
#include "include/world/generation.hpp"
#include "include/world/world.hpp"
#include "include/items/menu.hpp"
#include "include/objects/sprite.hpp"
#include "include/items/menu.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
using namespace std;

void Input() {
    if (IsKeyPressed(KEY_F4)) {
        ToggleFullscreen();
    }
    if (IsKeyPressed(KEY_E)) {
        Inventory.open = !Inventory.open;
    }
    if (Inventory.open == true) {
        Inventory.draw();
    }
    Player.move(camera.x, camera.y);
}

// hehehhah

void Initialize() {
    Logger.log("Initializing Window...");
    Window.init();
    
    Logger.log("Initializing Audio...");
    InitAudioDevice();

    Logger.log("Initializing Player...");
    Player.moveKeys = {KEY_W, KEY_A, KEY_S, KEY_D};
    Player.moveSpeed = 1;
    Player.image = (char *)"player";
    Player.init();

    Logger.log("Loading assets...");
    Assets.loadAssets();

    Logger.log("Creating seed...");
    srand(time(0));

    Logger.log("Initializing Hotbar...");
    Hotbar.init(5);

    Logger.log("Initializing Inventory...");
    Inventory.init(5, 4);
    Inventory.clear();

    Logger.log("Changing Mouse...");
    HideCursor();
}

int main() {
    {
        Initialize();
        stringstream ss;
        Texture2D Cursor = LoadTexture("images/global/cursor/cursor.png");
        while (!WindowShouldClose()) {
            Generation.generationUpdate();
            //UpdateMusicStream(Unknown);
            //UpdateMusicStream(closeToHome);
            BeginDrawing();
            Player.draw(Window.WIDTH / 2, Window.HEIGHT / 2);
            for (int i = 0; i < World.Blocks.size(); i++) {
                World.Blocks[i]->draw();
                World.Blocks[i]->collide(camera.x, camera.y, Window.WIDTH, Window.HEIGHT);
            }
            Input();
            Sprite sprite;
            if (GetFPS() <= 40) {
                DrawFPS(0, 0);
            }
            Sprites.draw();
            Hotbar.draw();
            Menus.DrawAll();
            DrawTexture(Cursor, GetMouseX(), GetMouseY(), WHITE);
            ClearBackground(GREEN);
            EndDrawing();
        }
        Player.Unload();
        Hotbar.Unload();
        Inventory.Unload();
    }
    CloseWindow();
    return 0;
}