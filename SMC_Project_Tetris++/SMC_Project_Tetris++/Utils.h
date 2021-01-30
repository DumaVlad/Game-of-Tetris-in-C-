#pragma once
#include <random>
#include <SFML/System/Vector2.hpp>

const sf::Vector2i STARTING_POSITION_1P = { 9,1 };
const sf::Vector2i STARTING_POSITION_2P = { 29,1 };

constexpr uint16_t BOARD_WIDTH = 20;
constexpr uint16_t BOARD_HEIGHT = 40;
constexpr uint16_t BOARD_WIDTH_2P = 40;
constexpr uint16_t BOARD_HEIGHT_2P = 40;

constexpr uint16_t BLOCK_ARRAY_ROWS = 7;
constexpr uint16_t BLOCK_ARRAY_COLUMNS = 16;
constexpr uint16_t DARKHOLE_TEXTURE_ID = 7;
constexpr uint16_t SPECIALSHAPE_TEXTURE_ID = 8;
constexpr uint16_t TEXTURES_NUMBER = 9;

constexpr int OPTIONS_WIDTH = 480;
constexpr int OPTIONS_HEIGHT = 600;
constexpr int HIGHSCORE_WIDTH = 700;
constexpr int HIGHSCORE_HEIGHT = 900;

class Utils
{
public:
	static int GetRandomNumber(int);
	static int GetRandomNumber(int, int);
};