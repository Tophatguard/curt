#include "menu.hpp"
#include <iostream>
#include "../text/text.hpp"
#include "../global/assets.hpp"
using namespace std;

void DrawTextureRot(Texture2D texture, bool flipX, bool flipY, float x, float y, float widthOffset = 0, float heightOffset = 0) {
    Rectangle source = {0, 0, (float)texture.width + widthOffset, (float)texture.height + heightOffset};
    if (flipX) {
        source.width = -source.width;
    }
    if (flipY) {
        source.height = -source.height;
    }
    DrawTextureRec(texture, source, {x, y}, WHITE);
}

void menu::Draw() {
    DrawTextureRot(cornerTexture, false, false, x, y);
    DrawTextureRot(sideTexture, false, false, x + cornerTexture.width, y, width - (2*cornerTexture.width));
    DrawTextureRot(cornerTexture, true, false, x + width, y);
    DrawTextureRot(sideYTexture, false, false, x + width, y + cornerTexture.height, 0, height - (2*cornerTexture.width));
    DrawTextureRot(sideYTexture, true, false, x, y + cornerTexture.height, 0, height - (2*cornerTexture.width));
    DrawTextureRot(cornerTexture, false, true, x, y + height);
    DrawTextureRot(sideTexture, false, true, x + cornerTexture.width, y + height, width - (2*cornerTexture.width));
    DrawTextureRot(cornerTexture, true, true, x + width, y + height);
    DrawTextureRot(centerTexture, false, false, x + cornerTexture.width, y + cornerTexture.height, width - (2*cornerTexture.width), height - (2*cornerTexture.width));
    DrawOutlinedText(Assets.comicSans, Title, x + cornerTexture.width / 2, y + cornerTexture.height / 2, 20, WHITE, 1, BLACK);
    DrawOutlinedText(Assets.comicSans, Description, x + cornerTexture.width / 2, y + 10+cornerTexture.height, 10, { 200, 200, 200, 255 }, 1, BLACK);
}

void menu::init(float x, float y, int width, int height, Texture2D corner, Texture2D side, Texture2D sideY, Texture2D center, char *Title, char *Description) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->cornerTexture = corner;
    this->sideTexture = side;
    this->sideYTexture = sideY;
    this->centerTexture = center;
    this->Title = Title;
    this->Description = Description;
}

void Menus::DrawAll() {
    for (int i = 0; i < menus.size(); i++) {
        if (menus[i].visible == true) {
            menus[i].Draw();
        }
    }
}

void Menus::add(menu Menu) {
    menus.push_back(Menu);
}