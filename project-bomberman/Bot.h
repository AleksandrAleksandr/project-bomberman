#pragma once
#include "PhysicalBody.h"
#include "Level.h"
#include "Player.h"
#include "vector"

class Bot : public PhysicalBody
{
	sf::Vector2i respawnPos;
public:
	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	Level* level;

	void update();
	void spawn();
	void SetRespawnPos(int x, int y);
	void SetLevel(Level* lvl);
	void FindFreeTiles();
	void SetPlayers(std::vector<Player*>* players_);
	void CheckCollisionsWithPlayers();

	int GetPosInTilesX();
	int GetPosInTilesY();
	void draw(sf::RenderWindow* window);

	Bot();
	~Bot();
private:
	std::vector<std::pair<int, int>> free_tiles;
	std::vector<int> directionX;
	std::vector<int> directionY;
	std::vector<Player*>* players;
	sf::Clock clock;
	sf::Time timeChangeDir;

	float velocity;
	bool seeTargetUp, seeTargetDown, seeTargetLeft, seeTargetRight;
};


