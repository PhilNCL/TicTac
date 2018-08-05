#pragma once

#include "Player.h"

class RandomPlayer : public Player
{
public:
	RandomPlayer(int playerIndex);
	~RandomPlayer();

	void performMove(Board& board) override;

	PlayerType getType() override;
};

