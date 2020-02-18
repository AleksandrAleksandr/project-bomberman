#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicalBody.h"

class Ray :public PhysicalBody
{
	const int TILE_SIZE = 64;
public:
	enum Side
	{
		Up,
		Down,
		Left,
		Right
	};

	Ray(Side side);
	~Ray();
	
	int GetSide();
	void SetRaySpriteSize(unsigned short size);
	void SetPosition(float x, float y);

	virtual void draw(sf::RenderWindow* window) const;
private:
	/// True - horizontal, false - vertical
	bool orientation;
	sf::Sprite sprite;
	sf::Texture texture;
	Side side;
	unsigned short size;

};