#include "Level.h"
#include "iostream"

Level::Level()
{
}

Level::~Level()
{
}

bool Level::loadFromFile(const std::string& file_)
{
	std::fstream file(file_, std::ios::in);
	if (!file.is_open())
		return false;

	file >> width;
	file >> height;

	data.resize(height);
	for (int i = 0; i < height; i++)
		data[i].resize(width);

	int cell;
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
		{
			file >> cell;
			data[i][j] = static_cast<CellType>(cell);
		}
	return true;
}

int Level::GetCell(int x, int y)
{
	return data[y][x];
}

int Level::GetHeight()
{
	return height;
}

int Level::GetWidth()
{
	return width;
}

void Level::SetLevelView(LevelView* view)
{
	level_view = view;
}

bool Level::DestroyTile(size_t x, size_t y, bool destroyTexture)
{
	if (data[y][x] <= CellType::NONE)
		return false;

	data[y][x] = CellType::NONE;
	level_view->ChangeTileTexture(x, y);

}

void Level::FillBlocks()
{
	std::pair<int, int> free_pos;              // j = 1..12,  i = 1..10
	for (int i = 2; i < GetHeight()-2; i++)
		for (int j = 2; j < GetWidth()-2; j++)
		{
			if (GetCell(j, i) == 0)
			{
				free_pos.first = i; free_pos.second = j;
				if ((i+j != 2) && (i+j != 3) && (i+j != 22) && (i+j !=21))
					free_tiles.push_back(free_pos);
			}
		}
	std::cout<< free_tiles.size() << std::endl;

	for (int i = 0; i < free_tiles.size() / 2; i++)
	{
		int a = rand() % free_tiles.size();
		data[free_tiles[a].first][free_tiles[a].second] = CellType::WEAK_WALL;
	}
}