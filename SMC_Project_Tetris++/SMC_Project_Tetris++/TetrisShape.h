#pragma once
#include <array>
#include <optional>
#include "Color.h"

class TetrisShape
{
public:
	using Position = std::pair<uint16_t, uint16_t>;

public:

	// Rule of Five
	TetrisShape();
	TetrisShape(uint16_t, uint16_t, Color);
	TetrisShape(const TetrisShape&);
	TetrisShape(TetrisShape&&);
	TetrisShape& operator=(const TetrisShape&);
	TetrisShape& operator=(TetrisShape&&);
	~TetrisShape();
	//

	std::optional<int>& operator[](const Position&);
	const std::optional<int>& operator[](const Position&) const;
	
	friend std::ostream& operator<<(std::ostream&, TetrisShape&);

public: //metodele care trebuie suprascrise pentru fiecare piesa
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	virtual void MoveDown() = 0;
	virtual void Rotate() = 0;
	virtual void ScaleUp() = 0;
	virtual void ScaleDown() = 0;

protected: 
	const static size_t ROWS = 5;
	const static size_t COLUMNS = 5;
	const static size_t SIZE = ROWS * COLUMNS;

protected:
	uint16_t m_centerL;
	uint16_t m_centerC;
	Color m_color;
	std::array<std::optional<int>, SIZE> m_piece_array;
};

