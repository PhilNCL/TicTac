#pragma once

#include "Player.h"


#include <memory>


#include "Board.h" // Replace with forward dec.

class SelectionPolicy;
class Node;

class MCTSPlayer : public Player
{
public:
	MCTSPlayer(int playerIndex);
	MCTSPlayer(int playerIndex, unsigned int numSamples);
	MCTSPlayer(int playerIndex, unsigned int numSamples, unsigned int rolloutDepth);
	MCTSPlayer(int playerIndex, unsigned int numSamples, float explorationConstant);
	~MCTSPlayer();
	// Performs the AI move
	void performMove(Board& board) override;

	PlayerType getType() override;
private:
	std::unique_ptr<SelectionPolicy> _selectionPolicy;

	const unsigned int NUM_SAMPLES;
	const unsigned int ROLLOUT_DEPTH;
};