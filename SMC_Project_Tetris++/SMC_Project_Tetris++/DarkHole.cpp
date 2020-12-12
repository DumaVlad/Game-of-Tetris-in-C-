#include "DarkHole.h"

DarkHole::DarkHole()
	: m_Position{}
{
	uint16_t x = Utils::GetRandomNumber(0, BOARD_WIDTH);
	uint16_t y = Utils::GetRandomNumber(0, BOARD_HEIGHT);
	m_Position = Position{ x,y };
}
