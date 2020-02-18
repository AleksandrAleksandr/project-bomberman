#include "Bonus.h"
#include "iostream"

Bonus::Bonus(std::pair<int, int> pos)
{
	sizeX = 32;
	sizeY = 32;
	
	int a = rand() % 2;
	type = static_cast<Type> (a);
	if (type == speed)
		texture.loadFromFile("SpeedPowerup.png");
	else if (type == bomb)
		texture.loadFromFile("BombPowerup.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX / 2, sizeY / 2);

	futurePos.x = pos.first;
	futurePos.y = pos.second;
	waitingTime = sf::seconds(10);
	state = hide;
}

Bonus::~Bonus()
{
}

void Bonus::SetPosition(int x, int y)
{
	x = x / 64;
	y = y / 64;
	//std::cout << y << " " << x << std::endl;
	SetPositionX(static_cast<float>(x) * 64 + 64 / 2);
	SetPositionY(static_cast<float>(y) * 64 + 64 / 2);
}

void Bonus::SetLevel(Level* lvl)
{
	level = lvl;
}

void Bonus::SetDetonationTime(sf::Time time)
{
	waitingTime = time;
}

void Bonus::update()
{
	if (state == hide && level->GetCell(futurePos.y, futurePos.x) == CellType::NONE)
	{
		clock.restart();
		SetPositionX(static_cast<float>(futurePos.y) * 64 + 64 / 2);
		SetPositionY(static_cast<float>(futurePos.x) * 64 + 64 / 2);
		sprite.setPosition(posX, posY);
		state = waiting;
	}
	else if (state == waiting && clock.getElapsedTime() >= waitingTime)
	{
		state = ended;
		//delete this;
	}
}

void Bonus::SetState(int st)
{
	state = static_cast<State> (st);
}
int Bonus::GetState()
{
	return state;
}

void Bonus::SetType(int type_)
{
	type = static_cast<Type> (type_);
}
int Bonus::GetType()
{
	return type;
}

int Bonus::GetPositionInTileCoordinatesX()
{
	return positionInTilesCoordsX;
}

int Bonus::GetPositionInTileCoordinatesY()
{
	return positionInTilesCoordsY;
}

/*void Bonus::explode()
{
	explosionSound.play();
	for (unsigned int i = 0; i < rays.size(); i++)
	{
		rays[i] = new Ray(static_cast<Ray::Side>(i));
		rays[i]->SetPosition(GetPositionX(), GetPositionY());
		rays[i]->SetRaySpriteSize(getRaySizeAfterCollisions(static_cast<Ray::Side>(i)));
	}
}*/

void Bonus::draw(sf::RenderWindow* window) const
{
	if (state != State::hide)
		window->draw(sprite);
}