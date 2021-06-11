#include "Board.h"

Board::Board(bool revealed, int mineCount_, int rows_, vector<Tile>& tiles_)
{
    debugMode = false;
    mineCount = mineCount_;
    rows = rows_;
    for (int i = 0; i < tiles_.size(); i++)
        tiles.push_back(tiles_[i]);
}

vector<Tile>& Board::GetTiles()
{
    return tiles;
}

void Board::Reveal()
{
    if (!revealed)
        revealed = true;

    for (int i = 0; i < tiles.size(); i++)
        tiles[i].Reveal();
}

void Board::Hide()
{
    for (int i = 0; i < tiles.size(); i++)
            tiles[i].Hide();
}

bool Board::isRevealed()
{
    return revealed;
}

int Board::getMineCount()
{
    return mineCount;
}
int Board::GetRows()
{
    return rows;
}
void Board::SetDebugMode(bool state)
{
    debugMode = state;
}
bool Board::GetDebugMode()
{
    return debugMode;
}