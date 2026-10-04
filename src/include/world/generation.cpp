#include "generation.hpp"
#include "../world/world.hpp"
#include "../objects/block.hpp"
#include "../window/window.hpp"
#include "../animals/player.hpp"
#include "../global/camera.hpp"
#include <raylib.h>
using namespace std;

void Generation::reset() {
    frame = 0;
    random = GetRandomValue(1, 10);
}

void Generation::generationUpdate() {
    if (Player.moving) {
        frame++;
        if (frame == (random * 60)) {
            random = GetRandomValue(1, 4);
            if (random == 1) {
                World.createBlockAt(GetRandomValue(0, Window.WIDTH) - camera.x, Window.HEIGHT - camera.y, RegisteredBlocks.rock());
            } else if (random == 2) {
                World.createBlockAt(-RegisteredBlocks.rock()->imaget.width - camera.x, GetRandomValue(0, Window.HEIGHT) - camera.y, RegisteredBlocks.rock());
            } else if (random == 3) {
                World.createBlockAt(GetRandomValue(0, Window.WIDTH) - camera.x, -RegisteredBlocks.rock()->imaget.width - camera.y, RegisteredBlocks.rock());
            } else if (random == 4) {
                World.createBlockAt(Window.WIDTH - camera.x, GetRandomValue(0, Window.HEIGHT) - camera.y, RegisteredBlocks.rock());
            }
            reset();
        }
    }
}