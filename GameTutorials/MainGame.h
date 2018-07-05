#pragma once

#include "AI.h"
#include "Board.h"
#include "GameReport.h"

#include <vector>
#include <memory>

enum class GameState { PLAYING, EXIT };

class Player;

class MainGame {
public:
    // Runs the main loop
    void run();

	MainGame();

	void doLogging();

private:
    // Initializes the game
    void init();

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

};

