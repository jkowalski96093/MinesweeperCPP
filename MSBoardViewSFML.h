#pragma once
#include "MinesweeperBoard.h"
#include <SFML/Graphics.hpp>
class MSBoardViewSFML :
	public MinesweeperBoard
{
	MinesweeperBoard &board;
	sf::RenderWindow &window;
	int screen_width;
	int screen_height;
	int board_width;
	int board_height;
	int field_width;
	int field_height;
	sf::RectangleShape MSfield;
	sf::Font font;

public:
	MSBoardViewSFML(MinesweeperBoard &board, sf::RenderWindow &window);
	MSBoardViewSFML(MinesweeperBoard &board, sf::RenderWindow &window, const int screen_width, const int screen_height);
	void drawField(int x,int y);
	void drawEmptyBoard();
	sf::Vector2f getPosition(int x, int y);
	void drawBoard();
	void drawStats();
	void boardControl();
	void buttonControl(int x, int y,int button);
	void buttonReveal(int x, int y);
	void buttonFlag(int x, int y);
	int buttonGetFieldX(int x);
	int buttonGetFieldY(int y);
	std::string Gamestate();
	void restart(int x, int y, GameMode m);
};