#pragma once

#include <raylib.h>

inline class Generation {
    public:
        int frame = 0;
        int random = GetRandomValue(1, 10);
        void reset();
        void generationUpdate();
} Generation;