#include "Board.h"
#include "Node.h"

#include <algorithm>

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
	return static_cast<float>(_score) / _visits;
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