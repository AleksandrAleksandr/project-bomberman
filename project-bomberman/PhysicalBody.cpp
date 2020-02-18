#include "PhysicalBody.h"

PhysicalBody::PhysicalBody()
{
	posX = posY = sizeX = sizeY = speedX = speedY = 0;
}

PhysicalBody::~PhysicalBody()
{
}

bool PhysicalBody::isCollision(float x, float y, float sizeX_, float sizeY_)
{
	return !(posY + sizeY / 2 < y - sizeY_ / 2) && !(posY - sizeY / 2 > y + sizeY_ / 2) &&
		!(posX + sizeX / 2 < x - sizeX_ / 2) && !(posX - sizeX / 2 > x + sizeX_ / 2);
}

bool PhysicalBody::isCollision(PhysicalBody& body)
{
	return isCollision(body.posX, body.posY, body.sizeX, body.sizeY);
}

float PhysicalBody::GetPositionX() const
{
	return posX;
}

float PhysicalBody::GetSizeX() const
{
	return sizeX;
}

float PhysicalBody::GetSizeY() const
{
	return sizeY;
}

float PhysicalBody::GetSpeedX() const
{
	return speedX;
}

float PhysicalBody::GetSpeedY() const
{
	return speedY;
}

float PhysicalBody::GetPositionY() const
{
	return posY;
}

void PhysicalBody::SetPositionX(float x)
{
	posX = x;
}

void PhysicalBody::SetPositionY(float y)
{
	posY = y;
}

void PhysicalBody::SetSize(float x, float y)
{
	sizeX = x;
	sizeY = y;
}

void PhysicalBody::SetSpeed(float x, float y)
{
	speedX = x;
	speedY = y;
}

void PhysicalBody::SetMovementX(float movement)
{
	movementX = movement;
}

void PhysicalBody::SetMovementY(float movement)
{
	movementY = movement;
}
