#pragma once

class PhysicalBody
{
public:
	PhysicalBody();
	~PhysicalBody();

	enum BodyPositionState{ OnSingleTile, OnTwoTilesHorizontal, OnTwoTilesVertical, OnFourTiles };

	struct BodyInfo
	{
		BodyPositionState state;

		unsigned int upBound;
		unsigned int downBound;
		unsigned int leftBound;
		unsigned int rightBound;
		unsigned int centerX;
		unsigned int centerY;
	};

	BodyInfo bodyInfo;

	bool isCollision(float x, float y, float sizeX, float sizeY);
	bool isCollision(PhysicalBody& body);
	float GetPositionX() const;
	float GetPositionY() const;
	float GetSizeX() const;
	float GetSizeY() const;
	float GetSpeedX() const;
	float GetSpeedY() const;

	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetSize(float x, float y);
	void SetSpeed(float x, float y);
	void SetMovementX(float movement);
	void SetMovementY(float movement);

protected:
	float posX;
	float posY;

	float sizeX;
	float sizeY;

	float speedX;
	float speedY;

	float movementX;
	float movementY;
};

