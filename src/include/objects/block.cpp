#include "block.hpp"
#include "../text/text.hpp"
#include "../animals/player.hpp"
#include "../global/camera.hpp"
#include "../window/window.hpp"
#include "../global/assets.hpp"
#include <raylib.h>
#include <iostream>
using namespace std;

void Block::collide(float& camx, float& camy, int WIDTH, int HEIGHT) {
    if (mined == true) return;
    if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)imaget.width, (float)imaget.height}) && IsKeyDown(KEY_W) && mined == false) {
        camy -= Player.moveSpeed;
    }
    if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)imaget.width, (float)imaget.height}) && IsKeyDown(KEY_A) && mined == false) {
        camx -= Player.moveSpeed;
    }
    if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)imaget.width, (float)imaget.height}) && IsKeyDown(KEY_S) && mined == false) {
        camy += Player.moveSpeed;
    }
    if (Player.moving && CheckCollisionRecs({(float)WIDTH / 2, (float)HEIGHT / 2, (float)Player.startingPlayerImage.width, (float)Player.startingPlayerImage.height}, {x + camx, y + camy, (float)imaget.width, (float)imaget.height}) && IsKeyDown(KEY_D) && mined == false) {
        camx += Player.moveSpeed;
    }
}

Block::~Block() {
    UnloadTexture(imaget);
    UnloadTexture(selectedImage);
    UnloadTexture(break1);
    UnloadTexture(break2);
}

void Block::draw() {
    if (CheckCollisionPointRec(GetMousePosition(), {x + camera.x, y + camera.y, (float)imaget.width, (float)imaget.height}) && CheckCollisionCircleRec({(float)Window.WIDTH / 2, (float)Window.HEIGHT / 2}, 80, {x + camera.x, y + camera.y, (float)imaget.width, (float)imaget.height}) && mined == false) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            health -= 1;
        }
        DrawTexture(selectedImage, x + camera.x, y + camera.y, WHITE);
        if (health >= ((ogHealth / 3) * 2)) {
            inffix = false;
        }
        if (health >= (ogHealth / 3) && health <= ((ogHealth / 3) * 2)) {
            DrawTexture(break1, x + camera.x, y + camera.y - 10, WHITE);
        if (!infhit1) {
            PlaySound(hitSound);
            infhit1 = true;
        }
        }
        if (health <= (ogHealth / 3)) {
            DrawTexture(break2, x + camera.x, y + camera.y - 10, WHITE);
            if (!infhit2) {
                PlaySound(hitSound);
                infhit2 = true;
            }
        }
        if (health == 0) {
            destroy();
            mined = true;
            infhit1 = false;
            infhit2 = false;
        }
        stringstream ss;
        ss << name << " " << health << "/" << ogHealth;
        DrawOutlinedText(Assets.comicSans, ss.str().c_str(), x + camera.x - imaget.width/2, y + camera.y - 20, 20, WHITE, 1, BLACK);
        ss.clear();
        ss.str(" ");
    } else if (mined == false) {
        DrawTexture(imaget, x + camera.x, y + camera.y, WHITE);
        if (health == 2) {
            DrawTexture(break1, x + camera.x, y + camera.y - 10, WHITE);
            if (!infhit1) {
                PlaySound(hitSound);
                infhit1 = true;
            }
        }
        if (health == 1) {
            DrawTexture(break2, x + camera.x, y + camera.y - 10, WHITE);
            if (!infhit2) {
                PlaySound(hitSound);
                infhit2 = true;
            }
        }
        if (health == 0) {
            destroy();
            mined = true;
            infhit1 = false;
            infhit2 = false;
        }
    }
}

void Block::destroy() {
    cout << "destroying block" << endl;
    onDestroy(this, name);
    // void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void;
    Hotbar.add(0, 1, 1);
}