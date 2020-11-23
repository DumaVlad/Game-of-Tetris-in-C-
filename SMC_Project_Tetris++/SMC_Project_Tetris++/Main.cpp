#include <SFML/Graphics.hpp>
#include <conio.h>
#include "Color.h"
#include "IShape.h"
#include "TShape.h"
#include "OShape.h"
#include "SShape.h"
#include "LShape.h"
#include "JShape.h"
#include "ZShape.h"


constexpr auto KB_UP = 72;;
constexpr auto KB_ESCAPE = 27;
constexpr auto KB_PLUS = 43;
constexpr auto KB_MINUS = 45;

int main()
{
	/*sf::RenderWindow window(sf::VideoMode(300, 300), "SFML works!");
	sf::RectangleShape shape1(sf::Vector2f(200,200));
	shape1.setPosition(50, 30);
	shape1.setFillColor(sf::Color::Yellow);
	shape1.setOutlineThickness(5);
	shape1.setOutlineColor(sf::Color::Blue);

	sf::Mouse button();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		window.close();
	}

	// get global mouse position
	sf::Vector2i position = sf::Mouse::getPosition();
	// set mouse position relative to a window
	sf::Mouse::setPosition(sf::Vector2i(200, 200), window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape1);
		window.display();
	}*/

	ZShape shape;
	std::cout << shape << std::endl;
	
	char input = 0;
	while (input != KB_ESCAPE)
	{
		input = _getch();
		switch (input)
		{
		case KB_UP:
		{
			std::cout << "Rotating..." << std::endl;
			shape.Rotate();
			std::cout << shape << std::endl;
			break;
		}
		case KB_PLUS:
		{
			std::cout << "Up Scaling..." << std::endl;
			shape.ScaleUp();
			std::cout << shape << std::endl;
			break;
		}
		case KB_MINUS:
		{
			std::cout << "Down Scaling..." << std::endl;
			shape.ScaleDown();
			std::cout << shape << std::endl;
			break;
		}
		case KB_ESCAPE:
		{
			std::cout << "Exiting the program..." << std::endl;
			return 0;
		}
		default:
			break;
		}
	}


	return 0;
}