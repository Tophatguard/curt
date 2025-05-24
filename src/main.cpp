#include "include/raylib.h"
#include "generation.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <sstream>
using namespace std;

int roundToNearestMultiple(int number, int multiple) {
  return round(static_cast<double>(number) / multiple) * multiple;
}

// CheckCollisionRecs({camx, camy, (float)LoadTexture(image).width, (float)LoadTexture(image).height}, {(float)WIDTH / 2, (float)HEIGHT / 2, (float)LoadTexture(Player.startingPlayerImage).width, (float)LoadTexture(Player.startingPlayerImage).height}

void DrawOutlinedText(Font font,const char *text, int posX, int posY, int fontSize, Color color, int outlineSize, Color outlineColor) {
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX, (float)posY}, fontSize, fontSize / 8, color);
}

class Player {
    public:
        Texture2D playerNorth;
        Texture2D playerSouth;
        Texture2D playerEast;
        Texture2D playerWest;
        Texture2D startingPlayerImage;
        Vector4 moveKeys;
        float moveSpeed;
        bool moving = false;
    public:
        void Unload() {
            UnloadTexture(playerNorth);
            UnloadTexture(playerSouth);
            UnloadTexture(playerEast);
            UnloadTexture(playerWest);
            UnloadTexture(startingPlayerImage);
        }
        void move(float& xToMove, float& yToMove) {
            if (IsKeyDown(moveKeys.x)) {
                startingPlayerImage = playerNorth;
                yToMove += moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.y)) {
                startingPlayerImage = playerWest;
                xToMove += moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.z)) {
                startingPlayerImage = playerSouth;
                yToMove -= moveSpeed;
                moving = true;
            }
            if (IsKeyDown(moveKeys.w)) {
                startingPlayerImage = playerEast;
                xToMove -= moveSpeed;
                moving = true;
            }
            if (!IsKeyDown(moveKeys.x) && !IsKeyDown(moveKeys.y) && !IsKeyDown(moveKeys.z) && !IsKeyDown(moveKeys.w)) {
                moving = false;
            }
        }
        void draw(int x, int y) {
            DrawTexture(startingPlayerImage, x, y, WHITE);
        }
} Player;

class HotBar {
    private:
        vector<vector<int>> items;
        int size;
        stringstream ss;
        Texture2D image = LoadTexture("images/slot.png");
        Texture2D rockImage = LoadTexture("images/rock.png");
        Texture2D selectedImage = LoadTexture("images/slot-selected.png");
        Font comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
    public:
        HotBar(int size) : size(size) {
            items.resize(size, std::vector<int>(2, 0));
        }
        int selectedSlot = 0;

        void Unload() {
            UnloadTexture(image);
            UnloadTexture(selectedImage);
            UnloadTexture(rockImage);
            UnloadFont(comic_sans);
        }

        void add(int slot, int itemID, int amount) {
            if (slot >= 0 && slot < size) {
                if (amount == 0) {
                    TraceLog(LOG_WARNING, "If you add 0 items, it does nothing.");
                } else {
                    items[slot][0] = itemID;
                    items[slot][1] += amount;
                }
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
            }
        }
        void removeItemFromSlot(int slot, int amount) {
            if (slot >= 0 && slot < size) {
                if (amount == items[slot][1]) {
                    items[slot][0] = 0;
                }
                items[slot][1] -= amount;
            }
        }
        int getItemIDInSlot(int slot) {
            if (slot >= 0 && slot < size) {
                return items[slot][0];
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
                return 1;
            }
        }
        int getItemAmount(int slot) {
            if (slot >= 0 && slot < size) {
                return items[slot][1];
            } else {
                TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
                return 1;
            }
        }
        void draw() {
            for (int i = 0; i < size; i++) {
                DrawTexture(image, image.width * i, 0, WHITE);
                if (getItemIDInSlot(i) == 1) {
                    DrawTexture(rockImage, image.width * i, 0, WHITE);
                    ss << getItemAmount(i);
                    DrawOutlinedText(comic_sans, ss.str().c_str(), image.width * i, 0, 20, WHITE, 1, BLACK);
                    ss.str(" ");
                    ss.clear();
                }
            }
            DrawTexture(selectedImage, selectedImage.width * selectedSlot, 0, WHITE);
            if (GetMouseWheelMove() != 0) {
                if (GetMouseWheelMove() < 0) {
                    selectedSlot++;
                    if (selectedSlot >= size) {
                        selectedSlot = 0;
                    }
                } else {
                    selectedSlot--;
                    if (selectedSlot < 0) {
                        selectedSlot = size - 1;
                    }
                }
            }
            if (getItemIDInSlot(selectedSlot) == 1) {
                DrawOutlinedText(comic_sans, "rock", 5, 32, 20, WHITE, 1, BLACK);
            }
            if (getItemIDInSlot(selectedSlot) == 0) {
                DrawOutlinedText(comic_sans,"items", 5, 32, 20, WHITE, 1, BLACK);
            }
        }
};

