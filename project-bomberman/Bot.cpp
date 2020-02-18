#include "Bot.h"
#include "iostream"

Bot::Bot()
{
	sizeX = 62;
	sizeY = 62;
	velocity = 1.5;

	texture.loadFromFile("Creep.png");
	sprite.setPosition(GetPositionX(), GetPositionY());
	sprite.setTexture(texture);
	sprite.setOrigin(sizeX / 2, sizeY / 2);
	sprite.setTextureRect(sf::IntRect(0, 0, sizeX, sizeY));
	//функция для поиска свободных позиций(NONE), и респ позицию бота выбирать из них
	directionX.push_back(1);
	directionX.push_back(-1);
	directionY.push_back(1);
	directionY.push_back(-1);

	clock.restart();
	timeChangeDir = sf::seconds(2);
}

Bot::~Bot()
{
}

void Bot::update()
{
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	sprite.setPosition(GetPositionX(), GetPositionY());
	
	CheckCollisionsWithPlayers();
	/*if (movementX == 0 && GetSpeedY() == 0)
	{
		int a = rand() % 2;
		SetSpeed(0, directionY[a]*3);
	}
	else if (movementY == 0 && GetSpeedX() == 0)
	{
		int a = rand() % 2;
		SetSpeed(directionX[a]*3, 0);
	}*/
	
	seeTargetUp = false;
	seeTargetDown = false;
	seeTargetLeft = false;
	seeTargetRight = false;
	for (unsigned int j = 0; j < players->size(); ++j)
	{
		if (bodyInfo.leftBound == bodyInfo.rightBound && GetPosInTilesX() == (*players)[j]->bodyInfo.centerX)
		{
			if ((*players)[j]->bodyInfo.centerY < GetPosInTilesY())
			{
				for (int k = 1; k <= (bodyInfo.centerY - (*players)[j]->bodyInfo.centerY); k++) {
					if (level->GetCell(GetPosInTilesX(), GetPosInTilesY() - k) != 0)
					{
						//std::cout << "barier UP\n";

						seeTargetUp = false;
						break;
					}
					seeTargetUp = true;
				}
			}
			else
			{
				for (int k = 1; k <= ((*players)[j]->bodyInfo.centerY - bodyInfo.centerY); k++) {
					if (level->GetCell(GetPosInTilesX(), GetPosInTilesY() + k) != 0)
					{
						seeTargetDown = false;
						break;
					}
					seeTargetDown = true;
				}
			}
		}

			if (bodyInfo.upBound == bodyInfo.downBound && GetPosInTilesY() == (*players)[j]->bodyInfo.centerY)
			{
				if ((*players)[j]->bodyInfo.centerX < GetPosInTilesX())
				{
					for (int k = 1; k <= (bodyInfo.centerX - (*players)[j]->bodyInfo.centerX); k++) {
						if (level->GetCell(GetPosInTilesX() - k, GetPosInTilesY()) != 0)
						{
							//std::cout << "barier UP\n";
							seeTargetLeft = false;
							break;
						}
						seeTargetLeft = true;
					}
				}
			else
			{
				for (int k = 1; k <= ((*players)[j]->bodyInfo.centerX - bodyInfo.centerX); k++) {
					if (level->GetCell(GetPosInTilesX() + k, GetPosInTilesY()) != 0)
					{
						seeTargetRight = false;
						break;
					}
					seeTargetRight = true;
					}
			}
			}
		if (seeTargetUp)
		{
			SetSpeed(0, directionY[1]*velocity);
			//std::cout << "target UP\n";
		}
		else if (seeTargetDown)
		{
			SetSpeed(0, directionY[0]*velocity);
			//std::cout << "target DOWN\n";
		}
		else if (seeTargetLeft)
		{
			SetSpeed(directionX[1]*velocity, 0);
			//std::cout << "target LEFT\n";
		}
		else if (seeTargetRight)
		{
			SetSpeed(directionX[0]*velocity, 0);
			//std::cout << "target Right\n";
		}

	}

	/*if (clock.getElapsedTime() > timeChangeDir && !seeTargetDown && !seeTargetLeft && !seeTargetRight && !seeTargetUp)
	{
		int left = false, right = false, up = false, down = false;
		/*int a = rand() % 4;
		std::cout << a << std::endl;
		if (a == 0 && level->GetCell(GetPosInTilesX() - 1, GetPosInTilesY()) == 0 && bodyInfo.upBound == bodyInfo.downBound)
		{
		SetSpeed(directionX[1], 0);
		}
		else if (a == 1 && level->GetCell(GetPosInTilesX() + 1, GetPosInTilesY()) == 0 && bodyInfo.upBound == bodyInfo.downBound)
		{
		SetSpeed(directionX[0], 0);
		}
		else if (a == 2 && level->GetCell(GetPosInTilesX(), GetPosInTilesY() - 1) == 0 && bodyInfo.leftBound == bodyInfo.rightBound)
		{
		SetSpeed(0, directionY[1]);
		}
		else if (a == 3 && level->GetCell(GetPosInTilesX(), GetPosInTilesY() + 1) == 0 && bodyInfo.leftBound == bodyInfo.rightBound)
		{
		SetSpeed(0, directionY[0]);
		}

		if (level->GetCell(GetPosInTilesX() - 1, GetPosInTilesY()) == 0 && bodyInfo.upBound == bodyInfo.downBound)
			left = true;
		if (level->GetCell(GetPosInTilesX() + 1, GetPosInTilesY()) == 0 && bodyInfo.upBound == bodyInfo.downBound)
			right = true;
		if (level->GetCell(GetPosInTilesX(), GetPosInTilesY() - 1) == 0 && bodyInfo.leftBound == bodyInfo.rightBound)
			up = true;
		if (level->GetCell(GetPosInTilesX(), GetPosInTilesY() + 1) == 0 && bodyInfo.leftBound == bodyInfo.rightBound)
			down = true;

		//std::cout << waysX << " " << waysY << std::endl;
		int randX = -1, randY = -1;
		if (left && right)
			randX = rand() % 2;
		else if (left)
			randX = 1;
		else if (right)
			randX = 0;

		if (up && down)
			randY = rand() % 2;
		else if (up)
			randY = 1;
		else if (right)
			randY = 0;

		int a = rand() % 2;
		/*if ((left || right) && (up || down))
		a = rand() % 2;
		else if (left || right)
		a = ;

		if (a == 0) // horizontal
			if (randX != -1)
				SetSpeed(directionX[randX] * velocity, 0);
			else        // vertical
				if (randY != -1)
					SetSpeed(0, directionY[randY] * velocity);

		clock.restart();
	}*/

	if (clock.getElapsedTime() > timeChangeDir && !seeTargetDown && !seeTargetLeft && !seeTargetRight && !seeTargetUp) {
	if (GetSpeedY() == 0 && (level->GetCell(GetPosInTilesX(), GetPosInTilesY() - 1) == 0 || level->GetCell(GetPosInTilesX(), GetPosInTilesY() + 1) == 0) && bodyInfo.leftBound == bodyInfo.rightBound)
	{
	int a = rand() % 3;
	if (a != 2) {
	SetSpeed(0, directionY[a]);
	clock.restart();
	}
	//std::cout << " up - down\n";

	//return;
	}
	else if (GetSpeedX() == 0 && (level->GetCell(GetPosInTilesX() - 1, GetPosInTilesY()) == 0 || level->GetCell(GetPosInTilesX() + 1, GetPosInTilesY()) == 0) && bodyInfo.upBound == bodyInfo.downBound)
	{
	int a = rand() % 3;
	if (a != 2) {
	SetSpeed(directionX[a], 0);
	clock.restart();
	}
	//std::cout << " right - left\n";
	//return;
	}
	}

	if (movementX == 0 && GetSpeedY() == 0)
	{
		SetSpeed(GetSpeedX()*(-1), 0);
		return;
	}
	else if (movementY == 0 && GetSpeedX() == 0)
	{
		SetSpeed(0, GetSpeedY()*(-1));
		return;
	}
}

