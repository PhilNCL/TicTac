#pragma once

enum class PolicyType
{
	UCB1
};

class SelectionPolicy
{
public:
	SelectionPolicy();
	~SelectionPolicy();

	virtual PolicyType getType() { return PolicyType::UCB1; }
};

