#pragma once

#include "Board.h"
#include "Player.h"



class AI : public Player
{
public:
	AI(int playerIndex);
	// Performs the AI move
	void performMove(Board& board) override;

	PlayerType getType() override { return PlayerType::MINIMAX; }
private:
	AiMove getBestMove(Board& board, int player, int depth = 0);
};

