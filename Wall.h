#ifndef WALL_H
#define WALL_H

#include "Building.h"

class Wall : public Building {
public:
    Wall(int x, int y);
    void takeDamage(int amount);
int getHealth() const;

static int getMaxInstances();
};

#endif
