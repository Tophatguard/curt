#pragma once

#include "raylib.h"

inline class Window {
    public:
        const int WIDTH = 640;
        const int HEIGHT = 480;
        void init() {
            InitWindow(WIDTH, HEIGHT, "Curt: THE SNAIL, DESTROYER OF WORLDS!");
            SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
        }
} Window;