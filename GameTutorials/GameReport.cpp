#include "GameReport.h"

#include <ostream>

#include "Player.h"
#include "Board.h"

GameReport::GameReport(PlayerType xPlayer, PlayerType oPlayer, int result, unsigned int numMoves) :
	_xPlayer(xPlayer),
	_oPlayer(oPlayer),
	_result(result),
	_numMoves(numMoves)
{
}


GameReport::~GameReport()
{
}


std::ostream& operator <<(std::ostream& os, const GameReport& report)
{
	os << GetPlayerTypeString(report._xPlayer) <<  "," << GetPlayerTypeString(report._oPlayer) << "," << GetResultString(report._result) << "," << report._numMoves << std::endl;
	return os;
}