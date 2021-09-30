#include "MinesweeperBoard.h"


MinesweeperBoard::MinesweeperBoard()
{
}


MinesweeperBoard::MinesweeperBoard(const MinesweeperBoard * board2)
{
	this->board = board2->board;
	this->width = board2->width;
	this->height = board2->height;
	this->game = board2->game;
	this->moveCount = board2->moveCount;
	this->flagCount = board2->flagCount;
}

MinesweeperBoard::MinesweeperBoard(int width, int height) :width(width), height(height)
{
	//width= mWidth; //this->width=width;
	//height = mHeight; // this->heigth=heigth;
	board.resize(width);                      //!!
	for (int i = 0; i < width; ++i)           //!!
		board[i].resize(height);              //!!

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board.at(i).at(j).hasFlag = 0;
			board.at(i).at(j).hasMine = 0;
			board.at(i).at(j).isRevealed = 0;
		}
	}
	moveCount = 0;
	game = RUNNING;
	//board.at(width).at(height)

}

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode) :width(width), height(height)
{
	board.resize(width);                      //!!
	for (int i = 0; i < width; ++i)           //!!
		board[i].resize(height);              //!!

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			board.at(i).at(j).hasFlag = 0;
			board.at(i).at(j).hasMine = 0;
			board.at(i).at(j).isRevealed = 0;
		}
	}
	int a = width * height;
	if (mode == EASY)
		a = a / 10;
	if (mode == NORMAL)
		a = a / 5;
	if (mode == HARD)
	{
		a *= 3;
		a = a / 10;
	}
	place_mines(a);
	moveCount = 0;
	game = RUNNING;
	flagCount = getMineCount();
	//board.at(width).at(height)
}


MinesweeperBoard::~MinesweeperBoard()
{
}

int MinesweeperBoard::getBoardWidth() const
{
	return width;
}

int MinesweeperBoard::getBoardHeight() const
{
	return height;
}

int MinesweeperBoard::getMoveCount() const
{
	return moveCount;
}

int MinesweeperBoard::getMineCount() const
{
	int mineCount = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (board.at(i).at(j).hasMine == 1)
				mineCount++;
		}
	}
	return mineCount;
}

int MinesweeperBoard::getFlagCount() const
{
	return flagCount;
}

bool MinesweeperBoard::onBoard(int x, int y) const
{
	if (x < 0 || x >= width)
		return 0;
	if (y < 0 || y >= height)
		return 0;
	else return 1;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
	if (onBoard(x, y) == 0)
		return 0;
	if (board.at(x).at(y).hasFlag == 1)
		return 1;
	else return 0;
}

bool MinesweeperBoard::hasMine(int x, int y) const
{
	if (onBoard(x, y) == 0)
		return 0;
	if (board.at(x).at(y).hasMine == 1)
		return 1;
	else return 0;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{
	if (onBoard(x, y) == 0)
		return;
	if (board.at(x).at(y).isRevealed == 1)
		return;
	if (game != RUNNING)
		return;
	if (board.at(x).at(y).hasFlag == 0)
	{
		if (flagCount != 0)
		{
			flagCount--;
			board.at(x).at(y).hasFlag = 1;
			moveCount++;
			isWin();
			return;
		}
		else std::cout << "\nBrak dostepnych flag. Usun dowolna flage przy uzyciu komendy f i sprobuj wykonac ruch ponownie.";
		return;
	}
	if (board.at(x).at(y).hasFlag == 1)
	{
		board.at(x).at(y).hasFlag = 0;
		flagCount++;
		moveCount++;
		return;
	}
}

void MinesweeperBoard::revealField(int x, int y)
{
	if (game == RUNNING)
	{
		if (moveCount == 0 && board.at(x).at(y).hasMine == 1)
		{
			srand(time(NULL));
			int a = rand() % width;
			int b = rand() % height;
			while (board.at(a).at(b).hasMine == 1)
			{
				a = rand() % width;
				b = rand() % height;
			}
			board.at(x).at(y).hasMine = 0;
			set_mine(a, b);
			revealFieldV2(x, y);
		}
		else revealFieldV2(x, y);

		moveCount++;
	}

}

void MinesweeperBoard::revealFieldV2(int x, int y)
{
	if (!onBoard(x, y)) // breake if outside of the board
		return;
	if (board.at(x).at(y).isRevealed) // break if already revealed
		return;
	if (board.at(x).at(y).hasFlag) // break if there is a flag
		return;
	board.at(x).at(y).isRevealed = 1; // reveal
	if (board.at(x).at(y).hasMine) // end game if there is a bomb
	{
		game = FINISHED_LOSS;
		return;
	}
	if (countMines(x, y) == 0) // reveal around if no mine
	{
		revealFieldV2(x - 1, y);
		revealFieldV2(x, y - 1);
		revealFieldV2(x + 1, y);
		revealFieldV2(x, y + 1);
		revealFieldV2(x - 1, y - 1);
		revealFieldV2(x + 1, y + 1);
		revealFieldV2(x - 1, y + 1);
		revealFieldV2(x + 1, y - 1);
	}
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{
	if (board.at(x).at(y).isRevealed == 1)
		return 1;
	else
		return 0;

}

void MinesweeperBoard::isWin()
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (board.at(i).at(j).hasMine == 1)
				if (board.at(i).at(j).hasFlag == 0)
					return;
		}
	}
	game = FINISHED_WIN;
	return;

}

