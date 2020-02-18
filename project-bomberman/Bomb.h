#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PhysicalBody.h"
#include "Level.h"
#include "Ray.h"

class Bomb : public PhysicalBody
{
	
public:
	const int MAX_RAY_SIZE = 4;
	enum State
	{
		waitingForExplosion,
		exploding,
		exploded
	};
	//sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;

	void update();
	void SetPosition(int x, int y);
	void SetDetonationTime(sf::Time time);
	void SetLevel(Level* lvl);

	int GetPositionInTileCoordinatesX();
	int GetPositionInTileCoordinatesY();
	Bomb::State GetState();
	Ray* GetRay(unsigned int side);
	unsigned short getRaySizeAfterCollisions(Ray::Side side);
	void draw(sf::RenderWindow* window) const;

	Bomb();
	~Bomb();

private:
	Level* level;
	int positionInTilesCoordsX;
	int positionInTilesCoordsY;
	State state;
	sf::Time detonationTime;
	sf::Clock detonationClock;
	struct rayLength
	{
		int up;
		int down;
		int left;
		int right;
	};
	std::vector<Ray*> rays;
	std::vector<std::pair<int, int>> tilesToDeleteAfterExplosion;

	void explode();
	
	sf::Sound explosionSound;
	sf::SoundBuffer soundBuffer;
};

