#include "assets.hpp"

void Assets::loadAssets() {
    // rock
    rock = LoadTexture("images/world/rock/rock.png");
    rockSelected = LoadTexture("images/world/rock/rock-selected.png");

    // grass
    grass = LoadTexture("images/world/grass/grass.png");
    grassSelected = LoadTexture("images/world/grass/grass-selected.png");

    // break
    break1 = LoadTexture("images/global/break/break1.png");
    break2 = LoadTexture("images/global/break/break2.png");

    // songs
    closeToHome = LoadMusicStream("songs/closeToHome.mp3");
    Unknown = LoadMusicStream("songs/Unknown.mp3");

    // sounds
    hit = LoadSound("sounds/hit.mp3");

}