#include "Board.h"

#include <string>

#include "RandomNumberGenerator.h"
#include "WinConstants.h"

// Arrays of chars for printing out the board all fancy-like
const char GLYPHS[3][3][3] = {
	{
		{ '#', ' ', '#' },
		{ ' ', '#', ' ' },
		{ '#', ' ', '#' }
	},

	{
		{ '#', '#', '#' },
		{ '#', ' ', '#' },
		{ '#', '#', '#' }
	},

{
	{ ' ', ' ', ' ' },
	{ ' ', ' ', ' ' },
	{ ' ', ' ', ' ' }
},
};

std::string GetResultString(int boardValue)
{
	switch (boardValue)
	{
		{
		case X_VAL:
			return "X";
			break;
		}

		{
		case O_VAL:
			return "O";
			break;
		}

		{
		case TIE_VAL:
			return "T";
			break;
		}

	}
}


void Board::init(int size) {
    // Just cap it at 9 since we have limited console space
    if (size > 9) size = 9;
    _size = size;
    // Set the board size
    _board.resize(size * size);
    // Clear it
    clear();
	_lastPlayer = O_VAL;
	_numMoves = 0;
}

void Board::clear() {
    for (size_t i = 0; i < _board.size(); i++) {
        _board[i] = NO_VAL;
    }
}

void Board::print() const {
    // Instead of calling printf multiple times, we build a single
    // string and call printf once, since its faster.

    std::string text = "";
    // Just reserve a bunch of memory, this should be enough
    text.reserve(_size * _size * 4);

    // Make top guide
    addGuide(text);

    // Loop through columns
    for (int y = 0; y < _size; y++) {
        // Add line
        addHorizontalLine(text);
        // Loop through glyph y
        for (int gy = 0; gy < 3; gy++) {
            // Add number or space
            if (gy == 1) {
                text += std::to_string(_size - y);
            } else {
                text += " ";
            }
            // Loop through row cells
            for (int x = 0; x < _size; x++) {
                // Loop through glyph x
                text += "|";
                for (int gx = 0; gx < 3; gx++) {
                    text += GLYPHS[getVal(x, _size - y - 1)][gy][gx];
                }
            }
            text += "|";
            // Add number or newline
            if (gy == 1) {
                text += std::to_string(_size - y) + "\n";
            } else {
                text += "\n";
            }
        }
    }
    // Add bottom line
    addHorizontalLine(text);\
    // Make bottom guide
    addGuide(text);

    // printf is faster than cout
    
    // Print the string
    printf("%s\n", text.c_str());
}

