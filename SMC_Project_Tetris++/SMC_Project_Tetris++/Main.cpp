#include <SFML/Graphics.hpp>
#include <conio.h>
#include "Color.h"
#include "TShape.h"

constexpr auto KB_UP = 72;;
constexpr auto KB_ESCAPE = 27;
constexpr auto KB_PLUS = 43;
constexpr auto KB_MINUS = 45;
int main()
{
	/*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/

	TShape shape;
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