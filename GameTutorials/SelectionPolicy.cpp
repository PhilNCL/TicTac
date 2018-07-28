#include "SelectionPolicy.h"

#include "Node.h"

#include <cassert>
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>

const float UCB1_CONSTANT = sqrt(2.0f);

using CHILD_ITER = std::vector<Node*>::const_iterator;

SelectionPolicy::SelectionPolicy()
{

}


SelectionPolicy::~SelectionPolicy()
{
}


#include <iostream>
Node*	   SelectionPolicy::getMostPromisingNode(Node* root, int totalVisits, int player)
{
	assert(root != nullptr);
	if (root->getChildren().empty())
	{
		return root;
	}
	//int i = 0;
	//std::cout << "Parent::Num Visits: " << root->getNumVisits() << " Tot. Score: " << root->getScore() << " Av. Score: " << root->getAverageScore() << std::endl;
	//for (auto child : root->getChildren())
	//{
	//	std::cout << "Child: " << i++ << " Num Visits: " << child->getNumVisits() << " Tot. Score: " << child->getScore() << " Av. Score: " << child->getAverageScore() << " UCB1 Score: " << this->scoreNode(child, totalVisits, player) << std::endl;
	//}
	auto comparator = [totalVisits, player, this](const Node* node_lhs, const Node* node_rhs)
	{
		return this->scoreNode(node_lhs, totalVisits, player) < this->scoreNode(node_rhs, totalVisits, player);
	};

	
	const CHILD_ITER children_begin = root->getChildren().cbegin();
	const CHILD_ITER children_end = root->getChildren().cend();
	CHILD_ITER best_child = children_end;
	best_child = std::max_element(children_begin, children_end, comparator);

	assert(best_child != children_end);
	return getMostPromisingNode(*best_child, totalVisits, player);
}

float		   UCB1::scoreNode(const Node* node, int totalVisits, int player)
{
	if (!node)
	{
		return 0;
	}

	if (node->getNumVisits() == 0)
	{
		return  std::numeric_limits<float>::max();
	}
	 
	return (node->getAverageScore() + 
			UCB1_CONSTANT * sqrt(log(static_cast<float>(totalVisits)) / node->getNumVisits()));
}