GameState MinesweeperBoard::getGameState() const
{
	return game;
}

int MinesweeperBoard::countMines(int x, int y) const
{
	int mineCount = 0;

	if (onBoard(x, y) == 0)
		return -1;
	if (board.at(x).at(y).isRevealed == 0)
		return -1;

	if (x != 0)
	{
		if (board.at(x - 1).at(y).hasMine == 1)  // 1xx                                       // xxx
			mineCount++;                         // 2*x                                        // xxx
		// 3xx
		if (y != 0 && board.at(x - 1).at(y - 1).hasMine == 1)
			mineCount++;
		if (y < height - 1 && board.at(x - 1).at(y + 1).hasMine == 1)
			mineCount++;

	}

	if (x < width - 1)
	{
		if (board.at(x + 1).at(y).hasMine == 1)
			mineCount++;
		if (y != 0 && board.at(x + 1).at(y - 1).hasMine == 1)
			mineCount++;
		if (y < height - 1 && board.at(x + 1).at(y + 1).hasMine == 1)
			mineCount++;
	}

	if (y < height - 1 && board.at(x).at(y + 1).hasMine == 1)
		mineCount++;
	if (y != 0 && board.at(x).at(y - 1).hasMine == 1)
		mineCount++;

	return mineCount;

}

void MinesweeperBoard::debug_display() const
{

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			std::cout << "[";

			if (board[j][i].hasMine == 1)
				std::cout << "M";
			else std::cout << ".";

			if (board[j][i].isRevealed == 1)
				std::cout << "o";
			else std::cout << ".";

			if (board[j][i].hasFlag == 1)
				std::cout << "f";
			else std::cout << ".";

			std::cout << "]";
		}
		std::cout << "\n";
	}

}

void MinesweeperBoard::set_mine(int mWidth, int mHeight)
{
	board.at(mWidth).at(mHeight).hasMine = 1;
}

void MinesweeperBoard::place_mines(int nofMines)
{
	if (nofMines < width*height)
	{
		std::srand(std::time(NULL));
		for (int i = 0; i < nofMines; i++)
		{
			int randWidth = std::rand() % width;
			int randHeight = std::rand() % height;
			if (board[randWidth][randHeight].hasMine == 0)
			{
				set_mine(randWidth, randHeight);
			}
			else i--;
		}

	}
	else std::cout << "BLAD: Zbyt duza liczba min";
}

char MinesweeperBoard::getFieldInfo(int x, int y) const
{
	if (x < 0 || x >= width)
		return '#';
	if (y < 0 || y >= height)
		return '#';             //outside board
	if (board.at(x).at(y).isRevealed == 0 && board.at(x).at(y).hasFlag == 1)
		return 'F';				//flag, not revealed
	if (board.at(x).at(y).isRevealed == 0 && board.at(x).at(y).hasFlag == 0)
		return '_';				//no flag, not revealed
	if (board.at(x).at(y).isRevealed == 1 && board.at(x).at(y).hasMine == 1)
		return 'x';				//has mine, is revealed
	if (board.at(x).at(y).isRevealed == 1 && countMines(x, y) == 0)
		return ' ';				//has 0 mines around, is revealed
	if (board.at(x).at(y).isRevealed == 1 && countMines(x, y) != 0)
		return '1';				//has some mines around, is
	else return 'e';  //error
}
