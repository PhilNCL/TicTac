#pragma once

class Node;

enum class PolicyType
{
	UCB1,
	EPSILON_GREEDY,
};

class SelectionPolicy
{
public:
	SelectionPolicy(int playerIndex);
	virtual ~SelectionPolicy();

	virtual Node*		getMostPromisingNode(Node* root, int totalVisits, int player);
	virtual float		scoreNode(const Node* node, int totalVisits, int player) = 0;
	virtual PolicyType  getType() = 0;

protected:
	int _playerIndex;
};

class UCB1 : public SelectionPolicy
{
public:
	UCB1(int playerIndex);
	float		scoreNode(const Node* node, int totalVisits, int player) override;
	PolicyType getType() override { return PolicyType::UCB1; }
};

class Greedy : public SelectionPolicy
{
public:
	Greedy(int playerIndex);
	float		scoreNode(const Node* node, int totalVisits, int player) override;
	PolicyType getType() override { return PolicyType::EPSILON_GREEDY; }
};