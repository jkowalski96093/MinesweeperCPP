#include <iostream>
#include "MinesweeperBoard.h"
#include "MSBoardTextView.h"
#include "MSTextController.h"
#include "MSBoardViewSFML.h"
#include <SFML/Graphics.hpp>

int main()
{
	int board_width = 10;
	int board_height = 10;
	GameMode mode = EASY;
	MinesweeperBoard board(board_width, board_height, mode);
	board.debug_display();

	const int screen_width = 850;
	const int screen_height = 650;

	sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "My application");

	window.setVerticalSyncEnabled(true);



	MSBoardViewSFML SFMLboard(board, window, screen_width, screen_height);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				SFMLboard.buttonControl(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					SFMLboard.restart(board_width, board_height, mode);
				}
			}
		}



		window.clear(sf::Color(0,0,0)); //tylko raz

		SFMLboard.boardControl();
		window.display(); //tylko raz
	}
}
