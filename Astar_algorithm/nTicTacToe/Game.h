/*
 * Game.h
 *
 *  Created on: 22 Mar. 2019
 *      Author: dongmo
 *	Modified by: Zarif Karim (17 Aug 2020)
 */

#ifndef GAME_H_
#define GAME_H_

int MinimaxPlayer::maxSearchDepth = 9;

class Game {
public:
	void play() {
		ticTacToe board;
		board.displayBoard();

		int h{1}, c{0};
		cout <<  "Enter 1 for odds, 0 for evens: ";	/* 1: Player 1  |  0: Player 2*/
		cin >> h;
		c = 1 - h;

		HumanPlayer hplayer(h);
		//MinimaxPlayer hplayer(h);
		MinimaxPlayer mplayer(c);

		bool done = false;
		int player = 1;

		while (!done) {
			int v = -1;
			int x = -1;
			int y = -1;
			if (player == h) {
				cout << "Player " << 2-player << ":\n";
				board.displayMoves(player);
				hplayer.getMove(board, v, x, y);
				board.addMove(v, x, y);
				cout << "Player " << 2-player << " plays " << v << 
					" at (" << (x + 1) << "," << (y + 1) << ") " << endl;
				board.displayBoard();
				done = checkWin(player, board);
				player = 1-player;
			} else {
				cout << "Player " << 2-player << ":\n";
				board.displayMoves(player);
				mplayer.getMove(board, v, x, y);
				board.addMove(v, x, y);
				cout << "Player " << 2-player << " plays " << v <<
					" at (" << (x + 1) << "," << (y + 1) << ") " << endl;
				board.displayBoard();
				done = checkWin(player, board);
				player = 1-player;
			}
		}
	}

	bool checkWin(int playerSymbol, ticTacToe board) {
		int gStatus = board.gameStatus(playerSymbol);

		if (gStatus == playerSymbol) {
			cout << "Player " << 2-playerSymbol << " wins!" << endl;
			return true;
		} else if (gStatus == DRAW) {
			cout << "This game is a draw!" << endl;
			return true;
		} else if (gStatus != CONTINUE) {
			return true;
		} else
			return false;
	}
};

#endif /* GAME_H_ */
