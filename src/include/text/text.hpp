#pragma once

#include "raylib.h"

inline void DrawOutlinedText(Font font, const char *text, int posX, int posY, float fontSize, Color color, int outlineSize, Color outlineColor) {
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY - outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX - outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX + outlineSize, (float)posY + outlineSize}, fontSize, fontSize / 8, outlineColor);
    DrawTextEx(font, text, {(float)posX, (float)posY}, fontSize, fontSize / 8, color);
}
