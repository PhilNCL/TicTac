#include "Player.h"

#include "Board.h"


Player::Player(int playerIndex)
{
	_thisPlayer = playerIndex;
	_opposingPlayer = (_thisPlayer == X_VAL) ? O_VAL : X_VAL;
}


Player::~Player()
{
}

std::string GetPlayerTypeString(PlayerType type)
{
	switch (type)
	{
	case PlayerType::MINIMAX:
	{
		return "Minimax";
	}
	case PlayerType::MCTS_UCB1:
	{
		return "MCTS_UCB1";
	}
	}
}