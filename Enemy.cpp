#include "Enemy.h"
#include "Wall.h"
#include "GoldMine.h"
#include "ElixirCollector.h"
#include "TownHall.h"
Enemy::Enemy(int x, int y) : Npc(x, y, "👹"), damage(10), speedCounter(0), speed(3),
                             isAttacking(false), targetBuilding(nullptr) {}
bool Enemy::update(const Position& targetPos, vector<Wall>& walls, vector<GoldMine>& goldMines,
                   vector<ElixirCollector>& elixirCollectors, const TownHall& townhall) {
    speedCounter++;
    if (speedCounter >= speed) {
        speedCounter = 0;

        Position pos = getPosition();

        // Check if reached Town Hall
        Position thPos = townhall.getPosition();
        if (pos.x >= thPos.x && pos.x < thPos.x + townhall.getSizeX() &&
            pos.y >= thPos.y && pos.y < thPos.y + townhall.getSizeY()) {
            return true;
        }

        // If already attacking a building
        if (isAttacking && targetBuilding) {
            targetBuilding->takeDamage(damage);
            if (targetBuilding->getHealth() <= 0) {
                isAttacking = false;
                // Move into the building's position after destroying it
                setPosition(targetBuilding->getPosition().x, targetBuilding->getPosition().y);
                targetBuilding = nullptr;
            }
            return false;
        }

        // Check for walls 1 tile ahead
        for (auto& wall : walls) {
            if ((pos.x == wall.getPosition().x - 1 && pos.y == wall.getPosition().y) && wall.getHealth() > 0) {
                isAttacking = true;
                targetBuilding = &wall;
                targetBuilding->takeDamage(damage);
                return false;
            }
        }

        // Check for other buildings (mines/collectors) when standing on them
        for (auto& mine : goldMines) {
            Position minePos = mine.getPosition();
            if (pos.x >= minePos.x && pos.x < minePos.x + mine.getSizeX() &&
                pos.y >= minePos.y && pos.y < minePos.y + mine.getSizeY() && mine.getHealth() > 0) {
                isAttacking = true;
                targetBuilding = &mine;
                targetBuilding->takeDamage(damage);
                return false;
            }
        }

        for (auto& collector : elixirCollectors) {
            Position colPos = collector.getPosition();
            if (pos.x >= colPos.x && pos.x < colPos.x + collector.getSizeX() &&
                pos.y >= colPos.y && pos.y < colPos.y + collector.getSizeY() && collector.getHealth() > 0) {
                isAttacking = true;
                targetBuilding = &collector;
                targetBuilding->takeDamage(damage);
                return false;
            }
        }

        // Normal movement
        isAttacking = false;
        targetBuilding = nullptr;

        if (pos.x < targetPos.x) pos.x++;
        else if (pos.x > targetPos.x) pos.x--;

        if (pos.y < targetPos.y) pos.y++;
        else if (pos.y > targetPos.y) pos.y--;

        setPosition(pos.x, pos.y);
    }
    return false;
}

int Enemy::getDamage() const {
    return damage;
}
