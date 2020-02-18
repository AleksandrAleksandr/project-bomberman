#include "Bomb.h"
#include "iostream"

Bomb::Bomb()
{
	sizeX = 48;
	sizeY = 48;
	/*shape.setSize(sf::Vector2f(sizeX, sizeY));
	shape.setFillColor(sf::Color(243, 197, 48));
	shape.setOrigin(sizeX / 2, sizeY / 2);*/
	texture.loadFromFile("Bomb_f02.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX / 2, sizeY / 2);
	rays.resize(4);
	state = waitingForExplosion;

	soundBuffer.loadFromFile("expl.wav");
	explosionSound.setBuffer(soundBuffer);
	detonationClock.restart();
}

Bomb::~Bomb()
{
}

void Bomb::SetPosition(int x, int y)
{
	x = x / 64;
	y = y / 64;
	//std::cout << y << " " << x << std::endl;
	SetPositionX(static_cast<float>(x)*64 + 64 / 2);
	SetPositionY(static_cast<float>(y)*64 + 64 / 2);
}

void Bomb::SetLevel(Level* lvl)
{
	level = lvl;
}

void Bomb::SetDetonationTime(sf::Time time)
{
	detonationTime = time;
}

void Bomb::update()
{
	sprite.setPosition(posX, posY);
	positionInTilesCoordsX = GetPositionX() / 64;
	positionInTilesCoordsY = GetPositionY() / 64;

	if (detonationClock.getElapsedTime() >= detonationTime && state < State::exploding)
	{
		state = exploding;
		explode();
	}
	else if (detonationClock.getElapsedTime() >= detonationTime + sf::seconds(1) && state < State::exploded)   //sf::seconds(1) - rays on screen time
		state = exploded;

	for (unsigned int i = 0; i < tilesToDeleteAfterExplosion.size(); i++)
		level->DestroyTile(tilesToDeleteAfterExplosion[i].first, tilesToDeleteAfterExplosion[i].second);

}

int Bomb::GetPositionInTileCoordinatesX()
{
	return positionInTilesCoordsX;
}

int Bomb::GetPositionInTileCoordinatesY()
{
	return positionInTilesCoordsY;
}

Bomb::State Bomb::GetState()
{
	return state;
}

void Bomb::explode()
{
	explosionSound.play();
	for (unsigned int i = 0; i < rays.size(); i++)
	{
		rays[i] = new Ray(static_cast<Ray::Side>(i));
		rays[i]->SetPosition(GetPositionX(), GetPositionY());
		rays[i]->SetRaySpriteSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
	}
}

unsigned short Bomb::getRaySizeAfterCollisions(Ray::Side side)
{
	unsigned short size = 0;

	switch (side)
	{
	case Ray::Up:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetCell(positionInTilesCoordsX, positionInTilesCoordsY - i) <= CellType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && positionInTilesCoordsY - size - 1 >= 0 && level->GetCell(positionInTilesCoordsX, positionInTilesCoordsY - size - 1) == CellType::WEAK_WALL)
			tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(positionInTilesCoordsX, positionInTilesCoordsY - ++size));

		break;
	case Ray::Down:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetCell(positionInTilesCoordsX, positionInTilesCoordsY + i) <= CellType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && positionInTilesCoordsY + size + 1 < level->GetHeight() && level->GetCell(positionInTilesCoordsX, positionInTilesCoordsY + size + 1) == CellType::WEAK_WALL)
			tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(positionInTilesCoordsX, positionInTilesCoordsY + ++size));
		break;
	case Ray::Left:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetCell(positionInTilesCoordsX - i, positionInTilesCoordsY) <= CellType::NONE)
			{
				size = i;
			}
			else break;
		}

		if (size != MAX_RAY_SIZE && (level->GetCell(positionInTilesCoordsX - size - 1, positionInTilesCoordsY) == CellType::WEAK_WALL))
		{
			tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(positionInTilesCoordsX - ++size, positionInTilesCoordsY));
		}
		break;
	case Ray::Right:
		for (int i = 1; i <= MAX_RAY_SIZE; ++i)
		{
			if (level->GetCell(positionInTilesCoordsX + i, positionInTilesCoordsY) <= CellType::NONE)
				size = i;
			else break;
		}
		if (size != MAX_RAY_SIZE && level->GetCell(positionInTilesCoordsX + size + 1, positionInTilesCoordsY) == CellType::WEAK_WALL)
			tilesToDeleteAfterExplosion.push_back(std::pair<int, int>(positionInTilesCoordsX + ++size, positionInTilesCoordsY));

		break;
	default:
		break;
	}


	return size;
}

void Bomb::draw(sf::RenderWindow* window) const
{

	window->draw(sprite);
	if (state == State::exploding)
	{
		for (unsigned int i = 0; i < rays.size(); ++i)
		{
			rays[i]->draw(window);
		}
	}
}

Ray* Bomb::GetRay(unsigned int side)
{
	return rays[side];
}