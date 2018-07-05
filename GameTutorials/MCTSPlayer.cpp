#include "MCTSPlayer.h"



MCTSPlayer::MCTSPlayer(int playerIndex) :
	Player(playerIndex)
{
}

MCTSPlayer::~MCTSPlayer()
{
}

void MCTSPlayer::performMove(Board& board)
{
	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y)
		{
			if (board.getVal(x, y) == NO_VAL)
			{
				board.setVal(x, y, _thisPlayer);
				return;
			}
		}
	}
	
	//AiMove bestMove = getBestMove(board, _thisPlayer);
	//board.setVal(bestMove.x, bestMove.y, _thisPlayer);
}

PlayerType MCTSPlayer::getType()
{
	return PlayerType::MCTS_UCB1;
	if (!selectionPolicy)
	{
		return PlayerType::NONE;
	}
	

	switch (selectionPolicy->getType())
	{
	case PolicyType::UCB1:
	{
		return PlayerType::MCTS_UCB1;
	}
	default:
	{
		return PlayerType::NONE;
	}
	}
}
