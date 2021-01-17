#pragma once
#include "TetrisShape.h"
#include "IBoard.h"
#include "Player.h"
#include "Utils.h"
#include <fstream>

class IGame
{
	friend class IBoard;
public:
	using Position = sf::Vector2i;

public:
	IGame(const unsigned int width, const unsigned int height);
	virtual void Run(bool&, uint16_t&) = 0;

	sf::Music m_gameplayMusic;
	std::unique_ptr<Player> m_player;
	sf::Texture m_texture;

protected:
	void Proceed(Direction);
	void Rotate();
	void ScaleUp();
	void ScaleDown();
	bool IsOccupied(uint16_t, uint16_t);
	std::pair<uint16_t, uint16_t> GetFreePosition(uint16_t, uint16_t);
	void InitializePauseMenu(const unsigned int width, const unsigned int height);
	void InitializeTextPauseMenu(const unsigned int width, const unsigned int height);
	void InitializeTextGameoverMenu(const unsigned int width, const unsigned int height);
	void InitializePlayerNameBox(const unsigned int width, const unsigned int height);
	void InitializePlayerNameText(const unsigned int width, const unsigned int height);
	virtual void AddSpecialShape() = 0;
	virtual void CreateShape() = 0;
	virtual bool IsValidMovement(std::array<Position, BLOCK_ARRAY_COLUMNS>) = 0;
	virtual void Update(const sf::Time&) = 0;
	virtual void ProcessEvents(bool&, uint16_t& levelSound) = 0;
	virtual void FileWriter(const std::string& file) = 0;
	

protected:
	sf::RenderWindow m_renderWindow;
	sf::RectangleShape m_separationLine;
	sf::Texture m_backGroundTexture;
	sf::Sprite m_backGroundSprite;
	std::unique_ptr<TetrisShape> m_tetrisShape;
	std::unique_ptr<TetrisShape> m_preview;
	std::unique_ptr<IBoard> m_board;
	sf::Time m_elapsedTime;
	int m_ID;
	uint16_t m_pause;
	sf::RectangleShape m_pauseMenu;
	sf::Font m_fontOptions;
	sf::Text m_textPauseMenu[4];
	sf::Text m_textGameOverMenu[5];
	sf::String m_playerNameInput1;
	sf::String m_playerNameInput2;
	sf::Text m_playerNameText;
	sf::Text m_playerNameBox;
};
