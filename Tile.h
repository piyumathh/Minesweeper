#ifndef MINESWEEPER_TILE_H
#define MINESWEEPER_TILE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
using namespace std;

class Tile : public sf::Sprite
{
private:
    int id;
    bool mine;
    bool flag;
    bool revealed;
    bool clicked;
    bool recursed;
    bool drawn;
    vector<Tile*> neighbors;
public:
    void ToggleFlag();
    void Reveal();
    void Hide();
    void SetMine(bool mine_);
    Tile(int id_, bool mine_, bool flag_, bool revealed_);
    void SetNeighbors(vector<Tile*>& neighbors_);
    int GetID() const;
    bool isRevealed();
    bool isMine();
    bool hasFlag();
    void Click();
    void Unclick();
    bool isClicked();
    vector<Tile*>& GetNeighbors();
    bool hasRecursed();
    void setRecursed(bool state);
    bool isDrawn();
    void setDrawn(bool state);
};


#endif //MINESWEEPER_TILE_H
