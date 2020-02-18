#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include "Level.h"

class Level;

class LevelView
{
public:
	LevelView();
	~LevelView();

	void setLevel(Level* level);
	void draw(sf::RenderWindow* window);
	void ChangeTileTexture(size_t x, size_t y);
	std::vector< std::vector<sf::Sprite> > data;
private:
	int cellSize;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
};

