#include "MCTSPlayer.h"

const int DEFAULT_NUM_SAMPLES = 1000;
const int DEFAULT_ROLLOUT_DEPTH = 9;

#include <cassert>
#include <iostream>
#include "Node.h"
#include "SelectionPolicy.h"


MCTSPlayer::MCTSPlayer(int playerIndex) :
	Player(playerIndex),
	NUM_SAMPLES(DEFAULT_NUM_SAMPLES),
	ROLLOUT_DEPTH(DEFAULT_ROLLOUT_DEPTH)
{
	_selectionPolicy = std::make_unique<UCB1>(playerIndex);
}

MCTSPlayer::MCTSPlayer(int playerIndex, unsigned int numSamples) :
	Player(playerIndex),
	NUM_SAMPLES(numSamples),
	ROLLOUT_DEPTH(DEFAULT_ROLLOUT_DEPTH)
{
	_selectionPolicy = std::make_unique<UCB1>(playerIndex);
}

MCTSPlayer::MCTSPlayer(int playerIndex, unsigned int numSamples, unsigned int rolloutDepth) : 
	Player(playerIndex),
	NUM_SAMPLES(numSamples),
	ROLLOUT_DEPTH(rolloutDepth)
{
	_selectionPolicy = std::make_unique<UCB1>(playerIndex);
}

MCTSPlayer::MCTSPlayer(int playerIndex, unsigned int numSamples, float explorationConstant):
	Player(playerIndex),
	NUM_SAMPLES(numSamples),
	ROLLOUT_DEPTH(DEFAULT_ROLLOUT_DEPTH)
{
	_selectionPolicy = std::make_unique<UCB1>(playerIndex, explorationConstant);
}

MCTSPlayer::~MCTSPlayer()
{
}

void MCTSPlayer::performMove(Board& board)
{
	Node rootNode = Node(board);
	Node* promisingNode;
	for (int sample = 0; sample < NUM_SAMPLES; ++sample)
	{
		promisingNode = _selectionPolicy->getMostPromisingNode(&rootNode, sample, _thisPlayer);
		assert(promisingNode != nullptr);
		if (promisingNode->getNumVisits() != 0)
		{
			expandNode(promisingNode);
			if (!promisingNode->getChildren().empty())
			{
				promisingNode = promisingNode->getChildren().front();
			}
		}

		float score = performRollout(promisingNode, _thisPlayer, ROLLOUT_DEPTH);
		backPropagate(promisingNode, score);
	}

	assert(!rootNode.getChildren().empty());
	//int i = 0;
	//std::cout << "Parent::Num Visits: " << rootNode.getNumVisits() << " Tot. Score: " << rootNode.getScore() << " Av. Score: " << rootNode.getAverageScore() << std::endl;
	//for (auto child : rootNode.getChildren())
	//{
	//	std::cout << "Child: " << i++ << " Num Visits: " << child->getNumVisits() << " Tot. Score: " << child->getScore() << " Av. Score: " << child->getAverageScore() << " UCB1 Score: " << _selectionPolicy->scoreNode(child, rootNode.getNumVisits(), _thisPlayer) << std::endl;
	//}
	Node* bestMove = bestChildNode(&rootNode);
	//std::cout << "*********" << std::endl;
	//board.print();
	board = bestMove->getState();
	//board.print();
	//std::cout << "*********" << std::endl;
	board.incrementNumMoves();
}

PlayerType MCTSPlayer::getType()
{
	if (!_selectionPolicy)
	{
		return PlayerType::NONE;
	}

	switch (_selectionPolicy->getType())
	{
	case PolicyType::UCB1:
	{
		return PlayerType::MCTS_UCB1;
	}
	default:
	{
		return PlayerType::NONE;
	}
	}
}