int Board::checkVictory() const {
    bool victory;
    int c;
    // Check the rows
    for (int y = 0; y < _size; y++) {
        c = getVal(0, y);
        if (c != NO_VAL) {
            victory = true;
            for (int x = 0; x < _size; x++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check the columns
    for (int x = 0; x < _size; x++) {
        c = getVal(x, 0);
        if (c != NO_VAL) {
            victory = true;
            for (int y = 0; y < _size; y++) {
                if (getVal(x, y) != c) {
                    victory = false;
                    break;
                }
            }
            if (victory) return c;
        }
    }

    // Check top left diagonal
    c = getVal(0, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(xy, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check top right diagonal
    c = getVal(_size - 1, 0);
    if (c != NO_VAL) {
        victory = true;
        for (int xy = 0; xy < _size; xy++) {
            if (getVal(_size - xy - 1, xy) != c) {
                victory = false;
                break;
            }
        }
        if (victory) return c;
    }

    // Check for tie game
    for (size_t i = 0; i < _board.size(); i++) {
        if (_board[i] == NO_VAL) return NO_VAL;
    }
    // If we get here, every spot was filled, so return tie
    return TIE_VAL;
}

bool Board::isFinished() const {
	bool victory;
	int c;
	// Check the rows
	for (int y = 0; y < _size; y++) {
		c = getVal(0, y);
		if (c != NO_VAL) {
			victory = true;
			for (int x = 0; x < _size; x++) {
				if (getVal(x, y) != c) {
					victory = false;
					break;
				}
			}
			if (victory) return true;
		}
	}

	// Check the columns
	for (int x = 0; x < _size; x++) {
		c = getVal(x, 0);
		if (c != NO_VAL) {
			victory = true;
			for (int y = 0; y < _size; y++) {
				if (getVal(x, y) != c) {
					victory = false;
					break;
				}
			}
			if (victory) return true;
		}
	}

	// Check top left diagonal
	c = getVal(0, 0);
	if (c != NO_VAL) {
		victory = true;
		for (int xy = 0; xy < _size; xy++) {
			if (getVal(xy, xy) != c) {
				victory = false;
				break;
			}
		}
		if (victory) return true;
	}

	// Check top right diagonal
	c = getVal(_size - 1, 0);
	if (c != NO_VAL) {
		victory = true;
		for (int xy = 0; xy < _size; xy++) {
			if (getVal(_size - xy - 1, xy) != c) {
				victory = false;
				break;
			}
		}
		if (victory) return true;
	}

	// Check for tie game
	for (size_t i = 0; i < _board.size(); i++) {
		if (_board[i] == NO_VAL) return false;
	}
	// If we get here, every spot was filled, so return tie
	return true;
}

void Board::addHorizontalLine(std::string& s) const {
    s += "-";
    for (int x = 0; x < _size; x++) {
        s += "----";
    }
    s += "--\n";
}

void Board::addGuide(std::string& s) const {
    s += " ";
    for (int i = 1; i <= _size; i++) {
        s += "| " + std::to_string(i) + " ";
    }
    s += "|\n";
}


void Board::makeRandomMove(int player)
{
	std::vector<std::size_t> emptySlots;

	for (size_t i = 0; i < _board.size(); i++) {
		if (_board[i] == NO_VAL)
		{
			emptySlots.push_back(i);
		}
	}

	int randomIndex = emptySlots[getRandomIntInRange(0, emptySlots.size() - 1)];
	setVal(randomIndex, player);
}

float Board::getScore(int player) const
{
	switch (checkVictory())
	{
	case X_VAL:
		return (player == X_VAL) ? MAX_WIN : MIN_WIN;
	case O_VAL:
		return (player == O_VAL) ? MAX_WIN : MIN_WIN;
	case TIE_VAL:
		return TIE;
	}
	return 0;
	//int score = 0;
	//// Check the rows
	//for (int y = 0; y < _size; y++)
	//{
	//	if (countOpponentInRow(player, y) == 0)
	//	{
	//		switch (countPlayerInRow(player, y))
	//		{
	//		case 1:
	//		{
	//			score += SCORE_SINGLE_TOKEN;
	//			break;
	//		}
	//		case 2:
	//		{
	//			score += SCORE_DOUBLE_TOKEN;
	//			break;
	//		}

	//		}
	//	}
	//	else
	//	{
	//		switch (countOpponentInRow(player, y))
	//		{
	//		case 1:
	//		{
	//			score -= SCORE_SINGLE_TOKEN;
	//			break;
	//		}
	//		case 2:
	//		{
	//			score -= SCORE_DOUBLE_TOKEN;
	//			break;
	//		}

	//		}
	//	}
	//}

	//// Check the columns
	//for (int y = 0; y < _size; y++)
	//{
	//	if (countOpponentInCol(player, y) == 0)
	//	{
	//		switch (countPlayerInCol(player, y))
	//		{
	//		case 1:
	//		{
	//			score += SCORE_SINGLE_TOKEN;
	//			break;
	//		}
	//		case 2:
	//		{
	//			score += SCORE_DOUBLE_TOKEN;
	//			break;
	//		}

	//		}
	//	}
	//	else
	//	{
	//		switch (countOpponentInCol(player, y))
	//		{
	//		case 1:
	//		{
	//			score -= SCORE_SINGLE_TOKEN;
	//			break;
	//		}
	//		case 2:
	//		{
	//			score -= SCORE_DOUBLE_TOKEN;
	//			break;
	//		}

	//		}
	//	}
	//}

	//// Check top left diagonal
	//if (countOpponentInForwardDiagonal(player) == 0)
	//{
	//	switch (countPlayerInForwardDiagonal(player))
	//	{
	//	case 1:
	//	{
	//		score += SCORE_SINGLE_TOKEN;
	//		break;
	//	}
	//	case 2:
	//	{
	//		score += SCORE_DOUBLE_TOKEN;
	//		break;
	//	}

	//	}
	//}
	//else
	//{
	//	switch (countOpponentInForwardDiagonal(player))
	//	{
	//	case 1:
	//	{
	//		score -= SCORE_SINGLE_TOKEN;
	//		break;
	//	}
	//	case 2:
	//	{
	//		score -= SCORE_DOUBLE_TOKEN;
	//		break;
	//	}

	//	}
	//}

	//// Check top right diagonal
	//if (countOpponentInReverseDiagonal(player) == 0)
	//{
	//	switch (countPlayerInReverseDiagonal(player))
	//	{
	//	case 1:
	//	{
	//		score += SCORE_SINGLE_TOKEN;
	//		break;
	//	}
	//	case 2:
	//	{
	//		score += SCORE_DOUBLE_TOKEN;
	//		break;
	//	}

	//	}
	//}
	//else
	//{
	//	switch (countOpponentInReverseDiagonal(player))
	//	{
	//	case 1:
	//	{
	//		score -= SCORE_SINGLE_TOKEN;
	//		break;
	//	}
	//	case 2:
	//	{
	//		score -= SCORE_DOUBLE_TOKEN;
	//		break;
	//	}

	//	}
	//}

	//score += (_lastPlayer == player) ? 0 : SCORE_TURN_ADVANTAGE;

	//return score;
}



std::vector<Board> Board::possibleStates()
{
	std::vector<Board> states;
	int player = (_lastPlayer == X_VAL) ? O_VAL : X_VAL;
	for (size_t i = 0; i < _board.size(); i++) {
		if (_board[i] == NO_VAL)
		{
			Board temp(*this);
			temp.setVal(i, player);
			states.emplace_back(temp);
		}
	}
	return states;
}


unsigned int Board::countPlayerInRow(int player, unsigned int row) const
{
	unsigned int numPlayer = 0;
	for (int y = 0; y < _size; y++) 
	{
		if (getVal(row, y) == player)
		{
			++numPlayer;
		}
	}
	return numPlayer;
}

unsigned int Board::countOpponentInRow(int player, unsigned int row) const
{
	return countPlayerInRow(player == X_VAL ? O_VAL : X_VAL, row);
}

unsigned int Board::countPlayerInCol(int player, unsigned int col) const
{
	unsigned int numPlayer = 0;
	for (int y = 0; y < _size; y++)
	{
		if (getVal(y, col) == player)
		{
			++numPlayer;
		}
	}
	return numPlayer;
}

unsigned int Board::countOpponentInCol(int player, unsigned int col) const
{
	return countPlayerInCol(player == X_VAL ? O_VAL : X_VAL, col);
}

unsigned int Board::countPlayerInForwardDiagonal(int player) const
{
	unsigned int numPlayer = 0;
	for (int d = 0; d < _size; d++) 
	{
		if (getVal(d, d) == player) 
		{
			++numPlayer;
		}
	}
	return numPlayer;
}


unsigned int Board::countOpponentInForwardDiagonal(int player) const
{
	return countPlayerInForwardDiagonal(player == X_VAL ? O_VAL : X_VAL);
}

unsigned int Board::countPlayerInReverseDiagonal(int player) const
{
	unsigned int numPlayer = 0;
	for (int d = 0; d < _size; d++) 
	{
		if (getVal(_size - d - 1, d) == player) 
		{
			++numPlayer;
		}
	}
	return numPlayer;
}

unsigned int Board::countOpponentInReverseDiagonal(int player) const
{
	return countPlayerInReverseDiagonal(player == X_VAL ? O_VAL : X_VAL);
}
