#pragma once

class Node;

enum class PolicyType
{
	UCB1
};

class SelectionPolicy
{
public:
	SelectionPolicy();
	virtual ~SelectionPolicy();

	virtual Node*		getMostPromisingNode(Node* root, int totalVisits, int player);
	virtual float		scoreNode(const Node* node, int totalVisits, int player) = 0;
	virtual PolicyType  getType() = 0;
};

class UCB1 : public SelectionPolicy
{
	float		scoreNode(const Node* node, int totalVisits, int player) override;
	PolicyType getType() override { return PolicyType::UCB1; }
};