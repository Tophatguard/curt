#include "block.hpp"
#include "../animals/player.hpp"
#include "../global/camera.hpp"
#include "../window/window.hpp"
#include "../global/assets.hpp"
#include <raylib.h>
using namespace std;

Block::Block(Texture2D image, Texture2D selectedImage) {
    // Stands for image Texture
    this->imaget = image;
    this->selectedImage = selectedImage;
    this->hitSound = Assets.hit;
    this->break1 = Assets.break1;
    this->break2 = Assets.break2;
}

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
            mined = true;
            infhit1 = false;
            infhit2 = false;
        }
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
            this->destroy();
            mined = true;
            infhit1 = false;
            infhit2 = false;
        }
    }
}

void Block::destroy() {
    // void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void void;
    Hotbar.add(0, 1, 1);
}