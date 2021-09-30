#include "MSTextController.h"



MSTextController::MSTextController(MinesweeperBoard &board2, MSBoardTextView view2) :board(board2), view(view2)
{
}

void MSTextController::play()
{
	while (board.getGameState() == RUNNING)
	{
		view.display();
		std::cout << std::endl << "r - odkryj pole" << std::endl << "f - postaw flage" << std::endl;
		char a;
		std::cin >> a;
		int x;
		int y;
		switch (a) {
		case 'r':	std::cout << "Wybierz ktore pole chcesz odkryc:" << std::endl;
			x = selectX();
			y = selectY();
			if (x != -1 && y != -1)
				board.revealFieldV2(x - 1, y - 1);
			break;
		case 'f':	std::cout << "Wybierz na ktorym polu chcesz ustawic/usunac flage:" << std::endl;
			x = selectX();
			y = selectY();
			if (x != -1 && y != -1)
				board.toggleFlag(x - 1, y - 1);
			break;
		default: std::cout << "Blad" << std::endl;
			break;

		}
		board.isWin();
	}
	if (board.getGameState() == FINISHED_LOSS)
	{
		std::cout << "\n----------------------------------------------";
		std::cout << "\n              BOOM! Game over";
		std::cout << "\n----------------------------------------------";
	}
	if (board.getGameState() == FINISHED_WIN)
	{
		std::cout << "\n----------------------------------------------";
		std::cout << "\n       Gratulacje udalo Ci sie wygrac!";
		std::cout << "\n----------------------------------------------";
	}
}

int MSTextController::selectX()
{
	std::cout << "\nPodaj wspolrzedna x " << "(1-" << board.getBoardWidth() << "):";
	int row;
	std::cin >> row;
	if (std::cin.fail())			 //source:https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
	{
		std::cout << "\nPodaj liczbe!"; 
		std::cin.clear();
	}
	if (row <= board.getBoardWidth() && row > 0)
	{
		return row;
	}
	std::cout << "\nNiepoprawna wspolrzedna" << std::endl;
	return -1;
}

int MSTextController::selectY()
{
	std::cout << "\nPodaj wspolrzedna y "<<"(1-"<<board.getBoardHeight()<<"):";
	int collumn;
	std::cin >> collumn;
	if (std::cin.fail())			//source:https://stackoverflow.com/questions/10828937/how-to-make-cin-take-only-numbers
	{
		std::cout << "\nPodaj liczbe!";  
		std::cin.clear();
	}
	if (collumn <= board.getBoardHeight() && collumn > 0)
	{
		return collumn;
	}
	std::cout << "\nNiepoprawna wspolrzedna" << std::endl;
	return -1;
}


MSTextController::~MSTextController()
{
}
