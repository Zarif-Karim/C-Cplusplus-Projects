/*
 * HumanPlayer.h
 *
 *  Created on: 22 Mar. 2019
 *      Author: dongmo
 *	Modified by: Zarif Karim (17 Aug 2020)
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

class HumanPlayer {
	int playerSymbol;
public:
	HumanPlayer(int ps) {
		playerSymbol = ps;
	}

	void getMove(ticTacToe board, int& v, int& x, int& y) {
		do {
			cout << "Enter move: (v r c)";
			cin >> v >> x >> y;
			cout << endl;
			x = x - 1;
			y = y - 1;
		} while (!board.isValidMove(v, x, y));
		return;
	}
};

#endif /* HUMANPLAYER_H_ */
