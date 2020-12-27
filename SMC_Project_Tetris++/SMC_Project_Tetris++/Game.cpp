#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game()
	: IGame(BOARD_WIDTH, BOARD_HEIGHT)
{
	m_board = std::make_unique<Board>(Position{ BOARD_WIDTH,BOARD_HEIGHT }, *this);
	CreateShape();
}

void Game::Run(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Clock clock; // starting the timer-ul
	sf::Time deltaTime(sf::Time::Zero);

	m_board->Clean();

	m_gameplayMusic.play();
	m_gameplayMusic.setLoop(true);

	while (m_renderWindow.isOpen())
	{
		m_gameplayMusic.setVolume((levelSound * 20.f));
		
		if (!m_pause)
		{
			sf::Time trigger(sf::seconds(85.f / (85.f + (m_player->GetLevel() * (m_player->GetLevel() * 5.f)))));
			std::cout << "Trigger =" << trigger.asMilliseconds() << std::endl;
			deltaTime = clock.restart(); // restarting the timer and returning the time passed until this point
			m_elapsedTime += deltaTime;
			std::cout << "m_ElapsedTime = " << m_elapsedTime.asMilliseconds() << std::endl << std::endl;

			ProcessEvents(menuOrGame, levelSound);
			Update(deltaTime);

			if (m_elapsedTime > trigger)
			{
				m_elapsedTime = sf::Time::Zero;
				Proceed(Direction::Down);
				std::cout << "Should go Down" << std::endl;
			}
			Render();
		}
		else
		{
			ProcessEvents(menuOrGame, levelSound);
			Render();
		}
	}
	m_gameplayMusic.stop();
}

void Game::Proceed(Direction direction)
{
	IGame::Proceed(direction);
}

void Game::Update(const sf::Time& dt)
{
	m_board->Update(dt);
	m_player->Update(dt);
	if (!m_tetrisShape)
	{
		if (m_board->IsToRemoveBlocks())
			return;
		CreateShape();
	}
}


void Game::Rotate()
{
	IGame::Rotate();
}

void Game::ScaleUp()
{
	IGame::ScaleUp();
}

void Game::ScaleDown()
{
	IGame::ScaleDown();
}

void Game::CreateShape()
{
	m_tetrisShape.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	//create new game if necessary
	if (m_board->IsOccupied(m_tetrisShape->GetBlockPosition()))
	{
		std::cout << "Game Over" << std::endl;

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("../Resources/Sounds/gameover.wav"))
			std::cout << "Could not load the gameover sound from file !! \n";
		FileWriter("out.txt");

		m_gameplayMusic.stop();
		gameoverMusic.play();

		//system("pause");

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = true;
	}
	m_ID = Utils::GetRandomNumber(7);
	m_preview.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	m_preview->SetPosition(Position{ BOARD_WIDTH, 30 });
}

bool Game::IsValidMovement(std::array<Position, 16> block)
{
	for (int i = 0; i < 16; i++)
	{
		if (block[i].x < 0 || block[i].x > BOARD_WIDTH - 1 || block[i].y > BOARD_HEIGHT - 1)
		{
			std::cout << "INVALID" << std::endl;
			return false;
		}
		if (IsOccupied(block[i].x, block[i].y))
		{
			std::cout << "INVALID" << std::endl;
			return false;
		}
	}
	std::cout << "VALID" << std::endl;
	return true;
}

bool Game::IsOccupied(int x, int y)
{
	return IGame::IsOccupied(x, y);
}

void Game::ProcessEvents(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Event e;
	while (m_renderWindow.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			menuOrGame = 1;
			m_renderWindow.close();
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (!m_pause)
			{
				if (e.key.code == sf::Keyboard::Down)
					Proceed(Direction::Down);
				else if (e.key.code == sf::Keyboard::Left)
					Proceed(Direction::Left);
				else if (e.key.code == sf::Keyboard::Right)
					Proceed(Direction::Right);
				else if (e.key.code == sf::Keyboard::Up)
					Rotate();
				else if (e.key.code == sf::Keyboard::A)
					ScaleUp();
				else if (e.key.code == sf::Keyboard::Z)
					ScaleDown();
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_renderWindow.close();
				}
				else if (e.key.code == sf::Keyboard::Space)
					m_pause = true;
			}
			else
			{
				if (e.key.code == sf::Keyboard::Enter)
					m_pause = false;
				else if (e.key.code == sf::Keyboard::O)
				{
					Options options;
					options.RunOptions(levelSound);
				}
				else if (e.key.code == sf::Keyboard::Escape)
				{
					menuOrGame = 1;
					m_renderWindow.close();
				}
			}
		}
	}
}

void Game::Render()
{
	m_renderWindow.clear(sf::Color::Black);
	m_player->Draw(m_renderWindow);
	m_board->Draw(m_renderWindow);
	if (m_tetrisShape)
		m_renderWindow.draw(*m_tetrisShape);
	m_renderWindow.draw(*m_preview);
	m_renderWindow.draw(m_separationLine);
	if (m_pause)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (int i = 0; i < 4; i++)
			m_renderWindow.draw(m_textPauseMenu[i]);
	}
	m_renderWindow.display();
}

void Game::FileWriter(std::string file)
{
	std::fstream fileOut;
	fileOut.open(file, std::fstream::app);
	if (!fileOut.is_open())
	{
		std::cout << "File cannot be opened!\n";
		return;
	}
	fileOut << m_player->GetPlayerName() << " " << m_player->GetScore() << "\n";
	
}

