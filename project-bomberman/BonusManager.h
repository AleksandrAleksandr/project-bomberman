#pragma once
#include <SFML/Graphics.hpp>
#include "Bonus.h"
#include "Player.h"
#include "Bot.h"

class BonusManager
{
public:
	BonusManager();
	~BonusManager();
	void Init(Level* level, std::vector<Player*>* players, std::vector<Bot*>* bots);
	void Update(float dt);
	void draw(sf::RenderWindow* window);
private:
	void scatterBonuses();
	//void handleBombKicking(float dt);
	void checkBonusCollisions();
	std::vector<Bonus*> bonuses;
	std::vector<std::pair<int, int>> bonuses_pos;
	//std::map<std::pair<int*, int*>, Bomb*> bombs;
	//std::map<std::pair<int*, int*>, Bomb*>::iterator it;
	std::vector<Player*>* players;
	std::vector<Bot*>* bots;
	
	Level* level;
	sf::RenderWindow* window;
};

