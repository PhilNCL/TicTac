#include "Board.h"
#include "Node.h"

#include <algorithm>
#include <cassert>

void expandNode(Node* node)
{
	node->addAllPossibleChildStates();
}

void backPropagate(Node* node, float score)
{
	Node* currentNode = node;
	while (currentNode)
	{
		currentNode->incrementNumVisits();
		currentNode->incrementScore(score);
		currentNode = currentNode->getParent();
	}
}


float performRollout(Node* node, int player, unsigned int ROLLOUT_DEPTH)
{
	Board tempBoard = node->getState();

	for (int depth = 0; depth < ROLLOUT_DEPTH; ++depth)
	{
		if (tempBoard.isFinished())
		{
			return tempBoard.getScore(player);
		}

		int currentPlayer = togglePlayer(tempBoard);
		tempBoard.makeRandomMove(currentPlayer);
	}
	return tempBoard.getScore(player);
}


Node* bestChildNode(Node* node)
{
	assert(node != nullptr);
	auto iter = std::max_element(node->getChildren().begin(), node->getChildren().end(), [](const Node* lhs, const Node* rhs)
	{
		return lhs->getAverageScore() < rhs->getAverageScore();
	});

	if (iter != node->getChildren().end())
	{
		return *iter;
	}
	else
	{
		return nullptr;
	}
}


Node::Node(Board board_state) :
	_state(board_state)
{
}


Node::~Node()
{
	for (Node* child : _children)
	{
		delete child;
	}
}


int	Node::getValue(int player) const
{
	return _state.getScore(player);
}

float	Node::getAverageScore() const
{
	if (_visits)
	{
		return static_cast<float>(_score) / _visits;
	}
	else
	{
		return 0.0f;
	}
}

void Node::addAllPossibleChildStates()
{
	for (const Board& board : _state.possibleStates())
	{
		Node* child = new Node(board);
		child->setParent(this);
		_children.emplace_back(child);
	}
}

//Node* Node::getChildWithMaxScore()
//{
//	auto iter = std::max_element(_children.begin(), _children.end(), [](const Node* lhs, const Node* rhs)
//	{
//		return lhs->getAverageScore() < rhs->getAverageScore();
//	});
//
//	if (iter != _children.end())
//	{
//		return *iter;
//	}
//	else
//	{
//		return nullptr;
//	}
//}