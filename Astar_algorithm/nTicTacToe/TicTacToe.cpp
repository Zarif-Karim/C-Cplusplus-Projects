//Main program

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

#include "Cell.h"
#include "nTicTacToe.h"
#include "HumanPlayer.h"
#include "Minimax-nTTT.h"
#include "Game.h"

using namespace std;

int main() {
	srand(time(0));

	Game game;

	game.play();

	return 0;
}
