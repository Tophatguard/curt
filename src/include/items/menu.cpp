#include "menu.hpp"

void menu::Draw() {
    DrawTexture(topLeftCorner, x, y, WHITE);
    DrawTexture(topRightCorner, x + width - topRightCorner.width, y, WHITE);
    DrawTexture(bottomLeftCorner, x, y + height - bottomLeftCorner.height, WHITE);
    DrawTexture(bottomRightCorner, x + width - bottomRightCorner.width, y + height - bottomRightCorner.height, WHITE);
}