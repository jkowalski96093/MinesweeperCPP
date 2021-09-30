#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum GameMode { EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
	bool hasMine;
	bool hasFlag;
	bool isRevealed;
};

class MinesweeperBoard
{
	std::vector<std::vector<Field>> board;
	int width;
	int height;
	GameState game;
	int moveCount;
	int flagCount;

public:

	MinesweeperBoard();
	MinesweeperBoard(const MinesweeperBoard *board2);
	MinesweeperBoard(int width, int height);
	MinesweeperBoard(int width, int height, GameMode mode);
	~MinesweeperBoard();

	int getBoardWidth() const;

	int getBoardHeight() const;

	int getMoveCount() const;

	int getMineCount() const;  //all mines on board

	int getFlagCount() const;  // number of flags left

	bool onBoard(int x, int y) const; //is (x,y) on the board

	bool hasFlag(int x, int y) const; // 1 - flag, 0 - no flag

	bool hasMine(int x, int y) const;

	void toggleFlag(int x, int y); //toggles flag

	void revealField(int x, int y); //reveales a field

	void revealFieldV2(int x, int y); //reveals field and if it has 0 mines around reveals other fields - does not work (yet)

	bool isRevealed(int x, int y) const; // 1-revealed , 0-not revealed

	void isWin(); // changes gamestate to FINISHED_WIN if there is a flag on every single mine

	GameState getGameState() const;

	int countMines(int x, int y) const; //how many mines around (x,y)

	void debug_display() const; //shows display in console

	void set_mine(int mWidth, int mHeight); //sets one mine

	void place_mines(int nofMines); //places nofMines randomly on board


	char getFieldInfo(int x, int y) const;
	/*
	# - outside board
	F - not revealed and has flag
	_ - not revealed and does not have flag
	x - is revealed and has mine
	' ' - is revealed and has 0 mines around it
	1 - is revealed and has some mines around it
	*/
};

