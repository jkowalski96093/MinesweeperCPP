#include "MSBoardTextView.h"

MSBoardTextView::MSBoardTextView():board(board)
{
}

MSBoardTextView::MSBoardTextView(const MSBoardTextView &view2) :board(view2.board)
{
}

MSBoardTextView::MSBoardTextView(MinesweeperBoard &board2) : board(board2)
{
}



void MSBoardTextView::display() const

{
	for (int p = 0; p < 50; p++)
		std::cout << "\n";
	{
		std::cout << "   ";
		for (int k = 0; k < board.getBoardWidth(); k++)
		{
			if (k < 9)
				std::cout << " " << k + 1 << " ";
			if (k >= 9 && k < 99)
				std::cout << k + 1 << " ";
			if (k >= 99)
				std::cout << k+1;
		}
		std::cout << " x           Ilosc min: " << board.getMineCount() << "  Ilosc flag: " << board.getFlagCount();
		std::cout << "  Ruch nr " << board.getMoveCount() + 1 << std::endl;
		for (int i = 0; i < board.getBoardWidth(); i++)
		{
			if (i < 9)
				std::cout << " " << i+1 << " ";
			if (i >= 9 && i < 99)
				std::cout << i + 1<<" ";
			if (i >= 99)
				std::cout << i + 1;

			for (int j = 0; j < board.getBoardHeight(); j++)
			{
				if (board.isRevealed(j, i) == 0 && board.hasFlag(j, i) == 0)
					std::cout << "[ ]";
				else if (board.hasFlag(j, i) == 1)
					std::cout << "[F]";
				else if (board.hasFlag(j, i) == 0 && board.isRevealed(j, i) == 1)
					std::cout << "["<<board.countMines(j,i)<<"]";
			}
			std::cout << "\n";
		}
		std::cout << " y";

	}
	std::cout << std::endl;

}


