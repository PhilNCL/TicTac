#pragma once

#include <vector>
#include <string>
#include <random>


const int TIE_VAL = -1;
// Indexes for board values
const int NO_VAL = 2;
const int X_VAL = 1;
const int O_VAL = 0;

std::string GetResultString(int boardValue);
// NOTE: The const after a function name makes a const function,
// indicating that the function won't change anything in the class.
// Const functions CAN NOT call non-const functions of the same class.

// Game board class
class Board {
public:
	Board();
    // Initializes the board
    void init(int size);
    // Clears the board
    void clear();
    // Prints the board to standard output
    void print() const;

    // If no player won, returns NO_VAL. Otherwise returns X_VAL, O_VAL or TIE_VAL
    int checkVictory() const;

    // Sets value at x,y spot
    void setVal(int x, int y, int val) {
        _board[y * _size + x] = val;
		_lastPlayer = val;
    }

	void setVal(int index, int player)
	{
		_board[index] = player;
		_lastPlayer = player;
	}

    // Gets value at x,y spot
    int getVal(int x, int y) const {
        return _board[y * _size + x];
    }

	void makeRandomMove(int player);

    // Getters
    int getSize() const { return _size; }
	int getLastPlayer() const { return _lastPlayer; }
	int getScore(int player) const;
	bool isFinished() const;
	std::vector<Board> possibleStates();
private:
    // Adds a horizontal line to string for printing
    void addHorizontalLine(std::string& s) const;
    // Adds a horizontal axis guide line to string for printing
    void addGuide(std::string& s) const;

	unsigned int countPlayerInRow(int player, unsigned int row) const;
	unsigned int countOpponentInRow(int player, unsigned int row) const;
	unsigned int countPlayerInCol(int player, unsigned int col) const;
	unsigned int countOpponentInCol(int player, unsigned int col) const;
	unsigned int countPlayerInForwardDiagonal(int player) const;
	unsigned int countOpponentInForwardDiagonal(int player) const;
	unsigned int countPlayerInReverseDiagonal(int player) const;
	unsigned int countOpponentInReverseDiagonal(int player) const;

    std::vector<int> _board;
    int _size;
	int _lastPlayer;
	std::mt19937_64 _randomEngine;
};

