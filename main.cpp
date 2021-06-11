#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "Tile.h"
#include "Random.h"
#include "Board.h"
using namespace std;

vector<Tile*> GetNeighborVector(vector<int> TileIDs, vector<Tile>& tiles);
void PlaceMines(int numMines, vector<Tile>& tiles);
void DrawMine(const Tile& t, sf::RenderWindow& window);
void DrawFlag(const Tile& t, sf::RenderWindow& window);
bool NumberCheck(vector<int>& v, int num);
void DrawBoard(Board& b, sf::RenderWindow& window, int flagCount);
int PlaceSpecificMines(string name, vector<Tile>& tiles, int rows, int columns);
void DrawMineNumber(Tile& t, sf::RenderWindow& window, Board& b);
void DrawCounter(int count, int rows, sf::RenderWindow& window);
bool WinCondition(Board& b);
string den();

bool WinCondition(Board& b)
{
    for (int i = 0; i < b.GetTiles().size(); i++)
    {
        if (!b.GetTiles()[i].isRevealed() && !b.GetTiles()[i].isMine())
            return false;
    }
    return true;
}

void DrawCounter(int count, int rows, sf::RenderWindow& window)
{
    sf:: Sprite counter1;
    sf:: Sprite counter2;
    sf:: Sprite counter3;
    sf:: Sprite counter4;
    counter1.setTexture(TextureManager::GetTexture("digits"));
    counter2.setTexture(TextureManager::GetTexture("digits"));
    counter3.setTexture(TextureManager::GetTexture("digits"));
    counter4.setTexture(TextureManager::GetTexture("digits"));

    if (count < 10 && count >= 0)
    {
        counter4.setTextureRect(sf::IntRect(count * 21, 0, 21, 32));
        counter4.setPosition(63.0f, (float) rows * 32);
        window.draw(counter4);
    }
    else if ((count >= 10 && count < 100) || (count < 0 && count > -10))
    {
        if (count >= 10 && count < 100)
        {
            int secondDigit = count % 10;
            int firstDigit = count / 10;
            counter4.setTextureRect(sf::IntRect(secondDigit * 21, 0, 21, 32));
            counter4.setPosition(63.0f, (float) rows * 32);
            window.draw(counter4);
            counter3.setTextureRect(sf::IntRect(firstDigit * 21, 0, 21, 32));
            counter3.setPosition(42.0f, (float) rows * 32);
            window.draw(counter3);
        }
        else
        {
            int digit = count - (2 * count);
            counter3.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
            counter3.setPosition(42.0f, (float) rows * 32);
            window.draw(counter3);
            counter4.setTextureRect(sf::IntRect(digit * 21, 0, 21, 32));
            counter4.setPosition(63.0f, (float) rows * 32);
            window.draw(counter4);
        }

    }
    else if ((count >= 100 && count < 1000) || (count <= -10 && count > -100))
    {
        if (count >= 100 && count < 1000)
        {
            int firstDigit = count / 100;
            int secondDigit = (count / 10) % 10;
            int thirdDigit = count % 10;
            counter4.setTextureRect(sf::IntRect(thirdDigit * 21, 0, 21, 32));
            counter4.setPosition(63.0f, (float) rows * 32);
            window.draw(counter4);
            counter3.setTextureRect(sf::IntRect(secondDigit * 21, 0, 21, 32));
            counter3.setPosition(42.0f, (float) rows * 32);
            window.draw(counter3);
            counter2.setTextureRect(sf::IntRect(firstDigit * 21, 0, 21, 32));
            counter2.setPosition(21.0f, (float) rows * 32);
            window.draw(counter2);
        }
        else
        {
            int absValue = count - (2 * count);
            int firstDigit = absValue / 10;
            int secondDigit = absValue % 10;
            counter2.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
            counter2.setPosition(21.0f, (float) rows * 32);
            window.draw(counter2);
            counter3.setTextureRect(sf::IntRect(firstDigit * 21, 0, 21, 32));
            counter3.setPosition(42.0f, (float) rows * 32);
            window.draw(counter3);
            counter4.setTextureRect(sf::IntRect(secondDigit * 21, 0, 21, 32));
            counter4.setPosition(63.0f, (float) rows * 32);
            window.draw(counter4);
        }
    }
    else
    {
        int absValue = count - (2 * count);
        int firstDigit = absValue / 100;
        int secondDigit = (absValue / 10) % 10;
        int thirdDigit = absValue % 10;
        counter1.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
        counter1.setPosition(0.0f, (float) rows * 32);
        window.draw(counter1);
        counter4.setTextureRect(sf::IntRect(thirdDigit * 21, 0, 21, 32));
        counter4.setPosition(63.0f, (float) rows * 32);
        window.draw(counter4);
        counter3.setTextureRect(sf::IntRect(secondDigit * 21, 0, 21, 32));
        counter3.setPosition(42.0f, (float) rows * 32);
        window.draw(counter3);
        counter2.setTextureRect(sf::IntRect(firstDigit * 21, 0, 21, 32));
        counter2.setPosition(21.0f, (float) rows * 32);
        window.draw(counter2);
    }
}

