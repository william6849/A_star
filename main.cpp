#include "lib.h"
#include<time.h>
#include<Windows.h>
int grid[HEIGHT][WIDTH] = { 0 };
int openmatrix[HEIGHT][WIDTH] = { 0 };
int grid2[HEIGHT][WIDTH] = { 0 };
int openmatrix2[HEIGHT][WIDTH] = { 0 };

int start_x = 0;
int start_y = 0;
int end_x = WIDTH - 1;
int end_y = HEIGHT - 1;

bool flag = false;

void clickstart(sf::RenderWindow &window) {
	grid[start_y][start_x] = 0;
	start_x = sf::Mouse::getPosition(window).x / (900 / WIDTH);
	start_y = sf::Mouse::getPosition(window).y / (900 / HEIGHT);
	openmatrix[start_y][start_x] = 0;
	grid[start_y][start_x] = 1;
}
void clickend(sf::RenderWindow &window) {
	grid[end_y][end_x] = 0;
	end_x = sf::Mouse::getPosition(window).x / (900 / WIDTH);
	end_y = sf::Mouse::getPosition(window).y / (900 / HEIGHT);
	openmatrix[end_y][end_x] = 0;
	grid[end_y][end_x] = 3;
}
void clickblock(sf::RenderWindow &window) {
	int x = sf::Mouse::getPosition(window).x / (900 / WIDTH),
		y = sf::Mouse::getPosition(window).y / (900 / HEIGHT);
	grid[y][x] != 2 ? grid[y][x] = 2 : grid[y][x] = 0;
	openmatrix[y][x] == 1 ? openmatrix[y][x] = 0 : openmatrix[y][x] = 1;
}


void input_poll(sf::RenderWindow &window) {
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			switch (event.key.code)
			{
			case 0:
				clickstart(window);
				break;
			case 1:
				clickblock(window);
				break;
			case 2:
				clickend(window);
				break;
			default:
				break;
			}
			flag = true;

			memmove(&grid2, &grid, sizeof(int) * HEIGHT * WIDTH);
			memmove(&openmatrix2, &openmatrix, sizeof(int) * HEIGHT * WIDTH);

			astar(grid2, openmatrix2, start_x, start_y, end_x, end_y);
		}
	}
}


int main() {
	grid[0][0] = 1;
	grid[HEIGHT - 1][WIDTH - 1] = 3;

	sf::RenderWindow window(sf::VideoMode(900, 900), "A_STAR", sf::Style::Close);
	window.setFramerateLimit(3600);
	window.clear(sf::Color::White);
	window_func win;

	sf::RectangleShape square[6];
	for (int i = 0; i < 6; ++i)
		square[i].setSize(sf::Vector2f(900 / WIDTH, 900 / HEIGHT));

	square[0].setFillColor(sf::Color::White);
	square[1].setFillColor(sf::Color::Blue);
	square[2].setFillColor(sf::Color::Red);
	square[3].setFillColor(sf::Color::Yellow);
	square[4].setFillColor(sf::Color::Cyan);
	square[5].setFillColor(sf::Color::Black);

	win.drawSeparationLine(window);
	window.display();

	while (window.isOpen()) {
		while (flag) {
			window.clear(sf::Color::White);
			for (int i = 0; i < HEIGHT; i++) {
				for (int j = 0; j < WIDTH; j++) {
					int n = grid2[i][j];
					square[n].setPosition(j * 900 / HEIGHT, i * 900 / WIDTH);
					window.draw(square[n]);
				}
			}
			win.drawSeparationLine(window);

			square[1].setPosition(start_x * 900 / HEIGHT, start_y * 900 / WIDTH);
			window.draw(square[1]);
			window.display();
			flag = false;
		}
		input_poll(window);
		Sleep(100);
	}

	return 0;
}