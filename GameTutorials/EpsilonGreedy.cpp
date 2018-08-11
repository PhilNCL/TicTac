#include "EpsilonGreedy.h"

#include <cassert>

#include "RandomNumberGenerator.h"
#include "Node.h"

EpsilonGreedyPlayer::EpsilonGreedyPlayer(int playerIndex, float epsilon, unsigned int num_samples, unsigned int rollout_depth) :
	Player(playerIndex),
	EPSILON(epsilon),
	NUM_SAMPLES(num_samples),
	ROLLOUT_DEPTH(rollout_depth)
{
}


EpsilonGreedyPlayer::~EpsilonGreedyPlayer()
{
}

void EpsilonGreedyPlayer::performMove(Board& board)
{	
	Node rootNode = Node(board);
	rootNode.addAllPossibleChildStates();
	const int numChildren = rootNode.getChildren().size();
	assert(numChildren != 0);

	Node* chosenMove = nullptr;

	for (int sample = 0; sample < NUM_SAMPLES; ++sample)
	{
		chosenMove = nullptr;
	
		chosenMove = getMostPromisingNode(&rootNode);

		if (chosenMove->getNumVisits() != 0)
		{
			expandNode(chosenMove);
			if (!chosenMove->getChildren().empty())
			{
				chosenMove = chosenMove->getChildren().front();
			}
		}

		float score = performRollout(chosenMove, _thisPlayer, ROLLOUT_DEPTH);
		backPropagate(chosenMove, score);
	}
	//std::cout << "*********" << std::endl;
	//board.print();
	assert(chosenMove != nullptr);
	Node* bestMove = bestChildNode(&rootNode);
	//std::cout << "*********" << std::endl;
	//board.print();
	board = bestMove->getState();
	//board.print();
	//std::cout << "*********" << std::endl;
	board.incrementNumMoves();
}


PlayerType EpsilonGreedyPlayer::getType()
{
	return PlayerType::EPSILON_GREEDY;
}

Node* EpsilonGreedyPlayer::getMostPromisingNode(Node* root)
{
	assert(root != nullptr);

	if (root->getChildren().empty())
	{
		return root;
	}

	float randomRoll = getProbability();
	int numChildren = root->getChildren().size();
	if (randomRoll < EPSILON)
	{
		// Pick a random child
		int randomIndex = getRandomIntInRange(0, numChildren - 1);
		return root->getChildren().at(randomIndex);
		//return getMostPromisingNode(root->getChildren().at(randomIndex));
	}
	else
	{
		// Pick best child
		auto iter = std::max_element(root->getChildren().begin(), root->getChildren().end(), [this](const Node* lhs, const Node* rhs)
		{
			return lhs->getAverageScore() < rhs->getAverageScore();
		});

		assert(iter != root->getChildren().end());
		return getMostPromisingNode(*iter);
	}
}