class Inventory {
    private:
        vector<vector<vector<int>>> items;
        stringstream ss;
        Texture2D image = LoadTexture("images/slot.png");
        Texture2D rockImage = LoadTexture("images/rock.png");
        Texture2D selectedImage = LoadTexture("images/slot-selected.png");
        Font comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
    public:
        Inventory(int sizeX, int sizeY) : items(sizeX, vector<vector<int>>(sizeY, vector<int>(1, 0))) {}
        int selectedSlot = 0;

        void Unload() {
            UnloadTexture(image);
            UnloadTexture(selectedImage);
            UnloadTexture(rockImage);
        }

        void Init() {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 4; j++) {
                    items[i][j][1] = 0;
                }
            }
        }

        void add(int slotX, int slotY, int itemID, int amount) {
            if (amount == 0) {
                TraceLog(LOG_WARNING, "If you add 0 items, it does nothing.");
            } else {
                items[slotX][slotY][0] = itemID;
                items[slotX][slotY][1] += amount;
            }
        }
        void removeItemFromSlot(int slotX, int slotY, int amount) {
            if (amount == items[slotX][slotY][1]) {
                items[slotX][slotY][0] = 0;
            } else {
                items[slotX][slotY][1] -= amount;
            }
        }
        int getItemIDInSlot(int slotX, int slotY) {
            return items[slotX][slotY][0];
        }
        int getItemAmount(int slotX, int slotY) {
            return items[slotX][slotY][1];
        }
        void draw() {
            for (int i = 0; i < 5; i++) {
                DrawTexture(image, image.width * i, 50, WHITE);
                for (int j = 0; j < 4; j++) {
                    DrawTexture(image, image.width * i, image.height * j + 50, WHITE);
                    ss << getItemAmount(i, j);
                    if (getItemIDInSlot(i, j) == 1) {
                        DrawTexture(rockImage, image.width * i, image.height * j + 50, WHITE);
                    } 
                    if (getItemAmount(i, j) != 0)
                        DrawOutlinedText(comic_sans, ss.str().c_str(), image.width * i, image.height * j + 50, 20, WHITE, 1, BLACK);
                    ss.str(" ");
                    ss.clear();
                }
            }
        }
};

