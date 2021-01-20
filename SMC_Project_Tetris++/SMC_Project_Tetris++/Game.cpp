#include "Game.h"
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include "Highscore.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <chrono>

Game::Game()
	: IGame(BOARD_WIDTH, BOARD_HEIGHT)
{
	if (!m_backGroundTexture.loadFromFile("../Resources/Images/tetris_board1P.jpg"))
	{
		std::cout << "Could not load texture from file in Game !! \n";
	}
	m_backGroundTexture.setSmooth(true);
	m_backGroundSprite.setTexture(m_backGroundTexture);
	m_backGroundSprite.setColor(sf::Color(255, 255, 255, 160));
	m_backGroundSprite.setOrigin(0.75, 0);

	m_pauseMenu.setSize(sf::Vector2f{ 290.f,200.f });

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

	auto start = std::chrono::system_clock::now();
	auto randomTime = Utils::GetRandomNumber(10, 20);
	auto randomTimeDH = Utils::GetRandomNumber(10, 20);
	auto pos_x = Utils::GetRandomNumber(0, BOARD_WIDTH - 1);
	auto pos_y = Utils::GetRandomNumber(0, BOARD_HEIGHT - 1);

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

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> duration = end - start;
			std::chrono::duration<double> durationDH = end - start;
			if (duration.count() >= randomTime)
			{
				std::cout << std::endl << duration.count();
				start = std::chrono::system_clock::now();
				AddSpecialShape();
				randomTime = Utils::GetRandomNumber(10, 20);
				std::cout << std::endl << randomTime;
			}

			if (durationDH.count() >= randomTimeDH)
			{
				m_board->GenerateDarkHole(DARKHOLE_TEXTURE_ID, Position{ pos_x, pos_y });
				auto end = std::chrono::system_clock::now();
				durationDH = end - start;
				randomTimeDH = Utils::GetRandomNumber(5, 10);
				if (durationDH.count() >= randomTimeDH)
				{
					m_board->DestroyDarkHole(Position{ pos_x, pos_y });
					randomTimeDH = Utils::GetRandomNumber(10, 20);
					pos_x = Utils::GetRandomNumber(0, BOARD_WIDTH - 1);
					pos_y = Utils::GetRandomNumber(0, BOARD_HEIGHT - 1);
				}
			}

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

void Game::AddSpecialShape()
{
	std::pair<uint16_t, uint16_t> field = GetFreePosition(Utils::GetRandomNumber(0, BOARD_WIDTH-1), BOARD_HEIGHT);
	Position block(field.first, field.second);
	m_board->AddSpecialBlock(SPECIALSHAPE_TEXTURE_ID, block);
	return;
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
		FileWriter("../Resources/Files/outputPlayers1P.txt");

		m_gameplayMusic.stop();
		gameoverMusic.play();

		//system("pause");

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = 2;
	}
	m_ID = Utils::GetRandomNumber(7);
	m_preview.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	m_preview->SetPosition(Position{ BOARD_WIDTH, 30 });
}

bool Game::IsValidMovement(std::array<Position, BLOCK_ARRAY_COLUMNS> block)
{
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
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

bool Game::IsOccupied(uint16_t x, uint16_t y)
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

		if (m_pause == 3) {
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode == 13)
				{
					m_pause = 0;
				}
				if (e.text.unicode == 8 && !m_playerNameInput1.isEmpty())
				{
					m_playerNameInput1.erase(m_playerNameInput1.getSize() - 1, 1);
					m_playerNameText.setString(m_playerNameInput1);
				}
				else if (e.text.unicode > 64 && e.text.unicode < 91 || e.text.unicode > 96 && e.text.unicode < 123)
				{
					if (m_playerNameInput1.getSize() < 9)
						m_playerNameInput1 += e.text.unicode;
					m_playerNameText.setString(m_playerNameInput1);
				}
			}
			m_renderWindow.draw(m_playerNameText);
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (m_pause == 0)
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
					m_pause = 1;
			}
			else
			{
				if (e.key.code == sf::Keyboard::Enter)
					m_pause = 0;
				else if (e.key.code == sf::Keyboard::O)
				{
					Options options;
					options.RunOptions(levelSound);
				}
				else if (e.key.code == sf::Keyboard::H)
				{
					Highscore highscore(0);
					highscore.runHighscore();
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
	if (m_pause == 0)
	{
		m_renderWindow.clear(sf::Color::Black);
		m_renderWindow.draw(m_backGroundSprite);
		m_player->Draw(m_renderWindow);
		m_board->Draw(m_renderWindow);
		if (m_tetrisShape)
			m_renderWindow.draw(*m_tetrisShape);
		m_renderWindow.draw(*m_preview);
		m_renderWindow.draw(m_separationLine);
	}
	else if (m_pause == 1)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (uint16_t i = 0;i < 5;i++)
			m_renderWindow.draw(m_textPauseMenu[i]);
	}
	else if (m_pause == 2)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (uint16_t i = 0;i < 5;i++)
			m_renderWindow.draw(m_textGameOverMenu[i]);
	}
	else if (m_pause == 3)
	{
		m_renderWindow.draw(m_pauseMenu);
		m_renderWindow.draw(m_playerNameBox);
		m_renderWindow.draw(m_playerNameText);
		m_player = std::make_unique<Player>(m_playerNameInput1, BOARD_WIDTH, BOARD_HEIGHT);
	}
	m_renderWindow.display();
}

void Game::FileWriter(const std::string& file)
{
	std::fstream fileOut;
	fileOut.open(file, std::fstream::app);
	if (!fileOut.is_open())
	{
		std::cout << "File cannot be opened!\n";
		return;
	}
	fileOut << '\n' << m_player->GetPlayerName() << " " << m_player->GetScore();

}

