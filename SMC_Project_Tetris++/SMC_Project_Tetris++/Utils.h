#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

const sf::Vector2i STARTING_POSITION_1P = { 5,1 };
const sf::Vector2i STARTING_POSITION_2P = { 25,1 };

constexpr int BOARD_WIDTH = 20;
constexpr int BOARD_HEIGHT = 40;
constexpr int OPTIONS_WIDTH = 480;
constexpr int OPTIONS_HEIGHT = 600;
constexpr int BOARD_WIDTH_2P = 40;
constexpr int BOARD_HEIGHT_2P = 40;

class Utils
{
public:
	static int GetRandomNumber(int);
	static int GetRandomNumber(int, int);
};