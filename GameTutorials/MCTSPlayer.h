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
	~MCTSPlayer();
	// Performs the AI move
	void performMove(Board& board) override;

	PlayerType getType() override;
private:
	std::unique_ptr<SelectionPolicy> _selectionPolicy;
	int performRollout(Node* node);
	void expandNode(Node* node);
	void backPropagate(Node* node, int score);
	Node* bestChildNode(Node* node);

	const unsigned int NUM_SAMPLES;
	const unsigned int ROLLOUT_DEPTH;
};