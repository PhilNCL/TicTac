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

	Node* chosenMove;

	for (int sample = 0; sample < NUM_SAMPLES; ++sample)
	{
		chosenMove = nullptr;
	
		float randomRoll = getProbability();
		if (randomRoll < EPSILON)
		{
			// Pick a random child
			int randomIndex = getRandomIntInRange(0, numChildren - 1);
			chosenMove = rootNode.getChildren().at(randomIndex);
		}
		else
		{
			// Pick best child
			auto iter = std::max_element(rootNode.getChildren().begin(), rootNode.getChildren().end(), [this](const Node* lhs, const Node* rhs)
			{
				return lhs->getValue(_thisPlayer) < rhs->getValue(_thisPlayer);
			});

			assert(iter != rootNode.getChildren().end());
			chosenMove = *iter;
		}

		float score = performRollout(chosenMove, _thisPlayer, ROLLOUT_DEPTH);
		backPropagate(chosenMove, score);
	}
	//std::cout << "*********" << std::endl;
	//board.print();
	board = chosenMove->getState();
	//board.print();
	//std::cout << "*********" << std::endl;
	board.incrementNumMoves();
}


PlayerType EpsilonGreedyPlayer::getType()
{
	return PlayerType::EPSILON_GREEDY;
}