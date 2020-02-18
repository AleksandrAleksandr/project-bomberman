#include "Ray.h"


void Ray::draw(sf::RenderWindow* window) const
{
	window->draw(sprite);
}

Ray::Ray(Side side)
	:side(side)
{
	/*sf::Texture texture;
	texture.loadFromFile("sample_raytextures.png");
	sprite.setTexture(texture);*/
	texture.loadFromFile("sample_raytextures.png");
	sprite.setTexture(texture);
}

Ray::~Ray()
{
}

int Ray::GetSide()
{
	return side;
}

void Ray::SetRaySpriteSize(unsigned short size)
{
	size = size;
	sprite.setTextureRect(sf::IntRect(0, 0, size*TILE_SIZE, TILE_SIZE));
	sprite.setOrigin(0, sprite.getGlobalBounds().height / 2.f);
	sprite.getTexture();
	switch (side)
	{
	case Ray::Up:
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - TILE_SIZE / 2);
		sprite.setRotation(270); 
		SetSize(TILE_SIZE, TILE_SIZE*size + TILE_SIZE);
		SetPositionY(static_cast<int>(GetPositionY() / TILE_SIZE) * TILE_SIZE);
		PhysicalBody::SetPositionY(GetPositionY() - ((TILE_SIZE*size) + TILE_SIZE) / 2 + TILE_SIZE);
		break;
	case Ray::Down:
		SetPositionY(static_cast<int>(GetPositionY() / TILE_SIZE) * TILE_SIZE);
		sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + TILE_SIZE / 2);
		sprite.setRotation(90);
		SetSize(TILE_SIZE, TILE_SIZE*size);
		PhysicalBody::SetPositionY(GetPositionY() + TILE_SIZE + (TILE_SIZE*size) / 2);
		break;
	case Ray::Left:
		SetPositionX(static_cast<int>(GetPositionX() / TILE_SIZE) * TILE_SIZE);
		sprite.setPosition(sprite.getPosition().x - TILE_SIZE / 2, sprite.getPosition().y);
		sprite.setRotation(180);
		SetSize(TILE_SIZE*size, TILE_SIZE);
		PhysicalBody::SetPositionX(GetPositionX() - (TILE_SIZE*size) / 2);
		break;
	case Ray::Right:
		SetPositionX(static_cast<int>(GetPositionX() / TILE_SIZE) * TILE_SIZE);
		sprite.setPosition(sprite.getPosition().x + TILE_SIZE / 2, sprite.getPosition().y);
		SetSize(TILE_SIZE*size, TILE_SIZE);
		PhysicalBody::SetPositionX(GetPositionX() + TILE_SIZE + (TILE_SIZE*size) / 2);
		break;
	default:
		break;
	}

}

void Ray::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
	PhysicalBody::SetPositionX(x);
	PhysicalBody::SetPositionY(y);
}