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
	sf::Clock clock; // starting the timer
	sf::Time deltaTime(sf::Time::Zero);

	m_board->Clean();

	m_gameplayMusic.play();
	m_gameplayMusic.setLoop(true);

	bool existsDH = false;
	auto copyDurationDH = 0;
	auto start = std::chrono::system_clock::now();
	auto startDH = std::chrono::system_clock::now();
	auto startDestroy = std::chrono::system_clock::now();
	auto randomTime = Utils::GetRandomNumber(10, 20);
	auto randomTimeDH = Utils::GetRandomNumber(10, 20);
	auto pos_x = Utils::GetRandomNumber(0, BOARD_WIDTH - 1);
	auto pos_y = Utils::GetRandomNumber(15, BOARD_HEIGHT - 1);
	uint16_t initialLines = 0;
	uint16_t finalLines = 0;
	uint16_t linesDifference = 0;

	while (m_renderWindow.isOpen())
	{
		m_gameplayMusic.setVolume((levelSound * 20.f));
		m_gameoverMusic.setVolume((levelSound * 20.f));
		m_board->m_clearLinesMusic.setVolume((levelSound * 20.f));

		if (!m_pause)
		{
			sf::Time trigger(sf::seconds(85.f / (85.f + (m_player->GetLevel() * (m_player->GetLevel() * 5.f)))));
			deltaTime = clock.restart(); // restarting the timer and returning the time passed until this point
			m_elapsedTime += deltaTime;

			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> duration = end - start;
			std::chrono::duration<double> durationDH = end - startDH;
			std::chrono::duration<double> durationDestroy = end - startDestroy;
			if (duration.count() >= randomTime)
			{
				start = std::chrono::system_clock::now();
				AddSpecialShape();
				randomTime = Utils::GetRandomNumber(10, 20);
			}

			if (durationDH.count() >= randomTimeDH)
			{
				copyDurationDH = randomTimeDH;
				startDH = std::chrono::system_clock::now();
				m_board->GenerateDarkHole(DARKHOLE_TEXTURE_ID, Position{ pos_x, pos_y });
				initialLines = m_player->GetClearedLines();
				randomTimeDH = Utils::GetRandomNumber(15, 25);
				existsDH = true;
			}
			if (durationDestroy.count() >= copyDurationDH + 5 && existsDH == true)
			{
				startDestroy = std::chrono::system_clock::now();
				finalLines = m_player->GetClearedLines();
				if (finalLines != initialLines)
				{
					linesDifference = finalLines - initialLines;
					m_board->DestroyDarkHole(Position{ pos_x, pos_y + linesDifference });
					pos_x = Utils::GetRandomNumber(0, BOARD_WIDTH - 1);
					pos_y = Utils::GetRandomNumber(15, BOARD_HEIGHT - 1);
					existsDH = false;
				}
				m_board->DestroyDarkHole(Position{ pos_x, pos_y});
				pos_x = Utils::GetRandomNumber(0, BOARD_WIDTH - 1);
				pos_y = Utils::GetRandomNumber(15, BOARD_HEIGHT - 1);
				existsDH = false;
			}

			ProcessEvents(menuOrGame, levelSound);
			Update(deltaTime);

			if (m_elapsedTime > trigger)
			{
				m_elapsedTime = sf::Time::Zero;
				Proceed(Direction::Down);
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
	std::pair<uint16_t, uint16_t> field = GetFreePosition(Utils::GetRandomNumber(0, BOARD_WIDTH - 1), BOARD_HEIGHT);
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
		FileWriter("../Resources/Files/outputPlayers1P.txt");
		m_player->Reset();

		m_gameplayMusic.pause();
		m_gameoverMusic.stop();
		m_gameoverMusic.play();

		m_board->Clean();
		m_pause = 2;
	}
	m_ID = Utils::GetRandomNumber(7);
	m_preview.reset(new TetrisShape(m_texture, m_ID, STARTING_POSITION_1P));
	m_preview->SetPosition(Position{ BOARD_WIDTH + 3, 30 });
}

bool Game::IsValidMovement(std::array<Position, BLOCK_ARRAY_COLUMNS> block)
{
	Position lastPosition = m_tetrisShape->m_block[2];
	for (uint16_t i = 0; i < BLOCK_ARRAY_COLUMNS; i++)
	{
		if (block[i].x < 0 || block[i].x > BOARD_WIDTH - 1 || block[i].y > BOARD_HEIGHT - 1 || block[i].y < 0)
			return false;

		if (IsOccupied(block[i].x, block[i].y))
			return false;

		if (IsDarkHole(block[i].x, block[i].y))
		{
			bool q = false;
			for (int index1 = 0; index1 < BLOCK_ARRAY_COLUMNS - 1; index1++)
				for (int index2 = index1 + 1; index2 < BLOCK_ARRAY_COLUMNS; index2++)
					if (m_tetrisShape->m_block[index1] != m_tetrisShape->m_block[index2])
					{
						q = true;
						break;
					}
			if (m_tetrisShape->m_block[i] == lastPosition && q == false)
			{
				CreateShape();
				break;
			}
			if (m_tetrisShape->m_block[i] == lastPosition)
			{
				Position tempPosition;
				for (int index = 0; index < BLOCK_ARRAY_COLUMNS; index++)
					if (m_tetrisShape->m_block[index] != lastPosition)
					{
						tempPosition = m_tetrisShape->m_block[index];
						m_tetrisShape->m_block[i] = tempPosition;
						for (int index = 0; index < BLOCK_ARRAY_COLUMNS; index++)
							if (m_tetrisShape->m_block[index] == lastPosition)
								m_tetrisShape->m_block[i] = tempPosition;
						lastPosition = tempPosition;
						break;
					}
			}
			if (i <= BLOCK_ARRAY_COLUMNS - 1)
				m_tetrisShape->m_block[i] = lastPosition;
		}
	}
	return true;
}

bool Game::IsOccupied(const uint16_t x, const uint16_t y)
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
				{
					m_pause = 0;
					m_gameplayMusic.play();
				}
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
		for (uint16_t i = 0; i < 5; i++)
			m_renderWindow.draw(m_textPauseMenu[i]);
	}
	else if (m_pause == 2)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (uint16_t i = 0; i < 5; i++)
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

