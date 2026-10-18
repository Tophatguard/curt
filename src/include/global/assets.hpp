#pragma once

#include "raylib.h"

inline struct Assets {
    Texture2D rock;
    Texture2D rockSelected;
    Texture2D grass;
    Texture2D grassSelected;
    Texture2D break1;
    Texture2D break2;

    Music closeToHome;
    Music Unknown;

    Sound hit;

    Texture2D cornerTexture;
    Texture2D sideTexture;
    Texture2D sideYTexture;
    Texture2D centerTexture;
    
    Font comicSans;

    Texture2D debug;

    Texture2D uranium;
    Texture2D uraniumSelected;

    void loadAssets();
} Assets;