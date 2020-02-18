#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"
#include "Botton.h"

class GUI
{
public:
	GUI();
	~GUI();
	void Init(sf::Font* font, short textSize, int screenWidth, int screenHeight, bool* playAgain, bool* exit, bool* enterMenu);
	void UpdateStats(std::vector<Player*> * players, short mouseX, short mouseY);
	void UpdateStats(std::vector<Player*> * players, short mouseX, short mouseY, bool & playAgain, bool & exit, bool & enterMenu);
	void processEvents(sf::Vector2i mousePos, sf::Event* eventPointer);
	void draw(sf::RenderWindow * window) const;

private:
	int m_screenWidth;
	int m_screenHeight;

	Botton* m_returnToMenuButton;
	Botton* m_playAgainButton;
	Botton* m_exitButton;

	sf::Texture* m_frameTexture;
	sf::Sprite* m_frame;

	sf::RectangleShape* rect;

	sf::Text* m_winnerText;

	bool m_endOfGameMenuView;
	bool m_gameGUIView;

	bool* m_playAgain;
	bool* m_exit;
	bool* m_enterMenu;

	int m_whoWin;

	sf::Text* m_playerOneLives;

	sf::Text* m_playerSecondLives;
};

