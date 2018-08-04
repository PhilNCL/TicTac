#pragma once

#include "Player.h"

class EpsilonGreedyPlayer : public Player
{
public:
	EpsilonGreedyPlayer(int playerIndex, float epsilon, unsigned int NUM_SAMPLES, unsigned int ROLLOUT_DEPTH = 9);
	~EpsilonGreedyPlayer();

	void performMove(Board& board) override;

	PlayerType getType() override;

private:


	const float EPSILON;
	const unsigned int NUM_SAMPLES;
	const unsigned int ROLLOUT_DEPTH;
};

