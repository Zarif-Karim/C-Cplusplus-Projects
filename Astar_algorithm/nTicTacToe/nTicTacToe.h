//Tic-Tac-Toe Header file

#define CONTINUE 20
#define DRAW 10

struct Move {
	int value;
	bool used;
};

class ticTacToe {
public:
	ticTacToe(const ticTacToe& cboard) {
		for (int row = 0; row < 3; row++)
			for (int col = 0; col < 3; col++)
				board[row][col] = cboard.board[row][col];

		for (int i = 0; i < 9; i++) moves[i] = cboard.moves[i];

		noOfMoves = cboard.noOfMoves;
	}

	void setBoard() {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cin >> board[i][j];
				
			}
		}
	}

	int getGrid(int i, int j) {
		return board[i][j];
	}

	bool isFull() {
		return (noOfMoves >= 9);
	}

	bool isEmpty() {
		return (noOfMoves == 0);
	}

	void displayBoard() const;
	//Function to print the board.

	vector<int> getAvailableMoves(int playerSymbol);
	//Function to get available moves for current player

	void displayMoves(int playerSymbol);
	//Function to print available mover of current player

	bool isValidMove(int value, int x, int y) const;
	//Function to determine if a move is valid.

	void addMove(int moveSymbol, int x, int y);
	//Function to get a move for a player

	void removeMove(int moveSymbol, int x, int y);
	//Function to get a move for a player

	int gameStatus(int player);
	//Function to determine the current status of the game.

	void reStart();
	//Function to restart the game.

	ticTacToe();
	//Default constructor.
	//Postcondition: Initializes the board to an empty state.

private:
	int board[3][3];

	Move moves[9];
	int noOfMoves;
};

void ticTacToe::displayBoard() const {
	cout << "   1    2    3" << endl << endl;

	for (int row = 0; row < 3; row++) {
		cout << row + 1;

		for (int col = 0; col < 3; col++) {
			cout << setw(3);
			if (board[row][col] == 0) cout << ' ';
			else cout << board[row][col];

			if (col != 2)
				cout << " |";
		}

		cout << endl;

		if (row != 2)
			cout << " ____|____|____" << endl << "     |    |    " << endl;
	}

	cout << endl;
}

vector<int> ticTacToe::getAvailableMoves(int playerSymbol) {
	vector<int> avlMoves;
	for (int i = 0; i < 9; i++) {
		if (moves[i].value % 2 == playerSymbol && !moves[i].used)
			avlMoves.push_back(moves[i].value);
	}
	return avlMoves;
}

void ticTacToe::displayMoves(int playerSymbol) {
	cout << "Available moves: ";
	for (int x : getAvailableMoves(playerSymbol)) cout << x << " ";
	cout << endl;
}

bool ticTacToe::isValidMove(int value, int row, int col) const {
	if (0 <= row && row <= 2 && 0 <= col && col <= 2 && 
		board[row][col] == 0 && !moves[value-1].used
		&& value > 0 && value < 10)
		return true;
	else
		return false;
}

void ticTacToe::addMove(int playerValue, int x, int y) {
	if (!isValidMove(playerValue, x, y))
		return;

	board[x][y] = playerValue;
	moves[playerValue - 1].used = true;

	++noOfMoves;
}

void ticTacToe::removeMove(int playerValue, int x, int y) {
	if (board[x][y] == 0) return;

	board[x][y] = 0;
	moves[playerValue - 1].used = false;

	--noOfMoves;
}

int ticTacToe::gameStatus(int player) {
	//Check rows for a win
	for (int row = 0; row < 3; row++)
		if (board[row][0] != 0 && board[row][1] != 0 && board[row][2] != 0 &&
			(board[row][0] + board[row][1] + board[row][2]) == 15) {
			//cout << "ROW WIN!\n";
			return player;//board[row][0] % 2;
		}

	//Check columns for a win
	for (int col = 0; col < 3; col++)
		if (board[0][col] != 0 && board[1][col] != 0 && board[2][col] != 0 &&
			(board[0][col] + board[1][col] + board[2][col]) == 15) {
			//cout << "COLUMN WIN!\n";
			return player;//board[0][col] % 2;
		}

	//Check diagonals for a win
	if (board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0 &&
		(board[0][0] + board[1][1] + board[2][2]) == 15) {
		//cout << "DIAGONAL WIN!\n";
		return player;//board[0][0] % 2;
	}

	if (board[2][0] != 0 && board[1][1] != 0 && board[0][2] != 0 &&
		(board[2][0] + board[1][1] + board[0][2]) == 15) {
		//cout << "r-DIAGONAL WIN!\n";
		return player;// board[2][0] % 2;
	}

	if (noOfMoves < 9)
		return CONTINUE;

	return DRAW;
}

void ticTacToe::reStart() {
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			board[row][col] = 0;

	for (int i = 0; i < 9; i++) moves[i] = { i + 1, false };

	noOfMoves = 0;
}

ticTacToe::ticTacToe() {
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			board[row][col] = 0;

	for (int i = 0; i < 9; i++) moves[i] = { i + 1, false };

	noOfMoves = 0;
}