typedef struct Interactible {
    bool mined = false;
    Texture2D image;
    Texture2D selectedImage;
    int x, y;
    int health = 3;
    private:
        bool inffix = false;
        Texture2D break1 = LoadTexture("images/break1.png");
        Texture2D break2 = LoadTexture("images/break2.png");
    public:
    void draw(float& camx, float& camy, int WIDTH, int HEIGHT) {
        if (CheckCollisionPointRec(GetMousePosition(), {x + camx, y + camy, (float)image.width, (float)image.height}) && CheckCollisionCircleRec({(float)WIDTH / 2, (float)HEIGHT / 2}, 80, {x + camx, y + camy, (float)image.width, (float)image.height}) && mined == false) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                health -= 1;
            }
            DrawTexture(selectedImage, x + camx, y + camy, WHITE);
            if (health == 3) {
                inffix = false;
            }
            if (health == 2) {
                DrawTexture(break1, x + camx, y + camy - 10, WHITE);
            }
            if (health == 1) {
                DrawTexture(break2, x + camx, y + camy - 10, WHITE);
            }
            if (health == 0) {
                mined = true;
            }
        } else if (mined == false) {
            DrawTexture(image, x + camx, y + camy, WHITE);
            if (health == 2) {
                DrawTexture(break1, x + camx, y + camy - 10, WHITE);
            }
            if (health == 1) {
                DrawTexture(break2, x + camx, y + camy - 10, WHITE);
            }
            if (health == 0) {
                mined = true;
            }
        }
    }
    void collide(float& camx, float& camy, int WIDTH, int HEIGHT) {
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_W) && mined == false) {
            camy -= Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_A) && mined == false) {
            camx -= Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_S) && mined == false) {
            camy += Player.moveSpeed;
        }
        if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)image.width, (float)image.height}) && IsKeyDown(KEY_D) && mined == false) {
            camx += Player.moveSpeed;
        }
    }
    bool Broken() {
        if (inffix == false && mined == true) {
            inffix = true;
            return true;
        } else {
            return false;
        }
    }
    void ReCreate() {
        health = 3;
        inffix = false;
        mined = false;
    }
    void Unload() {
        UnloadTexture(image);
        UnloadTexture(selectedImage);
        UnloadTexture(break1);
        UnloadTexture(break2);
    }
} Interactible;

void Input(float& camx, float& camy, bool& inventoryOpen, Inventory& inventory) {
    if (IsKeyPressed(KEY_F4)) {
        ToggleFullscreen();
    }
    if (IsKeyPressed(KEY_E)) {
        inventoryOpen = !inventoryOpen;
    }
    if (inventoryOpen == true) {
        inventory.draw();
    }
    Player.move(camx, camy);
}

int main() {
    const int WIDTH = 640;
    const int HEIGHT = 480;
    InitWindow(WIDTH, HEIGHT, "Curt, THE SNAIL, DESTROYER OF WORLDS!");
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    float camx = 0;
    float camy = 0;
    Interactible rock;
    Player.moveKeys = {KEY_W, KEY_A, KEY_S, KEY_D};
    Player.moveSpeed = 1;
    Player.playerNorth = LoadTexture("images/player-north.png");
    Player.playerSouth = LoadTexture("images/player-south.png");
    Player.playerEast = LoadTexture("images/player-east.png");
    Player.playerWest = LoadTexture("images/player-west.png");
    Player.startingPlayerImage = LoadTexture("images/player-east.png");
    rock.image = LoadTexture("images/rock.png");
    rock.selectedImage = LoadTexture("images/rock-selected.png");
    srand(time(0));
    rock.x = (rand() % (640 + 1) + 1);
    srand(time(0));
    rock.y = (rand() % (480 + 1) + 1);
    HotBar hotbar(5);
    bool first = true;
    Texture2D grass = LoadTexture("images/grass.png");
    bool invetoryOpen = false;
    Inventory inventory(5, 4);
    inventory.Init();
    while (!WindowShouldClose()) {
        BeginDrawing();
        drawWorld(grass, WIDTH, HEIGHT, camx, camy);
        Player.draw(WIDTH / 2, HEIGHT / 2);
        rock.draw(camx, camy, WIDTH, HEIGHT);
        rock.collide(camx, camy, WIDTH, HEIGHT);
        hotbar.draw();
        if (rock.Broken()) {
            hotbar.add(0, 1, 1);
            inventory.add(0, 0, 1, 1);
            srand(time(0));
            rock.x = (rand() % (640 + 1) + 1);
            srand(time(0));
            rock.y = (rand() % (480 + 1) + 1);
            rock.ReCreate();
        }
        Input(camx, camy, invetoryOpen, inventory);
        if (GetFPS() <= 100) {
            DrawFPS(0, 0);
        }
        ClearBackground(BLUE);
        EndDrawing();
    }
    Player.Unload();
    hotbar.Unload();
    rock.Unload();
    inventory.Unload();
    UnloadTexture(grass);
    CloseWindow();
    return 0;
}