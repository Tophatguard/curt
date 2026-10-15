#include "menu.hpp"

void DrawTextureRot(Texture2D texture, bool flipX, bool flipY, float x, float y, float widthOffset = 0, float heightOffset = 0) {
    Rectangle source = {0, 0, (float)texture.width + widthOffset, (float)texture.height + heightOffset};
    if (flipX) {
        source.width = -source.width;
    } else if (flipY) {
        source.height = -source.height;
    }
    DrawTextureRec(texture, source, {x, y}, WHITE);
}

void menu::Draw(float x, float y, int width, int height) {
    DrawTextureRot(cornerTexture, false, false, x, y);
    DrawTextureRot(sideTexture, false, false, x + cornerTexture.width, y, width - (2*cornerTexture.width));
    DrawTextureRot(cornerTexture, true, false, x + width, y);
}