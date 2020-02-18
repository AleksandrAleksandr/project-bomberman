#include "LevelView.h"
#include "iostream"

LevelView::LevelView()
{
	texture1.loadFromFile("BackgroundTile.png");
	texture2.loadFromFile("ExplodableBlock.png");
	texture3.loadFromFile("SolidBlock.png");
}

LevelView::~LevelView()
{
}

void LevelView::setLevel(Level* level)
{
	cellSize = 64;
	
	data.resize(level->GetHeight());
	for (int i = 0; i < level->GetHeight(); ++i)
	{
		data[i].resize(level->GetWidth());
		for (int j = 0; j < level->GetWidth(); ++j)
		{
			data[i][j].setPosition(static_cast<float>(j*cellSize), static_cast<float>(i*cellSize));
			if (level->GetCell(j, i) == 0)
				data[i][j].setTexture(texture1);
			else if (level->GetCell(j, i) == 1)
				data[i][j].setTexture(texture2);
			else
				data[i][j].setTexture(texture3);
		}
	}
}

void LevelView::draw(sf::RenderWindow* window)
{
	for (int i = 0; i < data.size(); i++)
		for (int j = 0; j < data[0].size(); j++)
		{
			window->draw(data[i][j]);
		}
}

void LevelView::ChangeTileTexture(size_t x, size_t y)
{
	data[y][x].setTexture(texture1);
}
