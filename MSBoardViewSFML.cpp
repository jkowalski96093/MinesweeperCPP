#include "MSBoardViewSFML.h"

MSBoardViewSFML::MSBoardViewSFML(MinesweeperBoard & board, sf::RenderWindow & window):board(board),window(window)
{
	screen_width = 850;
	screen_height = 650;
	board_width = screen_width-250;
	board_height = screen_height-50;
	field_width = board_width / board.getBoardWidth()-2;
	field_height = board_height / board.getBoardHeight()-2;
	MSfield = sf::RectangleShape(sf::Vector2f(field_width,field_height));
	MSfield.setFillColor(sf::Color(192, 192, 192));
	MSfield.setOutlineThickness(2);
	MSfield.setOutlineColor(sf::Color(128, 128, 128));

	if (! font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Failed to load font";
	}
}

MSBoardViewSFML::MSBoardViewSFML(MinesweeperBoard & board, sf::RenderWindow & window, const int screen_width, const int screen_height):
	board(board),window(window),screen_width(screen_width),screen_height(screen_height)
{
	board_width = screen_width - 250;
	board_height = screen_height - 50;
	field_width = board_width / board.getBoardWidth() - 2;
	field_height = board_height / board.getBoardHeight() - 2;
	MSfield = sf::RectangleShape(sf::Vector2f(field_width, field_height));
	MSfield.setFillColor(sf::Color(192, 192, 192));
	MSfield.setOutlineThickness(2);
	MSfield.setOutlineColor(sf::Color(128, 128, 128));

	if (!font.loadFromFile("Arial.ttf"))
	{
		std::cout << "Failed to load font";
	}
}

void MSBoardViewSFML::drawField(int x, int y)
{
	MSfield.setPosition(x+25, y+25);
	window.draw(MSfield);
}

void MSBoardViewSFML::drawEmptyBoard()
{
	int width = 0;
	int height = 0;
	for (int i = 0; i < board.getBoardWidth(); i++)
	{

		for (int j = 0; j < board.getBoardHeight(); j++)
		{
			drawField(i*field_width, j*field_height);
		}

	}
}

sf::Vector2f MSBoardViewSFML::getPosition(int x, int y)
{
	sf::Vector2f w;
	w.x = field_width * (x - 1) + 25;
	w.y = field_height * (y - 1) + 25;
	return w;
}

void MSBoardViewSFML::drawBoard()
{
	drawEmptyBoard();
	drawStats();
	sf::Text txt;
	txt.setFont(font);
	std::string str;
	sf::Vector2f wek;
	txt.setCharacterSize(20);
	txt.setFillColor(sf::Color(0, 0, 0));
	for (int i = 0; i < board.getBoardWidth(); i++)
	{
		for (int j = 0; j < board.getBoardHeight(); j++)
		{

			if (board.hasFlag(j, i) == 1)
			{
				txt.setPosition(getPosition(j+1,i+1).x + field_width/3, getPosition(j + 1, i + 1).y+field_height/3);
				txt.setString("F");
				window.draw(txt);

			}
			else if (board.hasMine(j, i) == 1 && board.isRevealed(j, i) == 1)
			{
				txt.setPosition(getPosition(j + 1, i + 1).x + field_width / 3, getPosition(j + 1, i + 1).y + field_height / 3);
				txt.setString("M");
				window.draw(txt);
			}
			else if (board.hasFlag(j, i) == 0 && board.isRevealed(j, i) == 1)
			{
				txt.setPosition(getPosition(j + 1, i + 1).x + field_width / 3, getPosition(j + 1, i + 1).y + field_height / 3);
				txt.setString(std::to_string(board.countMines(j, i)));
				window.draw(txt);
			}
		}
	}
}

void MSBoardViewSFML::drawStats()
{
	sf::Text txt;
	txt.setFont(font);
	std::string str;
	txt.setCharacterSize(15);
	txt.setString("Ilosc ruchow: " + std::to_string(board.getMoveCount()));
	txt.setPosition(board_width+20, board_height/5);
	window.draw(txt);
	txt.setString("Ilosc min: " + std::to_string(board.getMineCount()));
	txt.setPosition(board_width + 20, board_height / 5 + 20);
	window.draw(txt);
	txt.setString("Pozostalo flag: " + std::to_string(board.getFlagCount()));
	txt.setPosition(board_width + 20, board_height / 5 + 40);
	window.draw(txt);
	txt.setString("Gamestate: " + Gamestate());
	txt.setPosition(board_width + 20, board_height / 2);
	window.draw(txt);
	txt.setString("LPM - Odkryj pole");
	txt.setPosition(board_width + 20, board_height / 2 + 40);
	window.draw(txt);
	txt.setString("PPM - Ustaw flage");
	txt.setPosition(board_width + 20, board_height / 2 + 60);
	window.draw(txt);
	txt.setString("R - Restart");
	txt.setPosition(board_width + 20, board_height / 2 + 100);
	window.draw(txt);
}

void MSBoardViewSFML::boardControl()
{
	drawBoard();

}

void MSBoardViewSFML::buttonControl(int x, int y, int button)
{
	if (button == 0) //left click
	{
		buttonReveal(x, y);
	}

	if (button == 1) //right click
	{
		buttonFlag(x, y);
	}
}

void MSBoardViewSFML::buttonReveal(int x, int y)
{
	x = buttonGetFieldX(x);
	y = buttonGetFieldY(y);
	board.revealField(x, y);

}

void MSBoardViewSFML::buttonFlag(int x, int y)
{
	x = buttonGetFieldX(x);
	y = buttonGetFieldY(y);
	board.toggleFlag(x, y);

}

int MSBoardViewSFML::buttonGetFieldX(int x)
{
	for (int i = 0; i < board.getBoardWidth(); i++)
	{
		if (x >= 25 + i * field_width && x <= 25 + (i + 1) * field_width - 3)
			return i;
	}
	return 0;
}

int MSBoardViewSFML::buttonGetFieldY(int y)
{
	for (int i = 0; i < board.getBoardWidth(); i++)
	{
		if (y >= 25 + i * field_width && y <= 25 + (i + 1) * field_width - 3)
			return i;
	}
	return 0;
}

std::string MSBoardViewSFML::Gamestate()
{
	std::string str;
	if (board.getGameState() == RUNNING)
		str = "RUNNING";
	if (board.getGameState() == FINISHED_LOSS)
		str = "LOSS";
	if (board.getGameState() == FINISHED_WIN)
		str = "WIN";
	return str;
}

void MSBoardViewSFML::restart(int x, int y, GameMode m)
{
	board = MinesweeperBoard(x, y, m);
}





