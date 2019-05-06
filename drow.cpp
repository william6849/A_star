#include "drow.h"



window_func::window_func()
{

}

window_func::~window_func()
{
}


void window_func::drawSeparationLine(sf::RenderWindow &window)
{
	sf::RectangleShape verticalLine[WIDTH];
	sf::RectangleShape horizontalLine[HEIGHT];
	//sf::RectangleShape middleLine;
	//middleLine.setSize(sf::Vector2f(3, 900));
	//middleLine.setFillColor(sf::Color::Blue);
	//middleLine.setPosition(600, 0);

	for (size_t i = 0; i < HEIGHT; ++i)
	{
		for (size_t j = 0; j < WIDTH; j++) {
			verticalLine[i].setSize(sf::Vector2f(2, 900));
			verticalLine[i].setFillColor(sf::Color::Red);
			verticalLine[i].setPosition(900/WIDTH * (i + 1), 0);
			window.draw(verticalLine[i]);
		}
		horizontalLine[i].setSize(sf::Vector2f(900, 2));
		horizontalLine[i].setFillColor(sf::Color::Red);
		horizontalLine[i].setPosition(0, 900/HEIGHT * (i + 1));
		window.draw(horizontalLine[i]);
	}
}
