#pragma once
#include "MSBoardTextView.h"
class MSTextController :
	public MSBoardTextView
{
	MinesweeperBoard &board;
	MSBoardTextView view;
public:
	MSTextController(MinesweeperBoard &board2, MSBoardTextView view2);
	void play();
	int selectX();
	int selectY();
	~MSTextController();
};
