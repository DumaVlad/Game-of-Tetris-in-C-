#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <array>
#include <unordered_map>
#include "Game.h"

class Game; // for using methods from class Game

struct FieldInfo
{
	FieldInfo(sf::Texture&, uint16_t);
	sf::Sprite m_Sprite;
};

struct Field
{
	Field& operator=(const Field&);
	bool m_Occupied = false;
	bool m_Visible = false;
	FieldInfo* m_Info = nullptr;
};


class Board
{
public:
	using Position = sf::Vector2i;

public:
	Board(Position, Game&);
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;

	void Update(const sf::Time&);
	void Clean();
	void AddBlock(uint16_t, std::array<Position, 16>);
	bool IsOccupied(std::array<Position, 16>);
	void Draw(sf::RenderWindow&);
	void PrintBoard();
	inline bool IsToRemoveBlocks() const { return m_ToRemoveBlocks; };
	Field* GetField(uint16_t, uint16_t);

private:
	int Convert2DTo1D(uint16_t, uint16_t);
	void CleanLines();
	void MarkLinesForRemoval();
	void Blink();

private:
	Game& m_Game;
	std::unordered_map<uint16_t, std::unique_ptr<Field>> m_Fields;
	std::unordered_map<uint16_t, std::unique_ptr<FieldInfo>> m_FieldInfos;
	Position m_Size;
	std::vector<int> m_ToBeCleaned;
	float m_ElapsedTime;
	bool m_ToRemoveBlocks;
};

