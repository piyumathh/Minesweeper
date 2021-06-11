#ifndef MINESWEEPER_BOARD_H
#define MINESWEEPER_BOARD_H
#include <vector>
#include "Tile.h"
using namespace std;

class Board
{
private:
    int mineCount;
    int rows;
    vector<Tile> tiles;
    bool revealed;
    bool debugMode;
public:
    Board(bool revealed, int mineCount_, int rows_, vector<Tile>& tiles_);
    vector<Tile>& GetTiles();
    void Reveal();
    void Hide();
    void Reset();
    bool isRevealed();
    int getMineCount();
    int GetRows();
    void SetDebugMode(bool state);
    bool GetDebugMode();
};


#endif //MINESWEEPER_BOARD_H
