#pragma once

#include <vector>

#include "Board.h"

class Node;

class Node
{
public:
	Node(Board board_state);
	~Node();

	Node*						getParent()   const { return _parent; }
	void						setParent(Node* parent)   { _parent = parent; }
	const std::vector<Node*>&   getChildren() const { return _children; }
	int						    getScore()	  const { return _score; }
	float						getAverageScore() const;

	void						incrementScore(int scoreChange) { _score += scoreChange; }
	void						incrementNumVisits() { ++_visits; }

	const Board&				getState()	  const { return _state; }
	int							getNumVisits()const { return _visits; }
	bool						isTerminal()  const { return _terminal; } 

	int							getValue(int player)    const;
	
	void						addAllPossibleChildStates();
	//Node*						getChildWithMaxScore();
private: 
	Node*			   _parent;
	std::vector<Node*> _children;

	Board				_state;
	int					_visits;
	int					_score;
	bool				_terminal;
};

