#pragma once

class Board;

#include <string>

enum class PlayerType : unsigned
{
	HUMAN,
	MINIMAX,
	MCTS_UCB1,
	NONE
};

struct AiMove
{
	AiMove() {}
	AiMove(int Score) : score(Score) {}
	int x;
	int y;
	int score;
};

std::string GetPlayerTypeString(PlayerType type);

class Player
{
public:
	Player(int playerIndex);
	~Player();

public:
	// Performs the AI move
	virtual void		performMove(Board& board) = 0;
	virtual PlayerType  getType() = 0;
protected:
	int _thisPlayer; ///< Index of the AI
	int _opposingPlayer; ///< Index of the player
};


