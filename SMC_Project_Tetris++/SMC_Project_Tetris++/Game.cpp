#include "Game.h"
#include "Utils.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

Game::Game()
	: m_RenderWindow{ sf::VideoMode{10 * 18 + 100, 18 * 18}, "Tetris", sf::Style::Default }, m_Texture{}, m_SeparationLine{}, m_TetrisShape{nullptr}, m_Preview{nullptr}, m_Board{}, m_ElapsedTime{sf::Time::Zero}, m_ID{Utils::GetRandomNumber(7)}
{
	m_SeparationLine.setSize(sf::Vector2f{ 1.f, 18.f * 18.f });
	m_SeparationLine.setPosition(sf::Vector2f{ 10.f * 18.f, 0 });
	m_SeparationLine.setFillColor(sf::Color::Red);
	if (!m_Texture.loadFromFile("Blocks.png"))
	{
		std::cout << "Could not load texture from file !! \n";
	}
	m_Board = std::make_unique<Board>(Position{ 10,18 }, *this);
	CreateShape();
}

void Game::Run()
{
}

void Game::Proceed(Direction direction)
{
}

void Game::Update(const sf::Time& dt)
{
}

void Game::Rotate()
{
}

void Game::ScaleUp()
{
}

void Game::ScaleDown()
{
}

void Game::CreateShape()
{
}

bool Game::IsValidMovement(std::array<Position, 16> block)
{
	return false;
}

bool Game::IsOccupied(int x, int y)
{
	return false;
}

void Game::ProcessEvents()
{
}

void Game::Render()
{
}