void Bot::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
}

int Bot::GetPosInTilesX()
{
	return (static_cast<int> (GetPositionX() / 64));
}

int Bot::GetPosInTilesY()
{
	return (static_cast<int> (GetPositionY() / 64));
}

void Bot::SetRespawnPos(int x, int y)
{
	respawnPos.x = x;
	respawnPos.y = y;
}

void Bot::SetLevel(Level* lvl)
{
	level = lvl;
}

void Bot::spawn()
{
	SetPositionX(static_cast<int>(respawnPos.x * 64 + 64 / 2));
	SetPositionY(static_cast<int>(respawnPos.y * 64 + 64 / 2));
}

void Bot::FindFreeTiles()
{
	std::pair<int, int> free_pos;              // j = 1..12,  i = 1..10
	for (int i = 0; i < level->GetHeight(); i++)
		for (int j = 0; j < level->GetWidth(); j++)
		{
			if (level->GetCell(j, i) == 0)
			{
				free_pos.first = i; free_pos.second = j;
				free_tiles.push_back(free_pos);
				//std::cout << free_pos.first << " " << free_pos.second << std::endl;
			}
		}

	int a = rand() % free_tiles.size();
	SetRespawnPos(free_tiles[a].second, free_tiles[a].first);
	SetSpeed(1, 0);
}

void Bot::SetPlayers(std::vector<Player*>* players_)
{
	players = players_;
}

void Bot::CheckCollisionsWithPlayers()
{
	for (unsigned int j = 0; j < players->size(); ++j)
	{
		if (this->isCollision(*(*players)[j]))
			(*players)[j]->OnBombCollision();
	}
}