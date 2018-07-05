#pragma once

#include "Player.h"

class Human : public Player
{
public:
	Human(int playerIndex);
	~Human();

	void performMove(Board& board) override;
	PlayerType getType() override { return PlayerType::HUMAN; }
private:

};

