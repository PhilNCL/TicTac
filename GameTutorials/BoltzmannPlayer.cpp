#include "BoltzmannPlayer.h"

#include <cassert>
#include <vector>
#include "Node.h"

#include "RandomNumberGenerator.h"


BoltzmannPlayer::BoltzmannPlayer(int playerIndex, float tau, unsigned int num_samples, unsigned int rollout_depth) :
	Player(playerIndex),
	TAU(tau),
	NUM_SAMPLES(num_samples),
	ROLLOUT_DEPTH(rollout_depth)
{
}


BoltzmannPlayer::~BoltzmannPlayer()
{
}


void BoltzmannPlayer::performMove(Board& board)
{
	Node rootNode = Node(board);
	rootNode.addAllPossibleChildStates();
	const int numChildren = rootNode.getChildren().size();
	assert(numChildren != 0);

	std::vector<float> cumulativeProbabilities(numChildren, 0.0f);

	Node* chosenMove = nullptr;

	for (int sample = 0; sample < NUM_SAMPLES; ++sample)
	{
		chosenMove = nullptr;
		float normalisation = 0.0f;
		for (const Node* node : rootNode.getChildren())
		{
			normalisation += exp(node->getAverageScore() / TAU);
		}

		float cumulativeProbability = 0.0f;
		for (std::size_t idx = 0; idx < numChildren; ++idx)
		{
			cumulativeProbability += exp(rootNode.getChildren()[idx]->getAverageScore() / TAU) / normalisation;
			cumulativeProbabilities[idx] = cumulativeProbability;
		}

		float randomRoll = getProbability();
		std::size_t chosenIndex = 0;
		for (std::size_t idx = 0; idx < numChildren; ++idx)
		{
			if (randomRoll < cumulativeProbabilities[idx])
			{
				chosenIndex = idx;
				break;
			}
		}
		chosenMove = rootNode.getChildren()[chosenIndex];
		float score = performRollout(chosenMove, _thisPlayer, ROLLOUT_DEPTH);
		backPropagate(chosenMove, score);
	}
	//std::cout << "*********" << std::endl;
	//board.print()
	board = chosenMove->getState();
	//board.print();
	//std::cout << "*********" << std::endl;
	board.incrementNumMoves();
}


PlayerType BoltzmannPlayer::getType()
{
	return PlayerType::BOLTZMANN;
}

Node* BoltzmannPlayer::getMostPromisingNode(Node* root)
{
	assert(root != nullptr);

	if (root->getChildren().empty())
	{
		return root;
	}
	int numChildren = root->getChildren().size();
	std::vector<float> cumulativeProbabilities(numChildren, 0.0f);

	float normalisation = 0.0f;
	for (const Node* node : root->getChildren())
	{
		normalisation += exp(node->getAverageScore() / TAU);
	}

	float cumulativeProbability = 0.0f;
	for (std::size_t idx = 0; idx < numChildren; ++idx)
	{
		cumulativeProbability += exp(root->getChildren()[idx]->getAverageScore() / TAU) / normalisation;
		cumulativeProbabilities[idx] = cumulativeProbability;
	}

	float randomRoll = getProbability();
	std::size_t chosenIndex = 0;
	for (std::size_t idx = 0; idx < numChildren; ++idx)
	{
		if (randomRoll < cumulativeProbabilities[idx])
		{
			chosenIndex = idx;
			break;
		}
	}
	return getMostPromisingNode(root->getChildren()[chosenIndex]);
}