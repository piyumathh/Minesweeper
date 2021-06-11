#ifndef MINESWEEPER_TEXTUREMANAGER_H
#define MINESWEEPER_TEXTUREMANAGER_H
#include <SFML/Graphics.hpp>
#include <unordered_map>
using namespace std;

class TextureManager
{
    static unordered_map<string, sf::Texture> textures;
public:
    static void LoadTexture(string textureName);
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};


#endif //MINESWEEPER_TEXTUREMANAGER_H
