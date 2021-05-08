#pragma once

const int bSize = 3;
const int boardSize = 9;

struct State {
	int brd[boardSize] = { 0,1,2,3,4,5,6,7,8 };
	State* parent = NULL;//int pX, pY;
	int f, g, h = INT8_MAX;

	State() {};

	State(int b[]) {
		for (int i = 0; i < boardSize; i++) brd[i] = b[i];
	}

};
bool operator < (const State& lhs, const State& rhs) {
		return lhs.f > rhs.f; // simulate min heap
}


class Board {
public:
	Board(char mode) {
		//default board: initialise with 'd'
		int ar[] = { 1,2,3,4,0,5,6,7,8 }, x;
		switch (mode) {
		case 'u'/*User Input*/:
			/*Assumed user will insert correct values*/
			cout << "Enter initial state: ";
			for (int i = 0; i < boardSize; i++) {
				cin >> x;
				ar[i] = x;
			}
			break;
		case 'r' /*Randomized board*/:
			for (int i = 0; i < boardSize; i++) {
				x = rand() % 9;
				swap(ar[i], ar[x]);
			}
		default:
			break;
		}
			initialize(ar);
	}

	Board(const State& ob) {
		for (int i = 0; i < boardSize; i++) {
			b[i] = ob.brd[i];
			if (ob.brd[i] == 0) freeSlot = i;
		}
	}
	
	~Board() {}

	//prints the current board layout
	void printBoard()
	{
		for (int i = 0; i < bSize; i++) {
			cout << "                    ";
			for (int k = 1; k <= bSize; k++)
				cout << " ---";
			cout << "\n                    |";

			for (int j = 0; j < bSize; j++) {
				if (b[i*3+j] == 0) cout << "  " << " |";
				else cout << " " << b[i*3+j] << " |";
			}
			cout << endl;
		}
		cout << "                    ";
		for (int k = 1; k <= bSize; k++)
			cout << " ---";
		cout << "\n\n";
	}

	//Slides the numbers in the puzzle.
	bool update(int key) {
		switch (key) {
		case UP:
			if (freeSlot + 3 < 9) {
				swap(b[freeSlot], b[freeSlot + 3]);
				freeSlot += 3;
				return true;
			}
			break;
		case DOWN:
			if (freeSlot - 3 >= 0) {
				swap(b[freeSlot], b[freeSlot - 3]);
				freeSlot -= 3;
				return true;
			}
			break;
		case LEFT:
			if (freeSlot != 2 && freeSlot != 5 && freeSlot != 8 ) {
				swap(b[freeSlot], b[freeSlot + 1]);
				freeSlot += 1;
				return true;
			}
			break;
		case RIGHT:
			if (freeSlot != 0 && freeSlot != 3 && freeSlot != 6) {
				swap(b[freeSlot], b[freeSlot - 1]);
				freeSlot -= 1;
				return true;
			}
			break;
		default:
			break;
		}

		return false;
	}

	State nextMove(int key) {
		Board temp = *this;
		temp.update(key);
		
		return State(temp.b);
	}
private:
	/*
	Takes input from user to initialize the board
	Sets freeSlot variable to position where value is zero
	*/
	void initialize(int arr[]) {
		for (int j = 0; j < boardSize; j++) {
			if (arr[j] == 0) freeSlot = j;
			b[j] = arr[j];
		}
	}
	
	
	int b[boardSize];	// board for the game
	int freeSlot;		// position of the free slot

	friend Puzzle;
	//friend State;
};


