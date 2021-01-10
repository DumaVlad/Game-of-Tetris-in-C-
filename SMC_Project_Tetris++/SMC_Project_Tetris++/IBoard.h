#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/Music.hpp>
#include <array>
#include <unordered_map>
#include "IGame.h"

class IGame; // for using methods from class Game

struct FieldData
{
	FieldData(sf::Texture&, uint16_t);
	sf::Sprite m_Sprite;
};

struct Field
{
	Field& operator=(const Field&);
	bool m_Occupied = false;
	bool m_Visible = false;
	FieldData* m_Info = nullptr;
};


class IBoard
{
public:
	using Position = sf::Vector2i;

public:
	IBoard(Position, IGame&);
	IBoard(const IBoard& other) = delete;
	IBoard& operator=(const IBoard& other) = delete;

	void Update(const sf::Time&);
	void Clean();
	void AddBlock(uint16_t, std::array<Position, 16>);
	bool IsOccupied(std::array<Position, 16>);
	void Draw(sf::RenderWindow&);
	inline bool IsToRemoveBlocks() const { return m_ToRemoveBlocks; };
	Field* GetField(uint16_t, uint16_t);
	void AddSpecialBlock(uint16_t, Position);

private:
	int Convert2DTo1D(uint16_t, uint16_t);
	void CleanLines();
	virtual void MarkLinesForRemoval() = 0;
	void Blink();
	

protected:
	IGame& m_Game;
	std::unordered_map<uint16_t, std::unique_ptr<Field>> m_Fields;
	std::unordered_map<uint16_t, std::unique_ptr<FieldData>> m_FieldDatas;
	Position m_Size;
	std::vector<int> m_ToBeCleaned;
	float m_ElapsedTime;
	bool m_ToRemoveBlocks;
};
