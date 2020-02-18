#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicalBody.h"
#include "Level.h"

class Bonus : public PhysicalBody
{
public:
	enum State
	{
		hide,
		waiting,
		ended
	};

	enum Type
	{
		speed,
		bomb
	};
	//sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;

	void update();
	void SetPosition(int x, int y);
	void SetDetonationTime(sf::Time time);
	void SetLevel(Level* lvl);
	void SetState(int st);
	int GetState();
	void SetType(int type_);
	int GetType();

	int GetPositionInTileCoordinatesX();
	int GetPositionInTileCoordinatesY();

	void draw(sf::RenderWindow* window) const;

	Bonus(std::pair<int, int> pos);
	~Bonus();

private:
	Level* level;
	int positionInTilesCoordsX;
	int positionInTilesCoordsY;
	State state;
	Type type;
	sf::Time waitingTime;
	sf::Clock clock;
	sf::Vector2f futurePos;

	std::vector<std::pair<int, int>> bonuses;
	void explode();
};