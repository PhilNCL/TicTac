#include "GameReport.h"

#include <ostream>

#include "Player.h"
#include "Board.h"

GameReport::GameReport(PlayerType xPlayer, PlayerType oPlayer, int result) :
	_xPlayer(xPlayer),
	_oPlayer(oPlayer),
	_result(result)
{
}


GameReport::~GameReport()
{
}


std::ostream& operator <<(std::ostream& os, const GameReport& report)
{
	os << GetPlayerTypeString(report._xPlayer) <<  "," << GetPlayerTypeString(report._oPlayer) << "," << GetResultString(report._result) << std::endl;
	return os;
}