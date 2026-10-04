#include "player.hpp"
#include "../text/text.hpp"
using namespace std;


// player functions
void Player::draw(int x, int y) {
    DrawTexture(startingPlayerImage, x, y, WHITE);
}

void Player::move(float& xToMove, float& yToMove) {
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
    } else if (IsKeyDown(moveKeys.y) && IsKeyDown(moveKeys.w)) {
        moving = false;
    } else if (IsKeyDown(moveKeys.x) && IsKeyDown(moveKeys.z)) {
        moving = false;
    }
}

void Player::Unload() {
    UnloadTexture(playerNorth);
    UnloadTexture(playerSouth);
    UnloadTexture(playerEast);
    UnloadTexture(playerWest);
    UnloadTexture(startingPlayerImage);
}

void Player::init() {
    if (image == nullptr) image = (char *)"player";
    path = std::string("images/animals/") + std::string(image) + "/" + std::string(image);
    playerNorth = LoadTexture((path + "-north.png").c_str());
    playerSouth = LoadTexture((path + "-south.png").c_str());
    playerEast = LoadTexture((path + "-east.png").c_str());
    playerWest = LoadTexture((path + "-west.png").c_str());
    startingPlayerImage = playerSouth;
}

// Hotbar functions
void Hotbar::init(int newSize) {
    size = newSize;
    items.resize(size, std::vector<int>(2, 0));
    image = LoadTexture("images/global/slot/slot.png");
    rockImage = LoadTexture("images/world/rock/rock.png");
    selectedImage = LoadTexture("images/global/slot/slot-selected.png");
    comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
}

void Hotbar::draw() {
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
        // errerrrrerer i'm sans the skeleton
        DrawOutlinedText(comic_sans, "Rock", 5, 32, 20, WHITE, 1, BLACK);
    }
    if (getItemIDInSlot(selectedSlot) == 0) {
        DrawOutlinedText(comic_sans,"Items", 5, 32, 20, WHITE, 1, BLACK);
    }
}

void Hotbar::Unload() {
    UnloadTexture(image);
    UnloadTexture(selectedImage);
    UnloadTexture(rockImage);
    UnloadFont(comic_sans);
}

// am i supposed to remember how this works...
// also the Logger class was not implemented at the time so the following functions uses TraceLog instead
void Hotbar::add(int slot, int itemID, int amount) {
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

void Hotbar::removeItemFromSlot(int slot, int amount) {
    if (slot >= 0 && slot < size) {
        if (amount == items[slot][1]) {
            items[slot][0] = 0;
        }
        items[slot][1] -= amount;
    }
}

int Hotbar::getItemIDInSlot(int slot) {
    if (slot >= 0 && slot < size) {
        return items[slot][0];
    } else {
        TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
        return 1;
    }
}

int Hotbar::getItemAmount(int slot) {
    if (slot >= 0 && slot < size) {
        return items[slot][1];
    } else {
       TraceLog(LOG_FATAL, "FATAL ERROR: stack overflow");
        return 1;
    }
}

// Inventory functions
void Inventory::init(int sizeX, int sizeY) {
    items.assign(sizeX, std::vector<std::vector<int>>(sizeY, std::vector<int>(2, 0)));

    image = LoadTexture("images/global/slot/slot.png");
    rockImage = LoadTexture("images/world/rock/rock.png");
    selectedImage = LoadTexture("images/global/slot/slot-selected.png");
    comic_sans = LoadFont("fonts/Comic Sans MS.ttf");
}

void Inventory::Unload() {
    UnloadTexture(image);
    UnloadTexture(selectedImage);
    UnloadTexture(rockImage);
    UnloadFont(comic_sans);
}

void Inventory::clear() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            items[i][j][1] = 0;
        }
    }
}

void Inventory::add(int slotX, int slotY, int itemID, int amount) {
    if (amount == 0) {
        TraceLog(LOG_WARNING, "If you add 0 items, it does nothing.");
    } else {
        items[slotX][slotY][0] = itemID;
        items[slotX][slotY][1] += amount;
    }
}

void Inventory::removeItemFromSlot(int slotX, int slotY, int amount) {
    if (amount == items[slotX][slotY][1]) {
        items[slotX][slotY][0] = 0;
    } else {
        items[slotX][slotY][1] -= amount;
    }
}

int Inventory::getItemIDInSlot(int slotX, int slotY) {
    return items[slotX][slotY][0];
}

int Inventory::getItemAmount(int slotX, int slotY) {
    return items[slotX][slotY][1];
}

void Inventory::draw() {
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