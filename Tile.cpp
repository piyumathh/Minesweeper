#include "Tile.h"

void Tile::ToggleFlag()
{
    if (flag)
        flag = false;
    else
        flag = true;
}
void Tile::Reveal()
{
        revealed = true;
        setTexture(TextureManager::GetTexture("tile_revealed"));

}
void Tile::Hide()
{
    if (revealed)
    {
        revealed = false;
        setTexture(TextureManager::GetTexture("tile_hidden"));
    }
}

Tile::Tile(int id_, bool mine_, bool flag_, bool revealed_)
{
    id = id_;
    mine = mine_;
    flag = flag_;
    revealed = revealed_;
    //position = position_;
}

void Tile::SetNeighbors(vector<Tile*>& neighbors_)
{
    for (int i = 0; i < neighbors_.size(); i++)
        neighbors.push_back(neighbors_[i]);
}

int Tile::GetID() const
{
    return id;
}

void Tile::SetMine(bool mine_)
{
    mine = mine_;
}

bool Tile::isRevealed()
{
    return revealed;
}

bool Tile::isMine()
{
    return mine;
}
bool Tile::hasFlag()
{
    return flag;
}

vector<Tile *>& Tile::GetNeighbors()
{
    return neighbors;
}
void Tile::Click()
{
    clicked = true;
}
bool Tile::isClicked()
{
    return clicked;
}
void Tile::Unclick()
{
    clicked = false;
}
bool Tile::hasRecursed()
{
    return recursed;
}
void Tile::setRecursed(bool state)
{
    recursed = state;
}
bool Tile::isDrawn()
{
    return drawn;
}
void Tile::setDrawn(bool state)
{
    drawn = state;
}
