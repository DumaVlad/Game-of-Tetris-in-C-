#pragma once
#include <random>

constexpr int BOARD_WIDTH = 20;
constexpr int BOARD_HEIGHT = 40;
constexpr int OPTIONS_WIDTH = 400;
constexpr int OPTIONS_HEIGHT = 600;
constexpr int BOARD_WIDTH_2P = 40;
constexpr int BOARD_HEIGHT_2P = 40;

class Utils
{
public:
	static int GetRandomNumber(int);
	static int GetRandomNumber(int, int);
};