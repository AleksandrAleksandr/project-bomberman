#pragma once
#include "PhysicalBody.h"
#include "Player.h"
#include "Bot.h"
#include "Level.h"
#include "vector"


class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Init(Level* level_, std::vector<Player*>* players_, std::vector <Bot*>* bots_);
	void Update();
private:
	Level* level;
	std::vector <std::vector<PhysicalBody*>> levelObjects;
	std::vector <Player*> players;
	std::vector <Bot*> bots;

	void setBodyPositionInfo(int id);
	void setBotPositionInfo(int id);
	void setBodyPositionNextToAnotherBodyInAxisY(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);
	void setBodyPositionNextToAnotherBodyInAxisX(PhysicalBody * bodyToSetPostition, PhysicalBody * referenceBody);
};