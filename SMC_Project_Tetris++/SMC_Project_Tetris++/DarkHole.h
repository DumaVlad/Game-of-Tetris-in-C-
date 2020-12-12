#pragma once
#include "Utils.h"
#include "Config.h"
#include <SFML/System/Vector2.hpp>

class DarkHole
{
public:
	using Position = sf::Vector2i;
public:
	DarkHole();
	~DarkHole() = default;

private:
	Position m_Position;
};
