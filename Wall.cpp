#include "Wall.h"

Wall::Wall(int x, int y) : Building(x, y, 1, 1, 10, 0, 100, 200, "🧱", false) {}
void Wall::takeDamage(int amount) {
    health -= amount;
    if (health < 0) health = 0;
}

int Wall::getHealth() const {
    return health;
}


int Wall::getMaxInstances() {
    return 200;  
}
