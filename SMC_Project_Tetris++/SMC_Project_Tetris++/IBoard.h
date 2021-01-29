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
	sf::Sprite m_sprite;
};

struct Field
{
	Field& operator=(const Field&);
	bool m_occupied = false;
	bool m_visible = false;
	bool m_darkHole = false;
	FieldData* m_info = nullptr;
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
	void AddBlock(uint16_t, std::array<Position, BLOCK_ARRAY_COLUMNS>);
	bool IsOccupied(std::array<Position, BLOCK_ARRAY_COLUMNS>);
	void Draw(sf::RenderWindow&);
	inline bool IsToRemoveBlocks() const { return m_toRemoveBlocks; };
	Field* GetField(const uint16_t, const uint16_t);
	void AddSpecialBlock(uint16_t, Position);
	virtual void GenerateDarkHole(uint16_t, Position) = 0;
	virtual void DestroyDarkHole(Position) = 0;
	int Convert2DTo1D(const uint16_t, const uint16_t);
	//special
	sf::Music m_clearLinesMusic;

private:
	
	void CleanLines();
	virtual void MarkLinesForRemoval() = 0;
	void Blink();
	

protected:
	IGame& m_game;
	std::unordered_map<uint16_t, std::unique_ptr<Field>> m_fields;
	std::unordered_map<uint16_t, std::unique_ptr<FieldData>> m_fieldDatas;
	Position m_size;
	std::vector<int> m_toBeCleaned;
	float m_elapsedTime;
	bool m_toRemoveBlocks;
};
