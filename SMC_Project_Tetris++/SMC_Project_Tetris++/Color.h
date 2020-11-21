#pragma once
#include <cstdint>
#include <iostream>

enum class Color : uint8_t
{
	Red,
	Green,
	Yellow,
	Blue,
	Purple,
	Pink,
	Orange,
	None,
};

Color ConvertStringToColor(const std::string&);
std::string ConvertColorToString(const Color&);