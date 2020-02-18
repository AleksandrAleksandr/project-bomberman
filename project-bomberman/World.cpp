#include "World.h"
#include "iostream"

World::World(sf::RenderWindow* window_)
{
	window = window_;
	playersNumber = 2;
	botsNumber = 5;
}

World::~World()
{
	delete level;
	delete levelView;
	delete physicsEngine;
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		delete players[i];
	}
	for (unsigned int i = 0; i < bots.size(); ++i)
	{
		delete bots[i];
	}
	delete bombManager;
	delete bonusManager;
	delete font;
	delete gui;
}

void World::init()
{
	//window = new sf::RenderWindow(sf::VideoMode(15 * 64, 11 * 64), "game");
	window->setFramerateLimit(30);
	level = new Level();
	levelView = new LevelView();
	physicsEngine = new PhysicsEngine();
	bombManager = new BombManager();
	bonusManager = new BonusManager;
	gui = new GUI();

	for (int i = 0; i < playersNumber; i++)
		players.push_back(new Player());

	/*level->loadFromFile("level2.txt");
	level->FillBlocks();
	levelView->setLevel(level);
	level->SetLevelView(levelView);*/

	for (int i = 0; i < botsNumber; i++)
		bots.push_back(new Bot());

	initGameplay();

	/*for (int i = 0; i < players.size(); i++)
	{
		/*texture.loadFromFile("EAST_00.png");
		players_animators[i]->AddAnimationState("EAST", texture);
		texture.loadFromFile("NORTH_00.png");
		players_animators[i]->AddAnimationState("NORTH", texture);
		texture.loadFromFile("WEST_00.png");
		players_animators[i]->AddAnimationState("WEST", texture);
		texture.loadFromFile("SOUTH_00.png");
		players_animators[i]->AddAnimationState("SOUTH", texture);
		players_animators[i]->SetLoop(true);

		/*players[i]->SetAnimator(*players_animators[i], 48, 48);
		players_animators[i]->ChangeActiveState("EAST");
		players_animators[i]->Stop();
		players_animators[i]->SetDelayBetweenFrames(0.1f);
		players[i]->SetRespawnPos(12*i + 1, 8*i + 1);
		players[i]->SetAfterRespawnSafeTime(2.5f);
		players[i]->SetLevel(level);
		players[i]->SetAlive();
		players[i]->spawn();
	}*/

	/*for (int i = 0; i < bots.size(); i++)
	{
		bots[i]->SetLevel(level);
		bots[i]->SetPlayers(&players);
		bots[i]->FindFreeTiles();
		bots[i]->spawn();
	}*/

	//physicsEngine->Init(level, &players, &bots);
	bombManager->Init(level, &players, &bots);
	//bonusManager->Init(level, &players, &bots);

	font = new sf::Font();
	font->loadFromFile("Cat.ttf");
	gui->Init(font, 30, window->getSize().x, window->getSize().y, &playAgain, &exit, &enterMenu);

	music.openFromFile("game.wav");
	music.play();
	music.setLoop(true);
}

void World::handleEvents()
{
	if (exit)
	{
		return;
	}

	if (!endOfGame)
	{
		std::pair<int, int> input[2];

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			input[0].first = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			input[0].first = 1;

		// handle vertical axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			input[0].second = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			input[0].second = 1;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			input[1].first = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			input[1].first = 1;

		// handle vertical axis
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			input[1].second = -1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			input[1].second = 1;

		for (int i = 0; i < players.size(); i++)
		{
			players[i]->SetSpeed(input[i].first * players[i]->GetVelocityX(), input[i].second * players[i]->GetVelocityY());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			players[0]->BombPlant();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
			players[1]->BombPlant();
	}
	sf::Event event;

	while (window->pollEvent(event))
	{
		gui->processEvents(sf::Mouse::getPosition(*window), &event);
		if (event.type == sf::Event::Closed)
		{
			//window->close();
			exit = true;
			enterMenu = false;
			break;
		}
		// handle more events
	}
}

bool World::start()
{
	exit = false;
	sf::Clock clock;
	while (!exit)
	{
		handleEvents();
		float dt = clock.getElapsedTime().asSeconds();
		update(dt);
		draw();
	}
	return enterMenu;
}

void World::update(float dt)
{
	physicsEngine->Update();

	for (short i = 0; i < players.size(); i++)
	{
		if (!endOfGame)
			players[i]->update(dt);

		if (!players[i]->GetIsAlive())
		{
			endOfGame = true;
			if (i == 0)
			{
				players[1]->SetWin(true);
				break;
			}
			players[0]->SetWin(true);
			break;
		}
	}
	for (short i = 0; i < bots.size(); i++)
	{
		if (!endOfGame)
			bots[i]->update();
	}

	bombManager->Update(0);
	bonusManager->Update(0);

	if (endOfGame && !exit)
	{
		gui->UpdateStats(&players, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y, playAgain, exit, enterMenu);
	}
	else
	{
		gui->UpdateStats(&players, sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	}

	if (endOfGame && playAgain)
	{
		initGameplay();
	}
}

void World::initGameplay()
{
	for (int i = 0; i < 2; ++i)
	{
		players[i]->deleteBomb();
	}
	
	if (!level->loadFromFile("level2.txt"))
	{
		std::cerr << "[!] Cannot load file: \"" << "level2.txt" << "\". Exiting...\n";
		std::cin.get();
		std::exit(1);
	}
	level->FillBlocks();
	levelView->setLevel(level);
	level->SetLevelView(levelView);

	for (int i = 0; i < 2; ++i)
	{
		players[i]->SetRespawns(3);
		//players[i]->SetUpBomb(m_atlases[1], m_atlases[2]);
		players[i]->SetLevel(level);

		if (!i)
			players[i]->SetRespawnPos(1, 1);
		else
			players[i]->SetRespawnPos(level->GetWidth() - 2, level->GetHeight() - 2);
		players[i]->SetAfterRespawnSafeTime(2.5f);
		players[i]->spawn();
		players[i]->update(0);
		players[i]->SetWin(false);
		players[i]->SetAlive();
	}
	for (int i = 0; i < bots.size(); i++)
	{
	bots[i]->SetLevel(level);
	bots[i]->SetPlayers(&players);
	bots[i]->FindFreeTiles();
	bots[i]->spawn();
	}

	endOfGame = false;
	playAgain = false;

	physicsEngine->Init(level, &players, &bots);
	bonusManager->Init(level, &players, &bots);
}

void World::draw()
{
	window->clear();
	levelView->draw(window);

	for (unsigned i = 0; i < players.size(); ++i)
	{
		players[i]->draw(window);
	}
	for (unsigned i = 0; i < bots.size(); ++i)
	{
		bots[i]->draw(window);
	}
	bonusManager->draw(window);
	gui->draw(window);
	window->display();
}
