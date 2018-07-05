#pragma once

#include <ostream>

enum class PlayerType : unsigned;

struct GameReport
{
public:
	GameReport(PlayerType xPlayer, PlayerType yPlayer, int result);
	~GameReport();

	PlayerType _xPlayer;
	PlayerType _oPlayer;
	int		   _result;
};

std::ostream& operator << (std::ostream& os, const GameReport& rhs);