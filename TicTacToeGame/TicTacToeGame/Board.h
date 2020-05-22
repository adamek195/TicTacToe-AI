#ifndef _BOARD_H
#define _BOARD_H
#include <iostream>
#include <algorithm>
#include <vector>

#define MAX 1000
#define MIN -1000


// struktura opisujaca ruch ai
struct Move
{
	int row, col;
};

//klasa reprezentujaca plansze
class Board
{
	//tablica do gry w kolko i krzyzyk
	std::vector<std::vector<char>> board;
public:
	Board(int size)
	{
		for (int i = 0; i < size; i++)
		{
			this->board.push_back(std::vector<char>());
			for (int j = 0; j < size; j++)
				this->board[i].push_back('n');
		}
	};
	~Board() {};
	bool isMovesLeft();
	void printfBoard();
	int check();
	int getSizeOfBoard();
	int getSizeOfBoardRow(int);
	char getElement(int, int);
	void setElement(int, int, char);
	int minimax(int depth, bool isMax, int alpha, int beta);
	Move findBestMove();
	void playerMove(int row,int col);
	Move aiMove();
};


#endif


