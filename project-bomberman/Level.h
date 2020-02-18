#pragma once
#include <SFML/Graphics.hpp>
#include "vector"
#include <fstream>
#include "LevelView.h"

enum CellType
{
	NONE,
	WEAK_WALL,
	ROCK,
};

class LevelView;

class Level
{
public:
	Level();
	~Level();

	bool loadFromFile(const std::string& file_);
	int GetCell(int x, int y);
	int GetWidth();
	int GetHeight();
	bool DestroyTile(size_t x, size_t y, bool destroyTexture = true);
	void FillBlocks();

	void SetLevelView(LevelView* view);
private:
	int width;
	int height;
	LevelView* level_view;
	
	std::vector< std::vector<CellType> > data;
	std::vector< std::pair<int, int>> free_tiles;
};
