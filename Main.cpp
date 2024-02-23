#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Board.hpp"
#include "Menu.hpp"

using namespace std;
using namespace sf;

int main()
{
	Board board;

	RenderWindow window(VideoMode(200, 400), "Tetris");
	window.setFramerateLimit(60);

	board.InstallPart();

	int right = 0, left = 0, up = 0;

	int score = 0;
	int maxScore = 0;

	bool live = 1;

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		if (live) {
			if (Keyboard::isKeyPressed(Keyboard::Up) && !up) board.RotatePart(), up = 1;
			else if (!Keyboard::isKeyPressed(Keyboard::Up)) {
				up = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) board.UpdateLimitTimer(5);
			else board.UpdateLimitTimer(30);

			if (Keyboard::isKeyPressed(Keyboard::Right) && !right) {
				board.Right();
				right = 1;
			}
			else if (!Keyboard::isKeyPressed(Keyboard::Right)) {
				right = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right) && right) {
				right++;
				if (right == 6) right = 0;
			}

			if (Keyboard::isKeyPressed(Keyboard::Left) && !left) {
				board.Left();
				left = 1;
			}
			else if (!Keyboard::isKeyPressed(Keyboard::Left)) {
				left = 0;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left) && left) {
				left++;
				if (left == 6) left = 0;
			}

			if (board.UpdateBoard()) {
				if (!board.InstallPart()) {
					live = 0;
					board.ClearBoard();
				}
			}
			board.UpdateBoardColors();

			int newScore = board.CheckLine() * 5;
			score += newScore;
		}


		window.clear(Color(20, 20, 20));
		window.draw(board);
		window.display();
	}
	return 0;
}