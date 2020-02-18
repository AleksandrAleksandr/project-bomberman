#include "Botton.h"
#pragma warning(disable : 4996)

Botton::Botton(sf::Vector2f position, sf::Vector2i size, std::string pressTexture_src, std::string unpressTexture_src, std::string text)
{
	m_position = position;
	m_size = size;

	m_pressTexture.loadFromFile(pressTexture_src);
	m_unpressTexture.loadFromFile(unpressTexture_src);

	m_pressSprite.setTexture(m_pressTexture);
	m_unpressSprite.setTexture(m_unpressTexture);

	m_pressSprite.setScale(sf::Vector2f((float)size.x / (float)m_pressTexture.getSize().x, (float)size.y / (float)m_pressTexture.getSize().y));
	m_unpressSprite.setScale(sf::Vector2f((float)size.x / (float)m_pressTexture.getSize().x, (float)size.y / (float)m_pressTexture.getSize().y));

	m_font.loadFromFile("ahronbd.ttf");
	m_text.setFont(m_font);
	m_text.setString(text);
	m_text.setColor(sf::Color(0.f, 107, 139));

	m_pressSprite.setPosition(position);
	m_unpressSprite.setPosition(position);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f, 0);
	m_text.setPosition(sf::Vector2f((position.x + size.x / 2.f), position.y + size.y / 4));
}

Botton::~Botton()
{
}

bool Botton::Check(sf::Vector2i mousePosition)
{
	if (mousePosition.x > m_position.x && mousePosition.x < m_position.x + m_size.x)
	{
		if (mousePosition.y > m_position.y && mousePosition.y < m_position.y + m_size.y)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

void Botton::DoAction()
{
}

void Botton::Update(sf::Vector2i mousePosition, bool buttonPressed)
{
	if (Check(mousePosition) && buttonPressed) m_press = true;
	else if (Check(mousePosition) && !buttonPressed)
	{
		m_press = false;
		DoAction();
	}
	else m_press = false;
}

sf::Sprite* Botton::GetSpritePointer()
{
	if (m_press) return &m_pressSprite;
	else return &m_unpressSprite;
}

sf::Text* Botton::GetTextPointer()
{
	return &m_text;
}
