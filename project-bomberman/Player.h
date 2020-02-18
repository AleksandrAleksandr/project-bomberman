#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Bomb.h"
#include "LevelView.h"
#include "PhysicalBody.h"
#include "Animator.h"

class Player : public PhysicalBody
{
	sf::Vector2i respawnPos;
public:
	sf::RectangleShape shape;
	sf::Sprite sprite;
	sf::Texture texture;
	
	Level* level;
	Bomb* bomb;
	Bomb* bomb2;
	Animator* animator;

	bool canBeDamaged;
	sf::Clock respawnClock;
	sf::Time respawnSafeTime;
	
	void update(float dt);
	void spawn();
	void Respawn();
	void SetRespawnPos(int x, int y);
	void SetAfterRespawnSafeTime(float value);
	void SetLevel(Level* lvl);
	void SetAnimator(Animator& animator, size_t width, size_t height);
	void BombPlant();
	bool isBombExplosion() const;
	void OnBombCollision();
	Ray* GetRay(unsigned int side);
	void deleteBomb();

	short GetRespawnsCount() const;
	void SetRespawns(short respawns);
	void SetWin(bool val);
	bool GetWin() const;
	bool GetIsAlive() const;
	void SetIsAlive(bool var);
	void SetAlive();

	enum Bonus
	{
		speedPowerUp,
		bombPowerUp,
		none
	};
	void SpeedPowerUp();
	void BombPowerUp();
	sf::Clock bonusClock;
	sf::Time bonusTime;
	Bonus currentBonus;
	bool speedBonus;
	bool bombBonus;

	short respawns;
	short maxNumberOfRespawns;
	bool win;
	bool isAlive;

	float velocityX;
	float velocityY;
	void SetVelocity(float x, float y);
	float GetVelocityX();
	float GetVelocityY();

	int GetPosInTilesX();
	int GetPosInTilesY();
	void draw(sf::RenderWindow* window);
	Player();
	~Player();

	sf::Sound soundHit;
	sf::Sound soundPlant;
	sf::SoundBuffer soundBufferHit;
	sf::SoundBuffer soundBufferPlant;
};

