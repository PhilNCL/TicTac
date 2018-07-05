#pragma once

#include "Player.h"
#include "SelectionPolicy.h"

#include <memory>


#include "Board.h" // Replace with forward dec.

class MCTSPlayer : public Player
{
public:
	MCTSPlayer(int playerIndex);
	~MCTSPlayer();
	// Performs the AI move
	void performMove(Board& board) override;

	PlayerType getType() override;
private:
	std::unique_ptr<SelectionPolicy> selectionPolicy;

	AiMove getBestMove(Board& board, int player, int depth  = 0)
	{
		int retv = board.checkVictory();

		if (retv == _thisPlayer) // if AI won, return great
		{
			return AiMove(10 - depth);
		}
		else if (retv == _opposingPlayer) // if human won, return low
		{
			return AiMove(depth - 10);
		}
		else if (retv == TIE_VAL) // if nobody won, return 0
		{
			return AiMove(0);
		}

		depth++; // make sure you make it the always hardest for the human

		std::vector<AiMove> moves;

		// loop through holes
		for (int y = 0; y < board.getSize(); y++)
		{
			for (int x = 0; x < board.getSize(); x++)
			{
				if (board.getVal(x, y) == NO_VAL)
				{
					AiMove move;
					move.x = x;
					move.y = y;

					board.setVal(x, y, player);

					// check if a good move
					move.score = getBestMove(board, player == _thisPlayer ? _opposingPlayer : _thisPlayer, depth).score;

					moves.push_back(move);

					board.setVal(x, y, NO_VAL);
				}
			}
		}

		// pick the best move
		int bestMove = 0;
		if (player == _thisPlayer)
		{
			int bestScore = -1000;
			for (size_t i = 0; i < moves.size(); i++)
			{
				if (moves[i].score > bestScore)
				{
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}
		else
		{
			int bestScore = 1000;
			for (size_t i = 0; i < moves.size(); i++)
			{
				if (moves[i].score < bestScore)
				{
					bestMove = i;
					bestScore = moves[i].score;
				}
			}
		}

		// return it
		return moves[bestMove];
	}
};