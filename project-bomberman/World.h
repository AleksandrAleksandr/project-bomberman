#pragma once
#include "Level.h"
#include "LevelView.h"
#include "Player.h"
#include "Bot.h"
#include "PhysicsEngine.h"
#include "BombManager.h"
#include "Animator.h"
#include "BonusManager.h"
#include "GUI.h"

class World
{
private:
	void draw();
	void update(float dt);
	void handleEvents();
	void initGameplay();
public:
	World(sf::RenderWindow* window_);
	~World();

	void init();
	bool start();
private:
	Level* level;
	LevelView* levelView;
	std::vector<Player*> players;
	std::vector<Animator*> players_animators;
	std::vector<Bot*> bots;
	PhysicsEngine* physicsEngine;
	BombManager* bombManager;
	BonusManager* bonusManager;
	GUI* gui;
	sf::Font* font;

	bool enterMenu;
	bool exit;
	bool pause;
	bool endOfGame;
	bool playAgain;

	short playersNumber;
	short botsNumber;
	sf::RenderWindow* window;
	sf::Music music;
};

