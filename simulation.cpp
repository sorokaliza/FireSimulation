#include <iostream>
#include <vector>
#include <random>

const int WIDTH = 100;
const int HEIGHT = 100;
const int FIRE_CHANCE = 5; // chance of a new fire cell in %
const int FIRE_INTENSITY = 5; // max fire intensity
const int FIRE_SPREAD_CHANCE = 50; // chance of fire spreading in %

std::random_device rd;
std::mt19937 engine(rd());
std::uniform_int_distribution<int> fireChance(1, 100);
std::uniform_int_distribution<int> fireSpreadChance(1, 100);
std::uniform_int_distribution<int> fireIntensity(1, FIRE_INTENSITY);

class Cell {
public:
    int x, y;
    int fireIntensity;
    bool onFire;

    Cell(int x, int y) : x(x), y(y), fireIntensity(0), onFire(false) {}

    void update() {
        if (onFire) {
            if (fireIntensity > 0) {
                fireIntensity--;
            } else {
                onFire = false;
            }
        }
    }

    bool checkFireSpread() {
        return fireSpreadChance(engine) <= FIRE_SPREAD_CHANCE;
    }
};

class FireSimulation {
public:
    std::vector<std::vector<Cell>> grid;

    FireSimulation() {
        for (int y = 0; y < HEIGHT; y++) {
            std::vector<Cell> row;
            for (int x = 0; x < WIDTH; x++) {
                row.push_back(Cell(x, y));
            }
            grid.push_back(row);
        }
    }

    void update() {
