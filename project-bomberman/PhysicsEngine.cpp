#include "PhysicsEngine.h"
#include "iostream"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Init(Level * level_, std::vector<Player*>* players_, std::vector <Bot*>* bots_)
{
	level = level_;
	
	players.resize(players_->size());
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		players[i] = (*players_)[i];
	}

	bots.resize(bots_->size());
	for (unsigned int i = 0; i < bots.size(); ++i)
	{
		bots[i] = (*bots_)[i];
	}

	levelObjects.resize(level->GetHeight());
	for (unsigned int i = 0; i < levelObjects.size(); ++i)
	{
		levelObjects[i].resize(level->GetWidth());
	}

	for (unsigned int y = 0; y < levelObjects.size(); ++y)
		for (unsigned int x = 0; x < levelObjects[y].size(); ++x)
		{
			levelObjects[y][x] = new PhysicalBody();

			levelObjects[y][x]->SetPositionX(static_cast<float>(x)*64 + 64 / 2);
			levelObjects[y][x]->SetPositionY(static_cast<float>(y)*64 + 64 / 2);
			levelObjects[y][x]->SetSize(static_cast<float>(64), static_cast<float>(64));
		}

	//std::cout << level->GetCell(1, 2) << " " <<level->GetCell(4,7);
}

void PhysicsEngine::Update()
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		setBodyPositionInfo(i);

		players[i]->SetMovementX(0);
		players[i]->SetMovementY(0);

		float movementY = players[i]->GetSpeedY();
		float movementX = players[i]->GetSpeedX();

		/*if (movementX == 0 && movementY == 0)
			continue;*/

		PhysicalBody bodyAfterYMovement = *players[i];
		PhysicalBody bodyAfterXMovement = *players[i];

		bodyAfterYMovement.SetPositionY(players[i]->GetPositionY() + players[i]->GetSpeedY());
		bodyAfterXMovement.SetPositionX(players[i]->GetPositionX() + players[i]->GetSpeedX());

		bool moveInYAxis = true, moveInXAxis = true;

		switch (players[i]->bodyInfo.state)
		{
		case PhysicalBody::OnSingleTile:
			//std::cout << "On single tile\n";
			if (level->GetCell(players[i]->bodyInfo.centerX, players[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY - 1][players[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY - 1][players[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && level->GetCell(players[i]->bodyInfo.centerX, players[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY + 1][players[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY + 1][players[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && level->GetCell(players[i]->bodyInfo.centerX - 1, players[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && level->GetCell(players[i]->bodyInfo.centerX + 1, players[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case PhysicalBody::OnTwoTilesHorizontal:
			//std::cout << "On two horiz tile\n";

			int additionTileXCoord;
			if (players[i]->bodyInfo.leftBound == players[i]->bodyInfo.centerX)
				additionTileXCoord = players[i]->bodyInfo.rightBound;
			else
				additionTileXCoord = players[i]->bodyInfo.leftBound;
			
			if (moveInYAxis && level->GetCell(players[i]->bodyInfo.centerX, players[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY - 1][players[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY - 1][players[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis  && level->GetCell(players[i]->bodyInfo.centerX, players[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY + 1][players[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY + 1][players[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInYAxis &&level->GetCell(additionTileXCoord, players[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if (moveInYAxis &&level->GetCell(additionTileXCoord, players[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case PhysicalBody::OnTwoTilesVertical:
			//std::cout << "On two vertical tile\n";

			int additionTileYCoord;
			if (players[i]->bodyInfo.upBound == players[i]->bodyInfo.centerY)
				additionTileYCoord = players[i]->bodyInfo.downBound;
			else
				additionTileYCoord = players[i]->bodyInfo.upBound;
		
			if (moveInXAxis && level->GetCell(players[i]->bodyInfo.centerX - 1, players[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis  && level->GetCell(players[i]->bodyInfo.centerX + 1, players[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.centerY][players[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			if (moveInXAxis && level->GetCell(players[i]->bodyInfo.centerX - 1, additionTileYCoord) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[additionTileYCoord][players[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[additionTileYCoord][players[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis &&level->GetCell(players[i]->bodyInfo.centerX + 1, additionTileYCoord) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[additionTileYCoord][players[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[additionTileYCoord][players[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			break;

		case PhysicalBody::OnFourTiles:
			//std::cout << "On four tile\n";

			if (level->GetCell(players[i]->bodyInfo.leftBound, players[i]->bodyInfo.upBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.leftBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(players[i]->bodyInfo.rightBound, players[i]->bodyInfo.upBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.rightBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.upBound][players[i]->bodyInfo.rightBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(players[i]->bodyInfo.leftBound, players[i]->bodyInfo.downBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.leftBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(players[i]->bodyInfo.rightBound, players[i]->bodyInfo.downBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.rightBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(players[i], levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(players[i], levelObjects[players[i]->bodyInfo.downBound][players[i]->bodyInfo.rightBound]);
				moveInYAxis = false;
			}
		}
		if (moveInXAxis)
		{
			players[i]->SetMovementX(movementX);
		}
		if (moveInYAxis)
		{
			players[i]->SetMovementY(movementY);
		}
	}

	for (unsigned int i = 0; i < bots.size(); ++i)
	{
		setBotPositionInfo(i);

		bots[i]->SetMovementX(0);
		bots[i]->SetMovementY(0);

		float movementY = bots[i]->GetSpeedY();
		float movementX = bots[i]->GetSpeedX();

		/*if (movementX == 0 && movementY == 0)
		continue;*/

		PhysicalBody bodyAfterYMovement = *bots[i];
		PhysicalBody bodyAfterXMovement = *bots[i];

		bodyAfterYMovement.SetPositionY(bots[i]->GetPositionY() + bots[i]->GetSpeedY());
		bodyAfterXMovement.SetPositionX(bots[i]->GetPositionX() + bots[i]->GetSpeedX());

		bool moveInYAxis = true, moveInXAxis = true;

		switch (bots[i]->bodyInfo.state)
		{
		case PhysicalBody::OnSingleTile:
			if (level->GetCell(bots[i]->bodyInfo.centerX, bots[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY - 1][bots[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY - 1][bots[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis && level->GetCell(bots[i]->bodyInfo.centerX, bots[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY + 1][bots[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY + 1][bots[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInXAxis && level->GetCell(bots[i]->bodyInfo.centerX - 1, bots[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis && level->GetCell(bots[i]->bodyInfo.centerX + 1, bots[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}
			break;

		case PhysicalBody::OnTwoTilesHorizontal:
			int additionTileXCoord;
			if (bots[i]->bodyInfo.leftBound == bots[i]->bodyInfo.centerX)
				additionTileXCoord = bots[i]->bodyInfo.rightBound;
			else
				additionTileXCoord = bots[i]->bodyInfo.leftBound;

			if (moveInYAxis && level->GetCell(bots[i]->bodyInfo.centerX, bots[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY - 1][bots[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY - 1][bots[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}
			else if (moveInYAxis  && level->GetCell(bots[i]->bodyInfo.centerX, bots[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY + 1][bots[i]->bodyInfo.centerX]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY + 1][bots[i]->bodyInfo.centerX]);
				moveInYAxis = false;
			}

			if (moveInYAxis &&level->GetCell(additionTileXCoord, bots[i]->bodyInfo.centerY - 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY - 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY - 1][additionTileXCoord]);
				moveInYAxis = false;
			}
			else if (moveInYAxis &&level->GetCell(additionTileXCoord, bots[i]->bodyInfo.centerY + 1) > CellType::NONE && bodyAfterYMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY + 1][additionTileXCoord]))
			{
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.centerY + 1][additionTileXCoord]);
				moveInYAxis = false;
			}

			break;
		case PhysicalBody::OnTwoTilesVertical:
			int additionTileYCoord;
			if (bots[i]->bodyInfo.upBound == bots[i]->bodyInfo.centerY)
				additionTileYCoord = bots[i]->bodyInfo.downBound;
			else
				additionTileYCoord = bots[i]->bodyInfo.upBound;

			if (moveInXAxis && level->GetCell(bots[i]->bodyInfo.centerX - 1, bots[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis  && level->GetCell(bots[i]->bodyInfo.centerX + 1, bots[i]->bodyInfo.centerY) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.centerY][bots[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			if (moveInXAxis && level->GetCell(bots[i]->bodyInfo.centerX - 1, additionTileYCoord) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[additionTileYCoord][bots[i]->bodyInfo.centerX - 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[additionTileYCoord][bots[i]->bodyInfo.centerX - 1]);
				moveInXAxis = false;
			}
			else if (moveInXAxis &&level->GetCell(bots[i]->bodyInfo.centerX + 1, additionTileYCoord) > CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[additionTileYCoord][bots[i]->bodyInfo.centerX + 1]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[additionTileYCoord][bots[i]->bodyInfo.centerX + 1]);
				moveInXAxis = false;
			}

			break;

		case PhysicalBody::OnFourTiles:
			if (level->GetCell(bots[i]->bodyInfo.leftBound, bots[i]->bodyInfo.upBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.leftBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(bots[i]->bodyInfo.rightBound, bots[i]->bodyInfo.upBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.rightBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.upBound][bots[i]->bodyInfo.rightBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(bots[i]->bodyInfo.leftBound, bots[i]->bodyInfo.downBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.leftBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.leftBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.leftBound]);
				moveInYAxis = false;
			}
			else if (level->GetCell(bots[i]->bodyInfo.rightBound, bots[i]->bodyInfo.downBound)> CellType::NONE && bodyAfterXMovement.isCollision(*levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.rightBound]))
			{
				setBodyPositionNextToAnotherBodyInAxisX(bots[i], levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.rightBound]);
				moveInXAxis = false;
				setBodyPositionNextToAnotherBodyInAxisY(bots[i], levelObjects[bots[i]->bodyInfo.downBound][bots[i]->bodyInfo.rightBound]);
				moveInYAxis = false;
			}
		}
		if (moveInXAxis)
		{
			bots[i]->SetMovementX(movementX);
		}
		if (moveInYAxis)
		{
			bots[i]->SetMovementY(movementY);
		}
	}
}

void PhysicsEngine::setBodyPositionInfo(int id)
{
	players[id]->bodyInfo.centerX = static_cast<int> (players[id]->GetPositionX()) / 64;
	players[id]->bodyInfo.centerY = static_cast<int> (players[id]->GetPositionY()) / 64;

	players[id]->bodyInfo.upBound = static_cast<int> (players[id]->GetPositionY() - players[id]->GetSizeY() / 2) / 64;
	players[id]->bodyInfo.downBound = static_cast<int> (players[id]->GetPositionY() + players[id]->GetSizeY() / 2) / 64;
	players[id]->bodyInfo.leftBound = static_cast<int> (players[id]->GetPositionX() - players[id]->GetSizeX() / 2) / 64;
	players[id]->bodyInfo.rightBound = static_cast<int> (players[id]->GetPositionX() + players[id]->GetSizeX() / 2) / 64;

	if (players[id]->bodyInfo.upBound == players[id]->bodyInfo.downBound && players[id]->bodyInfo.rightBound == players[id]->bodyInfo.leftBound)
		players[id]->bodyInfo.state = PhysicalBody::OnSingleTile;
	else if (players[id]->bodyInfo.upBound != players[id]->bodyInfo.downBound && players[id]->bodyInfo.rightBound == players[id]->bodyInfo.leftBound)
		players[id]->bodyInfo.state = PhysicalBody::OnTwoTilesVertical;
	else if (players[id]->bodyInfo.upBound == players[id]->bodyInfo.downBound && players[id]->bodyInfo.rightBound != players[id]->bodyInfo.leftBound)
		players[id]->bodyInfo.state = PhysicalBody::OnTwoTilesHorizontal;
	else
		players[id]->bodyInfo.state = PhysicalBody::OnFourTiles;
	//std::cout << players[id]->bodyInfo.upBound << " " << players[id]->bodyInfo.downBound << " " << players[id]->bodyInfo.leftBound << " " << players[id]->bodyInfo.rightBound << std::endl;

}

void PhysicsEngine::setBotPositionInfo(int id)
{
	bots[id]->bodyInfo.centerX = static_cast<int> (bots[id]->GetPositionX()) / 64;
	bots[id]->bodyInfo.centerY = static_cast<int> (bots[id]->GetPositionY()) / 64;

	bots[id]->bodyInfo.upBound = static_cast<int> (bots[id]->GetPositionY() - bots[id]->GetSizeY() / 2) / 64;
	bots[id]->bodyInfo.downBound = static_cast<int> (bots[id]->GetPositionY() + bots[id]->GetSizeY() / 2) / 64;
	bots[id]->bodyInfo.leftBound = static_cast<int> (bots[id]->GetPositionX() - bots[id]->GetSizeX() / 2) / 64;
	bots[id]->bodyInfo.rightBound = static_cast<int> (bots[id]->GetPositionX() + bots[id]->GetSizeX() / 2) / 64;

	if (bots[id]->bodyInfo.upBound == bots[id]->bodyInfo.downBound && bots[id]->bodyInfo.rightBound == bots[id]->bodyInfo.leftBound)
		bots[id]->bodyInfo.state = PhysicalBody::OnSingleTile;
	else if (bots[id]->bodyInfo.upBound != bots[id]->bodyInfo.downBound && bots[id]->bodyInfo.rightBound == bots[id]->bodyInfo.leftBound)
		bots[id]->bodyInfo.state = PhysicalBody::OnTwoTilesVertical;
	else if (bots[id]->bodyInfo.upBound == bots[id]->bodyInfo.downBound && bots[id]->bodyInfo.rightBound != bots[id]->bodyInfo.leftBound)
		bots[id]->bodyInfo.state = PhysicalBody::OnTwoTilesHorizontal;
	else
		bots[id]->bodyInfo.state = PhysicalBody::OnFourTiles;
	//std::cout << players[id]->bodyInfo.upBound << " " << players[id]->bodyInfo.downBound << " " << players[id]->bodyInfo.leftBound << " " << players[id]->bodyInfo.rightBound << std::endl;

}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInAxisY(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionY() > tile->GetPositionY())
		body->SetPositionY(tile->GetPositionY() + tile->GetSizeY() / 2 + body->GetSizeY() / 2 + 0.1f);
	else
		body->SetPositionY(tile->GetPositionY() - tile->GetSizeY() / 2 - body->GetSizeY() / 2 - 0.1f);
}

void PhysicsEngine::setBodyPositionNextToAnotherBodyInAxisX(PhysicalBody * body, PhysicalBody * tile)
{
	if (body->GetPositionX() > tile->GetPositionX())
		body->SetPositionX(tile->GetPositionX() + tile->GetSizeX() / 2 + body->GetSizeX() / 2 + 0.1f);
	else
		body->SetPositionX(tile->GetPositionX() - tile->GetSizeX() / 2 - body->GetSizeX() / 2 - 0.1f);
}