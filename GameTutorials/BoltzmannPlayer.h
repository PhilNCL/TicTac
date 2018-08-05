#pragma once

#include "Player.h"

class Node;

class BoltzmannPlayer : public Player
{
public:
	BoltzmannPlayer(int playerIndex, float tau, unsigned int NUM_SAMPLES, unsigned int ROLLOUT_DEPTH = 9);
	~BoltzmannPlayer();

	void performMove(Board& board) override;

	PlayerType getType() override;
private:
	Node* getMostPromisingNode(Node* root);
	const float TAU;
	const unsigned int NUM_SAMPLES;
	const unsigned int ROLLOUT_DEPTH;
};