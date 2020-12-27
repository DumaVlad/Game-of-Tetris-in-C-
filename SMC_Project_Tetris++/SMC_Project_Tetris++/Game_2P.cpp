#include "Game_2P.h"
#include "Utils.h"
#include "Menu.h"
#include "Options.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game_2P::Game_2P()
	: IGame(BOARD_WIDTH_2P, BOARD_HEIGHT_2P), m_ID_2P{ Utils::GetRandomNumber(7) }, m_tetrisShape_2P{ nullptr }, m_preview_2P{ nullptr }
{

	m_board = std::make_unique<Board_2P>(Position{ BOARD_WIDTH_2P,BOARD_HEIGHT_2P }, *this);
	CreateShape();
	CreateShape_2P();
}

void Game_2P::Run(bool& menuOrGame, uint16_t& levelSound)
{
	sf::Clock clock; // starting the timer-ul
	sf::Time deltaTime(sf::Time::Zero);

	m_board->Clean();

	m_gameplayMusic.play();
	m_gameplayMusic.setLoop(true);

	while (m_renderWindow.isOpen())
	{
		m_gameplayMusic.setVolume(levelSound * 20.f);

		if (!m_pause)
		{
			sf::Time trigger(sf::seconds(85.f / (85.f + (m_score.GetLevel() * (m_score.GetLevel() * 5.f))))); // la inceput este = 1;
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
				Proceed_2P(Direction::Down);
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

void Game_2P::Proceed(Direction direction)
{
	if (!m_tetrisShape)
		return;

	if (IsValidMovement(m_tetrisShape->GetFutureBlockPosition(direction)))
	{
		m_tetrisShape->Move(direction);
		if (direction == Direction::UserPressedDown)
			m_score.AddPressedScore(1);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_tetrisShape->GetID();
			m_board->AddBlock(id, m_tetrisShape->GetBlockPosition());
			m_tetrisShape.reset(nullptr);
			m_score.SumPressedScore();
		}
	}
}

void Game_2P::Proceed_2P(Direction direction)
{
	if (!m_tetrisShape_2P)
		return;

	if (IsValidMovement(m_tetrisShape_2P->GetFutureBlockPosition(direction)))
	{
		m_tetrisShape_2P->Move(direction);
		if (direction == Direction::UserPressedDown)
			m_score.AddPressedScore(1);
	}
	else
	{
		if (direction == Direction::Down || direction == Direction::UserPressedDown)
		{
			int id = m_tetrisShape_2P->GetID();
			m_board->AddBlock(id, m_tetrisShape_2P->GetBlockPosition());
			m_tetrisShape_2P.reset(nullptr);
			m_score.SumPressedScore();
		}
	}
}

void Game_2P::Update(const sf::Time& dt)
{
	m_board->Update(dt);
	m_score.Update(dt);
	if (!m_tetrisShape)
	{
		if (m_board->IsToRemoveBlocks())
			return;
		CreateShape();
	}
	if (!m_tetrisShape_2P)
	{
		if (m_board->IsToRemoveBlocks())
			return;
		CreateShape_2P();
	}

}

void Game_2P::Rotate()
{
	if (!m_tetrisShape)
		return;

	m_tetrisShape->Rotate();
	if (!IsValidMovement(m_tetrisShape->GetBlockPosition()))
		m_tetrisShape->RevertState();
}

void Game_2P::Rotate_2P()
{
	if (!m_tetrisShape_2P)
		return;

	m_tetrisShape_2P->Rotate();
	if (!IsValidMovement(m_tetrisShape_2P->GetBlockPosition()))
		m_tetrisShape_2P->RevertState();
}

void Game_2P::ScaleUp()
{
	if (!m_tetrisShape)
		return;

	m_tetrisShape->ScaleUp();
	if (!IsValidMovement(m_tetrisShape->GetBlockPosition()))
	{
		m_tetrisShape->RevertState();
	}
}

void Game_2P::ScaleUp_2P()
{
	if (!m_tetrisShape_2P)
		return;

	m_tetrisShape_2P->ScaleUp();
	if (!IsValidMovement(m_tetrisShape_2P->GetBlockPosition()))
	{
		m_tetrisShape_2P->RevertState();
	}
}

void Game_2P::ScaleDown()
{
	if (!m_tetrisShape)
		return;

	m_tetrisShape->ScaleDown();
	if (!IsValidMovement(m_tetrisShape->GetBlockPosition()))
	{
		m_tetrisShape->RevertState();
	}
}

void Game_2P::ScaleDown_2P()
{
	if (!m_tetrisShape_2P)
		return;

	m_tetrisShape_2P->ScaleDown();
	if (!IsValidMovement(m_tetrisShape_2P->GetBlockPosition()))
	{
		m_tetrisShape_2P->RevertState();
	}
}

void Game_2P::CreateShape()
{
	m_tetrisShape.reset(new TetrisShape(m_texture, m_ID));
	//create new game if necessary
	if (m_board->IsOccupied(m_tetrisShape->GetBlockPosition()))
	{
		std::cout << "Game Over" << std::endl;

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("../Resources/Sounds/gameover.wav"))
			std::cout << "Could not load the gameover sound from file !! \n";

		m_gameplayMusic.stop();
		gameoverMusic.play();

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = true;
	}
	m_ID = Utils::GetRandomNumber(7);
	m_preview.reset(new TetrisShape(m_texture, m_ID));
	m_preview->SetPosition(Position{ BOARD_WIDTH_2P, 30 });
}

void Game_2P::CreateShape_2P()
{
	m_tetrisShape_2P.reset(new TetrisShape(m_texture, m_ID_2P));
	//create new game if necessary
	if (m_board->IsOccupied(m_tetrisShape_2P->GetBlockPosition()))
	{
		std::cout << "Game Over" << std::endl;

		sf::Music gameoverMusic;
		if (!gameoverMusic.openFromFile("..Resources/Sounds/gameover.wav"))
			std::cout << "Could not load the gameover sound from file !! \n";

		m_gameplayMusic.stop();
		gameoverMusic.play();

		//system("pause");

		m_board->Clean();
		m_gameplayMusic.play();
		m_pause = true;
	}
	m_ID_2P = Utils::GetRandomNumber(7);
	m_preview_2P.reset(new TetrisShape(m_texture, m_ID_2P));
	m_preview_2P->SetPosition(Position{ BOARD_WIDTH_2P, 0 });
}

bool Game_2P::IsValidMovement(std::array<Position, 16> block)
{
	for (int i = 0; i < 16; i++)
	{
		if (block[i].x < 0 || block[i].x > BOARD_WIDTH_2P - 1 || block[i].y > BOARD_HEIGHT_2P - 1)
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

bool Game_2P::IsOccupied(int x, int y)
{
	return m_board->GetField(x, y)->m_Occupied;
}

void Game_2P::ProcessEvents(bool& menuOrGame, uint16_t& levelSound)
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
				else if (e.key.code == sf::Keyboard::S)
					Proceed_2P(Direction::Down);
				else if (e.key.code == sf::Keyboard::Left)
					Proceed(Direction::Left);
				else if (e.key.code == sf::Keyboard::A)
					Proceed_2P(Direction::Left);
				else if (e.key.code == sf::Keyboard::Right)
					Proceed(Direction::Right);
				else if (e.key.code == sf::Keyboard::D)
					Proceed_2P(Direction::Right);
				else if (e.key.code == sf::Keyboard::Up)
					Rotate();
				else if (e.key.code == sf::Keyboard::W)
					Rotate_2P();
				else if (e.key.code == sf::Keyboard::Numpad1)
					ScaleUp();
				else if (e.key.code == sf::Keyboard::R)
					ScaleUp_2P();
				else if (e.key.code == sf::Keyboard::Numpad0)
					ScaleDown();
				else if (e.key.code == sf::Keyboard::F)
					ScaleDown_2P();
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

void Game_2P::Render()
{
	m_renderWindow.clear(sf::Color::Black);
	m_score.Draw(m_renderWindow);
	m_board->Draw(m_renderWindow);
	if (m_tetrisShape)
		m_renderWindow.draw(*m_tetrisShape);
	if (m_tetrisShape_2P)
		m_renderWindow.draw(*m_tetrisShape_2P);
	m_renderWindow.draw(*m_preview);
	m_renderWindow.draw(*m_preview_2P);
	m_renderWindow.draw(m_separationLine);
	if (m_pause)
	{
		m_renderWindow.draw(m_pauseMenu);
		for (int i = 0; i < 4; i++)
			m_renderWindow.draw(m_textPauseMenu[i]);
	}
	m_renderWindow.display();
}