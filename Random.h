#ifndef MINESWEEPER_RANDOM_H
#define MINESWEEPER_RANDOM_H
#include <random>
using namespace std;

class Random
{
    static mt19937 random;
public:
    static int RandInt(int min, int max);
    static float RandFloat(float min, float max);
};


#endif //MINESWEEPER_RANDOM_H
