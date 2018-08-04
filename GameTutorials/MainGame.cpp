#include "MainGame.h"
#include <iostream>
#include <fstream>

#include "MCTSPlayer.h"
#include "EpsilonGreedy.h"

#include <random>
void MainGame::run() {

	for (int num_samples = 2; num_samples <= 3002;  num_samples += 100)
	{
		init();
		// Game loop
		_players[X_VAL] = std::make_unique<MCTSPlayer>(X_VAL, num_samples);
		_players[O_VAL] = std::make_unique<AI>(O_VAL);
		const int NUM_GAMES = 100;
		for (int game = 0; game < NUM_GAMES; ++game)
		{
			int rv = NO_VAL;
			while (rv == NO_VAL)
			{
				
				//_board.print();
				_players[_currentPlayer]->performMove(_board);
				changePlayer();
				rv = _board.checkVictory();
			}
			endGame(rv == TIE_VAL);

		}
		init();
		_players[O_VAL] = std::make_unique<MCTSPlayer>(X_VAL, num_samples);
		_players[X_VAL] = std::make_unique<AI>(O_VAL);
		for (int game = 0; game < NUM_GAMES; ++game)
		{
			int rv = NO_VAL;
			while (rv == NO_VAL)
			{
				//_board.print();
				_players[_currentPlayer]->performMove(_board);
				changePlayer();
				rv = _board.checkVictory();
			}
			endGame(rv == TIE_VAL);

		}
		doLogging(num_samples);
	}

 
}

MainGame::MainGame() 
{
}

void MainGame::init() {
    _gameState = GameState::PLAYING;
    _board.init(3);
    _currentPlayer = X_VAL;


  //  printf("\n\n****** Welcome to Tic-Tac-Toe ******\n\n");

   // printf("\n\n");

	
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

    //_board.print();

	if (wasTie)
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), TIE_VAL, _board.getNumMoves()));
	}
	else if (_currentPlayer == X_VAL)
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), X_VAL, _board.getNumMoves()));
	}
	else
	{
		_reports.push_back(GameReport(_players[0]->getType(), _players[1]->getType(), O_VAL, _board.getNumMoves()));
	}

	init();
}

void MainGame::doLogging(unsigned int numSamples)
{
	std::cout << numSamples << std::endl;
	std::ofstream outFile("results" + std::to_string(numSamples) + ".csv");
	if (!outFile.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}

	std::ofstream outFileSamplesFirst("resultNumSamplesFirst.csv", std::ios::out | std::ios_base::app);
	if (!outFileSamplesFirst.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}
	std::ofstream outFileSamplesSecond("resultNumSamplesSecond.csv", std::ios::out | std::ios_base::app);
	if (!outFileSamplesSecond.is_open())
	{
		std::cout << "Error opening file\n";
		return;
	}
	outFile << "numSamples," << numSamples << std::endl;
	PlayerType currentXPlayer = PlayerType::NONE;
	PlayerType currentOPlayer = PlayerType::NONE;

	int num_X_wins = 0;
	int num_O_wins = 0;
	int num_draws = 0;
	unsigned int num_moves = 0;
	unsigned int total_num_moves = 0;
	for (auto& report : _reports)
	{

		if ((currentXPlayer != report._xPlayer && currentOPlayer != report._oPlayer) && total_num_moves != 0)
		{
			outFile << "X Wins: ," << num_X_wins << ", O Wins: " << num_O_wins << ", Draws: " << num_draws << std::endl;
			outFileSamplesFirst << numSamples << "," << (static_cast<float>(num_draws) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << "," << (static_cast<float>(total_num_moves) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << std::endl;
			std::cout << num_draws << ", " << num_O_wins << ", " << num_X_wins << ", " << (static_cast<float>(num_draws) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << " " << (static_cast<float>(total_num_moves) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << std::endl;
			num_draws = num_O_wins = num_X_wins = total_num_moves = 0;
		}

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
		num_moves = report._numMoves;
		total_num_moves += num_moves;
			
		currentXPlayer = report._xPlayer;
		currentOPlayer = report._oPlayer;

		outFile << report << std::endl;
		
	}
	outFileSamplesSecond << numSamples << "," << (static_cast<float>(num_draws) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << "," << (static_cast<float>(total_num_moves) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << std::endl;
	std::cout << num_draws << ", " << num_O_wins << ", " << num_X_wins << ", " << (static_cast<float>(num_draws) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << " " << (static_cast<float>(total_num_moves) / static_cast<float>(num_draws + num_O_wins + num_X_wins)) << std::endl;
	outFile << "X Wins: ," << num_X_wins << ", O Wins: " << num_O_wins << ", Draws: " << num_draws << std::endl;
	_reports.clear();

	outFileSamplesFirst.close();
	outFileSamplesSecond.close();
}