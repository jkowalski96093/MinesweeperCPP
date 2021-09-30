#pragma once
#include "MinesweeperBoard.h"
class MSBoardTextView :
	public MinesweeperBoard
{
	MinesweeperBoard &board;
public:
	MSBoardTextView();
	MSBoardTextView(const MSBoardTextView &view2);
	explicit MSBoardTextView(MinesweeperBoard &board2);
	void display() const;
};