void DrawMineNumber(Tile& t, sf::RenderWindow& window, Board& b)
{
    string path = "number_";
    int count = 0;
    vector<int> tileIDs;
    window.draw(t);

    for (int i = 0; i < t.GetNeighbors().size(); i++)
        tileIDs.push_back(t.GetNeighbors()[i]->GetID());

    for (int i = 0; i < tileIDs.size(); i++)
    {
        for (int j = 0; j < b.GetTiles().size(); j++)
        {
            if (tileIDs[i] == b.GetTiles()[j].GetID() && b.GetTiles()[j].isMine())
                count++;
        }
    }
    if (count != 0)
    {
        path += to_string(count);
        sf::Sprite number;
        number.setTexture(TextureManager::GetTexture(path));
        number.setPosition(t.getPosition());
        window.draw(number);
    }
    else
    {
        t.setRecursed(true);
        for (int i = 0; i < tileIDs.size(); i++)
        {
            for (int j = 0; j < b.GetTiles().size(); j++)
            {
                if (tileIDs[i] == b.GetTiles()[j].GetID() && !b.GetTiles()[j].hasFlag() && !b.GetTiles()[j].isRevealed() && !b.GetTiles()[j].isMine())
                {
                    b.GetTiles()[j].Reveal();
                    b.GetTiles()[j].Click();
                    window.draw(b.GetTiles()[j]);
                }
            }
        }
        for (int i = 0; i < t.GetNeighbors().size(); i++)
        {
            Tile& tile = *t.GetNeighbors()[i];
            if (!tile.hasFlag() && !tile.isRevealed() && !tile.isMine())
            {
                tile.Reveal();
                tile.Click();
            }
        }
        for (auto & i : t.GetNeighbors())
        {
            if (!i->hasRecursed())
                DrawMineNumber(*i, window, b);
        }

    }
}
void DrawFlag(const Tile& t, sf::RenderWindow& window)
{
    sf::Sprite flag;
    flag.setTexture(TextureManager::GetTexture("flag"));
    flag.setPosition(t.getPosition());
    window.draw(flag);
}

int PlaceSpecificMines(string name, vector<Tile>& tiles, int rows, int columns)
{
    for (int i = 0; i < tiles.size(); i++)
        tiles[i].SetMine(false);

    string path = "boards/";
    path += name + ".brd";
    ifstream input(path);
    string line;
    int mineCount = 0;
    for (int i = 0; i < rows; i++)
    {
        getline(input, line);
        for (int j = 0; j < columns; j++)
        {
            char c = line.at(j);
            if (c == '1')
            {
                tiles[(i*columns) + j].SetMine(true);
                mineCount++;
            }
            else
                tiles[(i*columns) + j].SetMine(false);
        }
    }
    return mineCount;
}

