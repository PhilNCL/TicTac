#pragma once

#include <ostream>

enum class PlayerType : unsigned;

struct GameReport
{
public:
	GameReport(PlayerType xPlayer, PlayerType yPlayer, int result, unsigned int numMoves);
	~GameReport();

	PlayerType	 _xPlayer;
	PlayerType	 _oPlayer;
	int			 _result;
	unsigned int _numMoves;
};

std::ostream& operator << (std::ostream& os, const GameReport& rhs);