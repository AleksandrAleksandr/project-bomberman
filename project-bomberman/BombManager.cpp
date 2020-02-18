#include "BombManager.h"
#include "iostream"

BombManager::BombManager()
{
}

BombManager::~BombManager()
{
}

void BombManager::Init(Level * level_, std::vector<Player*>* players_, std::vector<Bot*>* bots_)
{
	level = level_;
	players = players_;
	bots = bots_;
}

void BombManager::Update(float dt)
{
	gatherBombInformation();
	//handleBombKicking(dt);
	checkBombsAfterExplosionsCollisions();
}

/*void BombManager::handleBombKicking(float dt)
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

void BombManager::checkBombsAfterExplosionsCollisions()
{
	for (unsigned int i = rays.size(); i > 0; --i)
	{
		for (unsigned int j = 0; j < players->size(); ++j)
		{
			if (rays[i - 1]->isCollision(*(*players)[j]))
				(*players)[j]->OnBombCollision();
		}
		for (unsigned int j = 0; j < bots->size(); ++j)
		{
			if (rays[i - 1]->isCollision(*(*bots)[j]))
			{
				auto pos = std::find(bots->begin(), bots->end(), (*bots)[j]);
				bots->erase(pos);
			}
		}
		rays.pop_back();
	}
	//rays.clear();
}

void BombManager::gatherBombInformation()
{
	for (unsigned int i = 0; i < players->size(); ++i)
	{
		/*if ((*players)[i]->HasBomb())
		{
			bombs.emplace(std::pair<int*, int*>((*players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesX(), (*players)[i]->GetBomb()->GetPositionPointerInTileCoordinatesY()),
				(*players)[i]->GetBomb());
		}*/
		if ((*players)[i]->isBombExplosion())
			for (unsigned int j = 0; j < 4; ++j)
				rays.push_back((*players)[i]->GetRay(j));
	}
}