void DrawBoard(Board& b, sf::RenderWindow& window, int flagCount)
{
    for (int i = 0; i < b.GetTiles().size(); i++)
    {
        window.draw(b.GetTiles()[i]);
        if (b.GetTiles()[i].isRevealed())
        {
            if (b.GetTiles()[i].isMine())
            {
                if (b.GetTiles()[i].hasFlag())
                    DrawFlag(b.GetTiles()[i], window);

                DrawMine(b.GetTiles()[i], window);
            }
            else if (b.GetTiles()[i].isClicked() && !b.GetTiles()[i].isMine())
                DrawMineNumber(b.GetTiles()[i], window, b);
        }
        else
        {
            if (b.GetTiles()[i].isMine() && b.GetDebugMode())
                DrawMine(b.GetTiles()[i], window);
            if (b.GetTiles()[i].hasFlag())
                DrawFlag(b.GetTiles()[i], window);
        }
    }
    DrawCounter(flagCount, b.GetRows(), window);
}

bool NumberCheck(vector<int>& v, int num)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == num)
            return false;
    }
    return true;
}
void DrawMine(const Tile& t, sf::RenderWindow& window)
{
    sf::Sprite mine;
    mine.setTexture(TextureManager::GetTexture("mine"));
    mine.setPosition(t.getPosition());
    window.draw(mine);
}
void PlaceMines(int numMines, vector<Tile>& tiles)
{
    vector<int> mines;
    for (int i = 0; i < tiles.size(); i++)
        tiles[i].SetMine(false);

    mines.push_back(Random::RandInt(1, tiles.size()));
    //cout << mines[0] << endl;
    //int count = 1;
    while (mines.size() < numMines)
    {

        int m = Random::RandInt(1, tiles.size());
        if (NumberCheck(mines, m))
        {
            //count++;
            mines.push_back(m);
            //cout << m << " " << count << endl;
        }
    }

    for (int i = 0; i < mines.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            if(j + 1 == mines[i])
            {
                tiles[j].SetMine(true);
                //cout << tiles[j].GetID() << endl;
            }
        }
    }
}

vector<Tile*> GetNeighborVector(vector<int> TileIDs, vector<Tile>& tiles)
{
    vector<Tile*> neighbors;
    for (int i = 0; i < TileIDs.size(); i++)
    {
        for (int j = 0; j < tiles.size(); j++)
        {
            if (tiles[j].GetID() == TileIDs[i])
            {
                neighbors.push_back(&tiles[j]);
                break;
            }
        }
    }
    return neighbors;
}

