#pragma once

#include "AI.h"
#include "Board.h"
#include "GameReport.h"

#include <array>
#include <vector>
#include <memory>
#include <map>

enum class GameState { PLAYING, EXIT };

#include "Player.h"

class MainGame {
public:
    // Runs the main loop
    void run();

	MainGame();

	void doLogging(unsigned int numSamples = 0);
	void logComparison();
private:
    // Initializes the game
    void init();
	void init(int size);
    // Changes players
    void changePlayer();
    // Ends a game and prompts for quit or re-try
    void endGame(bool wasTie);

    // Member Variables
    Board _board; ///< The tic-tac-toe boarde
    int _currentPlayer; ///< The index of the current player
    int _aiPlayer; ///< Index of the AI player
	std::unique_ptr<Player> _players[2]; 
    GameState _gameState; ///< The state of the game

    bool _isMultiplayer;

	std::vector<GameReport> _reports;

	std::map<std::pair<PlayerType, PlayerType>, std::array<unsigned, 3>> _playerComparisonResults;
};

