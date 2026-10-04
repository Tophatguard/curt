#include "item.hpp"

Item::~Item() {
    UnloadTexture(image);
}