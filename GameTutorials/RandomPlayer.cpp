#include "RandomPlayer.h"

#include "Board.h"

RandomPlayer::RandomPlayer(int playerIndex) :
	Player(playerIndex)
{
}


RandomPlayer::~RandomPlayer()
{
}

void RandomPlayer::performMove(Board& board)
{
	board.makeRandomMove(_thisPlayer);
}

PlayerType RandomPlayer::getType()
{
	return PlayerType::RANDOM;
}