#include "Menu.h"
#include <iostream>

using namespace std;

/*void Menu::options()
{
	volume = m_volumeSlider->GetValue() * 100.f;

	if (m_volumeSlider->GetValue() == 0)
	{
		m_volumeSlider->SetValue(0.6f);
		volume = 60;
	}
	else if (volume < 10.f)
	{
		volume = 0;
	}
	else if (volume > 87.f)
	{
		volume = 100;
	}
	m_music.setVolume(volume);
	optionsText[3].setString(std::to_string(static_cast<int>(volume)) + '%');

	playersLives = m_playersSlider->GetValue() * 5.f;
	if (m_playersSlider->GetValue() == 0)
	{
		m_playersSlider->SetValue(0.2f);
		playersLives = 2;
	}
	else if (playersLives < 0.6f)
	{
		playersLives = 0;
	}
	else if (playersLives >= 4.5f)
	{
		playersLives = 5;
	}
	playersLives = static_cast<int>(playersLives) + 1;
	optionsText[2].setString(std::to_string(static_cast<int>(playersLives)));

}*/

Menu::Menu(size_t width, size_t height)
{
	m_window = new sf::RenderWindow();
	m_windowWidth = width;
	m_windowHeight = height;
	m_window->create(sf::VideoMode(static_cast<int>(m_windowWidth), static_cast<int>(m_windowHeight)), "Bomberman", sf::Style::Close);
	m_window->setFramerateLimit(60);

	/*sf::Image icon;
	icon.loadFromFile("icon.png");
	m_window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());*/

	m_buttonsPointers[0] = new Botton(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 2.3f - 50), sf::Vector2i(300, 75.f), "pressButton.png", "unpressButton.png", "START");
	//m_buttonsPointers[1] = new Botton(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f - 50), sf::Vector2i(300, 75.f), "pressButton.png", "unpressButton.png", "OPTIONS");
	m_buttonsPointers[3] = new Botton(sf::Vector2f(m_window->getSize().x / 2 - 150, m_window->getSize().y / 1.7f + 200 - 150), sf::Vector2i(300, 75.f), "pressButton.png", "unpressButton.png", "EXIT");

	//m_backgroundTexture.loadFromFile("menuBackground.png");
	m_backgroundTexture.loadFromFile("title_background.jpg");
	m_backgroundTexture.setSmooth(true);
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setScale(sf::Vector2f(m_window->getSize().x / 1080, m_window->getSize().y / 1365));
	m_backgroundSprite.setScale(sf::Vector2f((float)m_window->getSize().x / (float)m_backgroundTexture.getSize().x, (float)m_window->getSize().y / (float)m_backgroundTexture.getSize().y));

	m_gameLogoTexture.loadFromFile("menuLogo.png");
	m_gameLogoTexture.setSmooth(true);
	m_gameLogoSprite.setTexture(m_gameLogoTexture);
	m_gameLogoSprite.setScale(sf::Vector2f((float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f, (float)m_window->getSize().y / (float)m_gameLogoTexture.getSize().y / 7.f));
	m_gameLogoSprite.setPosition(sf::Vector2f(m_window->getSize().x / 2.f - (m_gameLogoTexture.getSize().x * m_gameLogoSprite.getScale().x) / 2.f, m_window->getSize().y / 5.f - 30));

	if (!m_music.openFromFile("menu.wav"))
	{
		std::cerr << "[!] Cannot load resource: 'menu.wav'" << std::endl;
		std::cin.get();
		std::exit(1);
	}

	m_music.play();
	m_music.setLoop(true);
	//m_music.setVolume(volume);

	m_optionReturnButton = new Botton(sf::Vector2f(25, m_windowHeight - 100), sf::Vector2i(300, 75), "pressButton.png", "unpressButton.png", "RETURN TO MENU");
}

Menu::~Menu()
{
}

void Menu::Run()
{
	m_exit = false;

	while (!m_exit)
	{
		draw();
		processEvents();

		/*if (m_options)
			options();*/

	}
}

void Menu::draw()
{
	//m_window->clear(sf::Color::White);

	m_window->draw(m_backgroundSprite);

	m_window->draw(m_backgroundSprite);

	m_window->draw(m_gameLogoSprite);

	m_window->draw(*m_buttonsPointers[0]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[0]->GetTextPointer());

	//m_window->draw(*m_buttonsPointers[1]->GetSpritePointer());
	//m_window->draw(*m_buttonsPointers[1]->GetTextPointer());

	m_window->draw(*m_buttonsPointers[3]->GetSpritePointer());
	m_window->draw(*m_buttonsPointers[3]->GetTextPointer());

	m_window->display();
}

void Menu::processEvents()
{
	sf::Event event;
	sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*m_window).x, sf::Mouse::getPosition(*m_window).y);
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_exit = true;
			break;
		}
		/*if (m_options)
		{
			m_playersSlider->Update(sf::Mouse::getPosition(*m_window), &event);
			m_volumeSlider->Update(sf::Mouse::getPosition(*m_window), &event);
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && !m_credits)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), false);
				if (m_optionReturnButton->GetSpritePointer()->getGlobalBounds().contains(mouse))
					m_options = false;
			}
		}*/
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), false);
			//m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), false);
			//m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), false);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), false);

			if (m_buttonsPointers[0]->GetSpritePointer()->getGlobalBounds().contains(mouse))
			{
				m_music.stop();
				world = new World(m_window);
				world->init();
				//m_game->Initialize(volume, volume, playersLives);
				m_exit = !world->start();
				m_music.play();
				delete world;
				return;
			}
			else
			{
				if (m_buttonsPointers[3]->GetSpritePointer()->getGlobalBounds().contains(mouse))
					m_exit = true;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			if (m_options)
			{
				m_optionReturnButton->Update(sf::Mouse::getPosition(*m_window), true);
				break;
			}

			m_buttonsPointers[0]->Update(sf::Mouse::getPosition(*m_window), true);
			//m_buttonsPointers[1]->Update(sf::Mouse::getPosition(*m_window), true);
			//m_buttonsPointers[2]->Update(sf::Mouse::getPosition(*m_window), true);
			m_buttonsPointers[3]->Update(sf::Mouse::getPosition(*m_window), true);
		}

		if (m_options)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_options = false;
	}
}