#include "interactable.hpp"
#include "../animals/player.hpp"
using namespace std;

void Interactable::init() {
    if (image == nullptr) image = (char *)"rock";
    path = string("images/") + string("world/") + string(image) + "/" + string(image);
    selectedImage = LoadTexture((path + "-selected.png").c_str());
    // Stands for image Texture
    imaget = LoadTexture((path + ".png").c_str());
    break1 = LoadTexture("images/global/break/break1.png");
    break2 = LoadTexture("images/global/break/break2.png");
}

void Interactable::collide(float& camx, float& camy, int WIDTH, int HEIGHT) {
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

Interactable::~Interactable() {
    UnloadTexture(imaget);
    UnloadTexture(selectedImage);
    UnloadTexture(break1);
    UnloadTexture(break2);
}