#include "include/raylib.h"
#include <string>
#include <cmath>

void drawWorld(Texture2D grass, int screenWidth, int screenHeight, int camx, int camy) {
    const int tileWidth = grass.width;
    const int tileHeight = grass.height;

    // Adjusted grid bounds calculation for Y/5 scaling
    const int maxX = (screenWidth/(tileWidth/2) + screenHeight/(tileHeight/5)) / 2 + 1;
    const int maxY = (screenHeight * 2)/(tileHeight/5) + 1; // Vertical coverage calculation

    // Modified vertical offset to account for Y/5 scaling
    const int verticalOffset = -tileHeight * 2;

    for(int gridY = -maxY; gridY <= maxY; gridY++) {
        for(int gridX = -maxX; gridX <= maxX; gridX++) {
            // Convert to modified isometric coordinates
            Vector2 pos = {
                (float)((gridX - gridY) * tileWidth / 2),
                (float)((gridX + gridY) * tileHeight / 5 + verticalOffset)
            };

            // Expanded bounds check for the new scaling
            if(pos.x + tileWidth > -tileWidth && pos.x < screenWidth + tileWidth &&
               pos.y + tileHeight > -tileHeight && pos.y < screenHeight + tileHeight) {
                DrawTexture(grass, pos.x + camx, pos.y + camy, WHITE);
            }
        }
    }
}