int main()
{
    ifstream input("boards/config.cfg");
    string numCol;
    string numRow;
    string numMine;
    getline(input, numCol);
    getline(input, numRow);
    getline(input, numMine);
    cout << "Columns: (at least 15)" << endl;
    int numColumns = stoi(numCol);
    cin >> numColumns;
    cout << "Rows: " << endl;
    int numRows = stoi(numRow);
    cin >> numRows;
    cout << "Mines: " << endl;
    int numMines = stoi(numMine);
    cin >> numMines;
    int numTiles = numColumns * numRows;
    vector<Tile> tiles;
    int flagCounter = numMines;
    bool gameOver = false;

    //making the tiles
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numColumns; j++)
        {
            Tile t((i*numColumns) + j + 1, false, false, false);
            t.setPosition((float) j*32, (float) i*32);
            t.setTexture(TextureManager::GetTexture("tile_hidden"));
            tiles.push_back(t);
        }   //tiles are IDed starting from 1
    }

    //setting up neighbor vectors
    for (int i = 0; i < tiles.size(); i++)
    {
        vector<int> TileIDs;
        vector<Tile*> neighborsMain;
        if (tiles[i].GetID() == 1)      //left up corner
        {
            TileIDs.push_back(2);
            TileIDs.push_back(1 + numColumns);
            TileIDs.push_back(2 + numColumns);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);
            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() == numColumns)    //right up corner
        {
            TileIDs.push_back(numColumns - 1);
            TileIDs.push_back(numColumns * 2);
            TileIDs.push_back((numColumns * 2) - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() ==  numTiles) //right bottom corner
        {
            TileIDs.push_back(numTiles - 1);
            TileIDs.push_back(numTiles - numColumns);
            TileIDs.push_back(numTiles - numColumns - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() ==  numTiles - numColumns + 1)    //bottom left corner
        {
            TileIDs.push_back(numTiles - numColumns + 2);
            TileIDs.push_back(numTiles - (numColumns * 2) + 1);
            TileIDs.push_back(numTiles - (numColumns * 2) + 2);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() < numColumns && tiles[i].GetID() > 1)
        {
            TileIDs.push_back(tiles[i].GetID() + 1);
            TileIDs.push_back(tiles[i].GetID() - 1);
            TileIDs.push_back(tiles[i].GetID() + numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns + 1);
            TileIDs.push_back(tiles[i].GetID() + numColumns - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() > numTiles - numColumns && tiles[i].GetID() < numTiles)
        {
            TileIDs.push_back(tiles[i].GetID() + 1);
            TileIDs.push_back(tiles[i].GetID() - 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns);
            TileIDs.push_back(tiles[i].GetID() - numColumns + 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() % numColumns == 0 && tiles[i].GetID() != numColumns && tiles[i].GetID() != numTiles)
        {
            TileIDs.push_back(tiles[i].GetID() - 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns - 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else if (tiles[i].GetID() % numColumns == 1 && tiles[i].GetID() != 1 && tiles[i].GetID() != numTiles - numColumns + 1)
        {
            TileIDs.push_back(tiles[i].GetID() + 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns + 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns + 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
        else
        {
            TileIDs.push_back(tiles[i].GetID() + 1);
            TileIDs.push_back(tiles[i].GetID() - 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns);
            TileIDs.push_back(tiles[i].GetID() + numColumns + 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns + 1);
            TileIDs.push_back(tiles[i].GetID() + numColumns - 1);
            TileIDs.push_back(tiles[i].GetID() - numColumns - 1);
            for (int j = 0; j < GetNeighborVector(TileIDs, tiles).size(); j++)
                neighborsMain.push_back(GetNeighborVector(TileIDs, tiles)[j]);

            tiles[i].SetNeighbors(neighborsMain);
        }
    } //done setting up neighbor vectors hope it works

    //making face
    sf::Sprite face;
    face.setTexture(TextureManager::GetTexture("face_happy"));
    face.setPosition((float) (numColumns - 12) * 32, (float) numRows * 32);

    //making buttons
    sf::Sprite debug;
    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition((float) (numColumns - 8) * 32, (float) numRows * 32);
    sf::Sprite test1;
    test1.setTexture(TextureManager::GetTexture("test_1"));
    test1.setPosition((float) (numColumns - 6) * 32, (float) numRows * 32);
    sf::Sprite test2;
    test2.setTexture(TextureManager::GetTexture("test_2"));
    test2.setPosition((float) (numColumns - 4) * 32, (float) numRows * 32);
    sf::Sprite test3;
    test3.setTexture(TextureManager::GetTexture("test_3"));
    test3.setPosition((float) (numColumns - 2) * 32, (float) numRows * 32);

    //making the board
    Board b(false, numMines, numRows, tiles);

    //setting mines
    PlaceMines(b.getMineCount(), b.GetTiles());

    sf::RenderWindow window(sf::VideoMode(numColumns * 32, (numRows * 32) + 88), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (debug.getGlobalBounds().contains(mousePos.x, mousePos.y) && !gameOver)
                    {
                        if (b.GetDebugMode())
                            b.SetDebugMode(false);
                        else
                            b.SetDebugMode(true);
                        /*or (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].isMine() && !b.GetTiles()[i].isRevealed())
                                b.GetTiles()[i].Reveal();
                            else if (b.GetTiles()[i].isMine() && b.GetTiles()[i].isRevealed())
                                b.GetTiles()[i].Hide();
                        }*/
                    }
                    else if (face.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        flagCounter = numMines;
                        gameOver = false;
                        for (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].isClicked())
                                b.GetTiles()[i].Unclick();
                            if (b.GetTiles()[i].hasFlag())
                                b.GetTiles()[i].ToggleFlag();
                        }
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        b.Hide();
                        PlaceMines(numMines, b.GetTiles());
                    }
                    else if (test1.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        for (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].hasFlag())
                                b.GetTiles()[i].ToggleFlag();
                        }
                        gameOver = false;
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        b.Hide();
                        PlaceSpecificMines("testboard1", b.GetTiles(), numRows, numColumns);
                        flagCounter = PlaceSpecificMines("testboard1", b.GetTiles(), numRows, numColumns);
                    }
                    else if (test2.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        for (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].hasFlag())
                                b.GetTiles()[i].ToggleFlag();
                        }
                        gameOver = false;
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        b.Hide();
                        PlaceSpecificMines("testboard2", b.GetTiles(), numRows, numColumns);
                        flagCounter = PlaceSpecificMines("testboard2", b.GetTiles(), numRows, numColumns);
                    }
                    else if (test3.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        for (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].hasFlag())
                                b.GetTiles()[i].ToggleFlag();
                        }
                        gameOver = false;
                        face.setTexture(TextureManager::GetTexture("face_happy"));
                        b.Hide();
                        PlaceSpecificMines("testboard3", b.GetTiles(), numRows, numColumns);
                        flagCounter = PlaceSpecificMines("testboard3", b.GetTiles(), numRows, numColumns);
                    }
                    else
                    {
                        for (int i = 0; i < b.GetTiles().size(); i++)
                        {
                            if (b.GetTiles()[i].getGlobalBounds().contains(mousePos.x, mousePos.y) && !b.GetTiles()[i].hasFlag() && !gameOver)
                            {
                                b.GetTiles()[i].Click();
                                b.GetTiles()[i].Reveal();
                                if (b.GetTiles()[i].isMine())
                                {
                                    for (int j = 0; j < b.GetTiles().size(); j++)
                                    {
                                        if (b.GetTiles()[j].isMine())
                                            b.GetTiles()[j].Reveal();
                                    }
                                    face.setTexture(TextureManager::GetTexture("face_lose"));
                                    gameOver = true;
                                }
                            }
                        }
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    for (int i = 0; i < b.GetTiles().size(); i++)
                    {
                        if (b.GetTiles()[i].getGlobalBounds().contains(mousePos.x, mousePos.y) && !b.GetTiles()[i].isRevealed() && !gameOver)
                        {
                            b.GetTiles()[i].ToggleFlag();
                            if (b.GetTiles()[i].hasFlag())
                                flagCounter--;
                            else
                                flagCounter++;
                        }
                    }
                }
            }
        }
        window.clear();
        DrawBoard(b, window, flagCounter);
        if (WinCondition(b))
        {
            gameOver = true;
            face.setTexture(TextureManager::GetTexture("face_win"));
            for (int j = 0; j < b.GetTiles().size(); j++)
            {
                if (!b.GetTiles()[j].isRevealed() && !b.GetTiles()[j].hasFlag())
                {
                    b.GetTiles()[j].ToggleFlag();
                    flagCounter--;
                }
            }
        }
        window.draw(face);
        window.draw(debug);
        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.display();
    }

    return 0;
}
//win condition
//recursion
//lock board
//change bg color maybe
//recursion acts slightly better when draw board b passed by value