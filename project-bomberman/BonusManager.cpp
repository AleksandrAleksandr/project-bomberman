#include "BonusManager.h"
#include "iostream"

BonusManager::BonusManager()
{
}

BonusManager::~BonusManager()
{
}

void BonusManager::Init(Level * level_, std::vector<Player*>* players_, std::vector<Bot*>* bots_)
{
	level = level_;
	players = players_;
	bots = bots_;
	scatterBonuses();
}

void BonusManager::Update(float dt)
{
	for (short i = 0; i < bonuses.size(); i++)
	{
		bonuses[i]->update();
		if (bonuses[i]->GetState() == 2)
		{
			auto pos = std::find(bonuses.begin(), bonuses.end(), bonuses[i]);
			bonuses.erase(pos);
		}
	}
	//handleBombKicking(dt);
	//std::cout <<bonuses.size()<<std::endl;
	checkBonusCollisions();
}

void BonusManager::scatterBonuses()
{
	std::pair<int, int> weak_wall;              // j = 1..12,  i = 1..10
	for (int i = 1; i < level->GetHeight(); i++)
		for (int j = 1; j < level->GetWidth(); j++)
		{
			if (level->GetCell(j, i) == CellType::WEAK_WALL)
			{
				weak_wall.first = i; weak_wall.second = j;
				bonuses_pos.push_back(weak_wall);
			}
		}

	for (int i = 0; i < 6; i++)
	{
		int a = rand() % bonuses_pos.size();
		bonuses.push_back(new Bonus(bonuses_pos[a]));
		std::cout << bonuses_pos[a].first<<" "<<bonuses_pos[a].second << std::endl;
	}
	for (int i = 0; i < bonuses.size(); i++)
	{
		bonuses[i]->SetLevel(level);
	}
	std::cout << bonuses.size() << std::endl;
}

/*void BonusManager::handleBombKicking(float dt)
{
for (it = bombs.begin(); it != bombs.end(); ++it)
{
Bomb* tmpBomb = it->second;

if (tmpBomb->GetState() == Bomb::State::waitingForExplosion)
{

if (tmpBomb->isMoving() &&
(level->GetTile(tmpBomb->GetNextPositionInTileCoordsX(), tmpBomb->GetNextPositionInTileCoordsY()) == TT::NONE || level->GetTile(tmpBomb->GetNextPositionInTileCoordsX(), tmpBomb->GetNextPositionInTileCoordsY()) == TT::NONE_WITH_SHADOW))
{
tmpBomb->SetPositionX(tmpBomb->GetPositionX() + tmpBomb->GetVelocityX() * dt);
tmpBomb->SetPositionY(tmpBomb->GetPositionY() + tmpBomb->GetVelocityY() * dt);

if (level->GetTile(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY()) == TT::BOMB)
level->DestroyTile(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY(), false);
}
else
{
tmpBomb->FixPosition();
tmpBomb->StopMoving();
level->SetTileAsBomb(tmpBomb->GetPositionInTileCoordinatesX(), tmpBomb->GetPositionInTileCoordinatesY());
}
}

for (unsigned int i = 0; i < players->size(); ++i)
{
if ((*players)[i]->IsCollidingWithBomb() && (*players)[i]->GetBombCollidingWithCoordinates().x == *(it->first.first)
&& (*players)[i]->GetBombCollidingWithCoordinates().y == *(it->first.second))
{
tmpBomb->SetMoveDirection((*players)[i]->GetSideBombCollidingWith());
(*players)[i]->SetIsCollidingWithBomb(false);
(*players)[i]->SetSideBombCollidingWith(0, 0);
}
}


for (unsigned int i = 0; i < players->size(); ++i)
{
if (tmpBomb->isMoving())
{
if (((*players)[i])->IsTileCollidingInAxisX(tmpBomb->GetNextPositionInTileCoordsX())
&& ((*players)[i])->IsTileCollidingInAxisY(tmpBomb->GetNextPositionInTileCoordsY()))
{
tmpBomb->StopMoving();
}
}
}
}
bombs.clear();
}*/

void BonusManager::checkBonusCollisions()
{
	for (unsigned int i = bonuses.size(); i > 0; --i)
	{
		for (unsigned int j = 0; j < players->size(); ++j)
		{
			if (bonuses[i - 1]->isCollision(*(*players)[j]))
			{
				//(*players)[j]->OnBombCollision();
				if (bonuses[i - 1]->GetType() == 0)
				{
					(*players)[j]->SpeedPowerUp();
				}
				else if (bonuses[i - 1]->GetType() == 1)
				{
					(*players)[j]->BombPowerUp();
				}
				bonuses[i - 1]->SetState(2);
			}
		}
		
		//bonuses.pop_back();
	}
	//rays.clear();
}

void BonusManager::draw(sf::RenderWindow* window)
{
	for (short i = 0; i < bonuses.size(); i++)
	{
		bonuses[i]->draw(window);
	}
}
