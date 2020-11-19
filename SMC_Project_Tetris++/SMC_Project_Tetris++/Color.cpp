#include "Color.h"

Color ConvertStringToColor(const std::string& color)
{
	if (color == "red")
		return Color::Red;
	if (color == "green")
		return Color::Green;
	if (color == "yellow")
		return Color::Yellow;
	if (color == "blue")
		return Color::Blue;
	if (color == "purple")
		return Color::Purple;
	if (color == "pink")
		return Color::Pink;
}

std::string ConvertColorToString(const Color& color)
{
	switch (color)
	{
	case Color::Red:
		return "red";
	case Color::Green:
		return "green";
	case Color::Yellow:
		return "yellow";
	case Color::Blue:
		return "blue";
	case Color::Purple:
		return "purple";
	case Color::Pink:
		return "pink";
	default:
		break;
	}
}
