#include "MainGame.h"
#include <iostream>
#include <fstream>

#include "MCTSPlayer.h"

void MainGame::run() {
    init();
    // Game loop
	_players[X_VAL] = std::make_unique<AI>(X_VAL);
	_players[O_VAL] = std::make_unique<MCTSPlayer>(O_VAL);
	const int NUM_GAMES = 10;
	for (int game = 0; game < NUM_GAMES; ++game)
	{
		int rv = NO_VAL;
		while (rv == NO_VAL)
		{
			_board.print();
			_players[_currentPlayer]->performMove(_board);
			changePlayer();
			rv = _board.checkVictory();
		}
		endGame(rv == TIE_VAL);

	}
	init();
	_players[X_VAL] = std::make_unique<MCTSPlayer>(X_VAL);
	_players[O_VAL] = std::make_unique<AI>(O_VAL);
	for (int game = 0; game < NUM_GAMES; ++game)
	{
		int rv = NO_VAL;
		while (rv == NO_VAL)
		{
			_board.print();
			_players[_currentPlayer]->performMove(_board);
			changePlayer();
			rv = _board.checkVictory();
		}
		endGame(rv == TIE_VAL);

	}
 
}

MainGame::MainGame()
{
}

void MainGame::init() {
    _gameState = GameState::PLAYING;
    _board.init(3);
    _currentPlayer = X_VAL;

    printf("\n\n****** Welcome to Tic-Tac-Toe ******\n\n");

    printf("\n\n");

	
	_isMultiplayer = false;
}

void MainGame::changePlayer() {
    if (_currentPlayer == X_VAL) {
        _currentPlayer = O_VAL;
    } else {
        _currentPlayer = X_VAL;
    }
}

void MainGame::endGame(bool wasTie) {

    _board.print();

	if (wasTie)
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), TIE_VAL));
	}
	else if (_currentPlayer == X_VAL)
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), X_VAL));
	}
	else
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), O_VAL));
	}

	init();
}

void MainGame::doLogging()
{
	std::ofstream outFile("results.csv");
	if (!outFile.is_open())
	{
		return;
	}

	PlayerType currentXPlayer = PlayerType::NONE;
	PlayerType currentOPlayer = PlayerType::NONE;

	int num_X_wins = 0;
	int num_O_wins = 0;
	int num_draws = 0;
	for (auto& report : _reports)
	{
		if (currentXPlayer == report._xPlayer && currentOPlayer == report._oPlayer)
		{
			switch (report._result)
			{
			case X_VAL:
				++num_X_wins;
				break;
			case O_VAL:
				++num_O_wins;
				break;
			case TIE_VAL:
				++num_draws;
				break;
			}
			
		}
		else
		{
			outFile << "X Wins: ," << num_X_wins << ", O Wins: " << num_O_wins << ", Draws: " << num_draws << std::endl;
			num_draws = num_O_wins = num_X_wins = 0;
			currentXPlayer = report._xPlayer;
			currentOPlayer = report._oPlayer;
		}
		outFile << report << std::endl;
		
	}

	outFile << "X Wins: ," << num_X_wins << ", O Wins: " << num_O_wins << ", Draws: " << num_draws << std::endl;
}