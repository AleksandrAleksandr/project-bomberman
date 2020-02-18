#include "Player.h"

Player::Player()
{
	sizeX = 48;
	sizeY = 48;
	SetVelocity(5, 5);
	texture.loadFromFile("man.png");
	sprite.setPosition(GetPositionX(), GetPositionY());
	sprite.setOrigin(sizeX / 2, sizeY / 2);
	sprite.setTexture(texture);

	canBeDamaged = true;
	respawns = maxNumberOfRespawns = 2;
	bonusTime = sf::seconds(8);
	currentBonus = Bonus::none;
	speedBonus = false;
	bombBonus = false;

	soundBufferHit.loadFromFile("hurt.wav");
	soundBufferPlant.loadFromFile("plant.wav");
	soundHit.setBuffer(soundBufferHit);
	soundPlant.setBuffer(soundBufferPlant);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	//animator->Animate(dt);
	SetPositionX(GetPositionX() + movementX);
	SetPositionY(GetPositionY() + movementY);
	sprite.setPosition(GetPositionX(), GetPositionY());

	if (bomb != nullptr)
	{
		bomb->update();

		if (bomb->GetState() == Bomb::exploding)
		{

		}
		if (bomb->GetState() == Bomb::exploded)
		{
			delete bomb;
			bomb = nullptr;
		}
	}
	if (bomb2 != nullptr)
	{
		bomb2->update();

		if (bomb2->GetState() == Bomb::exploding)
		{

		}
		if (bomb2->GetState() == Bomb::exploded)
		{
			delete bomb2;
			bomb2 = nullptr;
		}
	}
	if (respawns > 0 && respawns < maxNumberOfRespawns && (respawnClock.getElapsedTime() > respawnSafeTime))
	{
		canBeDamaged = true;
	}
	else if (respawns <= 0 && isAlive)
	{
		//endGame();
		isAlive = false;
	}
	else
		isAlive = true;

	if (bonusClock.getElapsedTime() > bonusTime)
	{
		if (speedBonus)
		{
			SetVelocity(5, 5);
			currentBonus = Bonus::none;
			speedBonus = false;
		}
	}
}

void Player::draw(sf::RenderWindow* window)
{
	window->draw(sprite);
	if (bomb != nullptr)
		bomb->draw(window);
	if (bomb2 != nullptr)
		bomb2->draw(window);
}

void Player::SetVelocity(float x, float y)
{
	velocityX = x;
	velocityY = y;
}
float Player::GetVelocityX()
{
	return velocityX;
}
float Player::GetVelocityY()
{
	return velocityY;
}

int Player::GetPosInTilesX()
{
	return (static_cast<int> (GetPositionX() / 64));
}

int Player::GetPosInTilesY()
{
	return (static_cast<int> (GetPositionY() / 64));
}

void Player::SetRespawnPos(int x, int y)
{
	respawnPos.x = x;
	respawnPos.y = y;
}

void Player::SetAfterRespawnSafeTime(float value)
{
	respawnSafeTime = sf::seconds(value);
}

void Player::SetLevel(Level* lvl)
{
	level = lvl;
}

void Player::spawn()
{
	SetPositionX(static_cast<int>(respawnPos.x * 64 + 64 / 2));
	SetPositionY(static_cast<int>(respawnPos.y * 64 + 64 / 2));
}

void Player::Respawn()
{
	canBeDamaged = false;
	respawnClock.restart();
	spawn();
	respawns--;
	soundHit.play();
}

void Player::SetRespawns(short hp)
{
	respawns = maxNumberOfRespawns = hp;
}

void Player::deleteBomb()
{
	delete bomb;
	bomb = nullptr;
}

void Player::BombPlant()
{
	if (bomb == nullptr)
	{
		bomb = new Bomb;
		bomb->SetPosition(static_cast<int> (GetPositionX()), static_cast<int> (GetPositionY()));
		bomb->SetLevel(level);
		bomb->SetDetonationTime(sf::seconds(3));
		soundPlant.play();
		return;
	}
	if (bombBonus && bomb2 == nullptr)
	{
		std::cout << " bomb 2\n";
		bomb2 = new Bomb;
		bomb2->SetPosition(static_cast<int> (GetPositionX()), static_cast<int> (GetPositionY()));
		bomb2->SetLevel(level);
		bomb2->SetDetonationTime(sf::seconds(2.5));
		soundPlant.play();
		bombBonus = false;
	}
}

bool Player::isBombExplosion() const
{
	return (bomb != nullptr && bomb->GetState() == Bomb::exploding);
}

void Player::OnBombCollision()
{
	if (canBeDamaged)
		Respawn();
}

Ray* Player::GetRay(unsigned int side)
{
	return (bomb->GetRay(side));
}

void Player::SpeedPowerUp()
{
	std::cout << "Speed poweUpp!!\n";
	currentBonus = Bonus::speedPowerUp;
	speedBonus = true;
	bonusClock.restart();
	SetVelocity(GetVelocityX() * 2, GetVelocityY() * 2);
}

void Player::BombPowerUp()
{
	std::cout << "Bomb bonus!!\n";
	currentBonus = Bonus::bombPowerUp;
	bombBonus = true;
}

short Player::GetRespawnsCount() const
{
	return respawns;
}

void Player::SetWin(bool val)
{
	win = val;
}

bool Player::GetWin() const
{
	return win;
}

bool Player::GetIsAlive() const
{
	return isAlive;
}

void Player::SetIsAlive(bool var)
{
	isAlive = var;
}

void Player::SetAlive()
{
	isAlive = true;
	canBeDamaged = true;
}


void Player::SetAnimator(Animator& animator_, size_t width, size_t height)
{
	float w = static_cast<float>(width);
	float h = static_cast<float>(height);

	float tileSize = 64; // HACK tmp only

	sprite.setOrigin(w / 2.f, h / 2.f);
	SetSize(w, h);

	animator = &animator_;
	animator->SetSprite(sprite);
	//sprite.setPosition(sf::Vector2f(3 * tileSize + w, 5 * tileSize + h));
}