#include "Human.h"

#include "Board.h"

#include <iostream>


Human::Human(int playerIndex) :
	Player(playerIndex)
{

}


Human::~Human()
{
}


void Human::performMove(Board& board)
{
	// Get input
	bool wasValid = false;

	int x, y;
	do {
		printf("Enter the X: ");
		while (!(std::cin >> x)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			printf("ERROR: Invalid input!");
		}
		printf("Enter the Y: ");
		while (!(std::cin >> y)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			printf("ERROR: Invalid input!");
		}

		if (x < 1 || y < 1 || x > board.getSize() || y > board.getSize()) {
			printf("ERROR: Invalid X or Y!\n");
		}
		else if (board.getVal(x - 1, y - 1) != 0) {
			printf("ERROR: That spot is taken!\n");
		}
		else {
			wasValid = true;
		}

	} while (!wasValid);

	// Now place the token
	board.setVal(x - 1, y - 1, _thisPlayer);
}