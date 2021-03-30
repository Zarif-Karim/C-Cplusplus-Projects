/*
 * MiniMaxPlayer.h
 *
 *  Created on: 17 Aug. 2020
 *      Author: Zarif Karim
 */


#ifndef MINIMAXPLAYER_H_
#define MINIMAXPLAYER_H_

struct Util {
	int x, y, z;
};

class MinimaxPlayer {
	int playerSymbol;
	static int maxSearchDepth;

	int eval(int r, int d) {
		int rVal;
		if (r == playerSymbol) rVal = 10;
		else if (r == DRAW) rVal = 0;
		else rVal = -10;

		return (rVal - d);
	}
public:
	MinimaxPlayer(int ps) {
		playerSymbol = ps;
		/*cout << "Enter maximun Search Tree Depth for Minimax Player: ";
		cin >> maxSearchDepth;*/
	}

	void getMove(ticTacToe board, int& v, int& x, int& y) {
		//This if block is for testing purpose only
		if (board.isEmpty()) {
			int n[4] = { 1,3,7,9 };
			if (rand() % 2 == 1) {
				x = rand() % 3;
				y = abs(x - 1);
			}
			else {
				y = rand() % 3;
				x = abs(y - 1);
			}
			v = n[rand() % 4];
			return; 
		}

		int maxUtil = INT8_MIN;
		vector<Util> choices;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board.getGrid(i, j) == 0) {
					
					for (int z : board.getAvailableMoves(playerSymbol)) {
						board.addMove(z, i, j);
						int utility = minimax(board, 0, INT8_MIN, INT8_MAX, 1-playerSymbol);
						// print for testing and stat logging|remove before submission
						//printf("(%d,%d): %d [U: %+d]\t", i+1, j+1, z, utility); 
						board.removeMove(z, i, j);

						if (utility > maxUtil) {
							maxUtil = utility;
							choices.clear();
							choices.push_back({i,j,z});
						}
						else if (utility == maxUtil) {
							choices.push_back({i, j, z});
						}
					}
					cout << endl;
				}
			}
		}
		Util m = choices[rand() % choices.size()];
		v = m.z;
		x = m.x;
		y = m.y;
	}

	int minimax(ticTacToe board, int maxDepth, int alpha, int beta, int player) {
		int r = board.gameStatus(1-player);
		if (r != CONTINUE || maxDepth == maxSearchDepth) return eval(r, maxDepth);

		if (/*maxPlayer*/player == playerSymbol) {
			int maxUtil = INT8_MIN; bool b = false;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board.getGrid(i, j) == 0) {
						for (int x : board.getAvailableMoves(playerSymbol)) {
							board.addMove(x, i, j);
							int utility = minimax(board, maxDepth + 1, alpha, beta, 1-playerSymbol);
							maxUtil = max(maxUtil, utility);
							board.removeMove(x, i, j);
							alpha = max(alpha, utility);
							if (beta <= alpha) {
								b = true;
								break;
							}
						}
					}
					if (b) break;
				}
				if (b) break;
			}
			return maxUtil;
		}
		else {
			int minUtil = INT8_MAX; bool b = false;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board.getGrid(i, j) == 0) {
						for (int x : board.getAvailableMoves(1-playerSymbol)) {
							board.addMove(x, i, j);
							int utility = minimax(board, maxDepth + 1, alpha, beta, playerSymbol);
							board.removeMove(x, i, j);
							minUtil = min(minUtil, utility);
							beta = min(beta, utility);
							if (beta <= alpha) {
								b = true;
								break;
							}
						}
					}
					if (b) break;
				}
				if (b) break;
			}
			return minUtil;
		}
	}
};

#endif /* MINIMAXPLAYER_H_ */


