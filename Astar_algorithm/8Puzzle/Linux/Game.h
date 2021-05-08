#pragma once

//typedef char Player;

class Puzzle {
	Board b;

	int goal[boardSize] = {1,2,3,8,0,4,7,6,5};

	int movesCount = 0;

	bool boardsMatch(int ar[], int arr[]) {
		for (int i = 0; i < boardSize; i++) {
			if (ar[i] != arr[i]) return false;
		}
		return true;
	}

	bool goalReached(State* s = NULL) {
		/*if(s == NULL)
			for (int i = 0; i < boardSize; i++) {
				if (goal[i] != b.b[i]) return false;
			}
		else 
			for (int i = 0; i < boardSize; i++) {
				if (goal[i] != s->brd[i]) return false;
			}
		return true;*/
		return boardsMatch(goal, (s == NULL) ? b.b : s->brd);
	}

	string generateMK(State s) const{
		string k = "";
		for (int x: s.brd) {
			k.push_back(x+48);
		}
		return k;
	}

public:

	Puzzle(/*char mode*/) : b('u') {
		//b.printBoard();
		cout << "Goal state:  1 2 3 8 0 4 7 6 5\n"
			<< "/* To enable dynamic goal state entering uncomment "
			<< "lines 47 - 50 on Game.h */\n\n";
		/*cout << "Enter goal state: ";
		for (int i = 0; i < boardSize; i++) {
			cin >> goal[i];
		}*/
	}
	/*
	//human player: uses arrow keys to move tiles in board.
	void play() {
		//_getch might only be supported in windows
		// if no support change getch to cin and use inputs as defined in 8Puzzle.cpp
		// or if manual playing is not needed comment out this entire function for easier fix
		while (!goalReached()) {
			b.printBoard();
			_getch();
			if (b.update(_getch())) movesCount++;
			system("CLS");
			b.printBoard();
			cout << "\n\nStep : " << movesCount << endl;
		}
	}
	*/
	void setHeuristics(State& s) {
		int temp = 0;
		
		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				if (s.brd[i] == goal[j]) {
					temp += abs(i/bSize - j/bSize) + abs(i%bSize - j%bSize);
					break;
				}
			}
		}
		

		s.h = temp;

		if (s.parent != NULL) s.g = s.parent->g + 1;
		else s.g = 1;

		s.f = s.g + s.h;
	}

	int A_Star(int print) {
		priority_queue <State> open;
		unordered_map<string, State> closed;

		
		State first = State(b.b);
		setHeuristics(first);
		first.g--;
		first.f--;
		first.parent = NULL;
		open.push(first);

		int states = 0;
		//int simulator = 0;

		//extra end condition
		bool end = false;
		string goalNode;

		if(print) cout << "Searching";

		//add neighbour moves:
		while (!open.empty()) {

			string k = generateMK(open.top());
			closed[k] = open.top();

			open.pop();

			list <State>  neighbours;
			Board temp = closed[k];

			//commented printing function for efficiency
			//cout <<"\t\t\t"<< states++ << "\n";
			states++;
			/*if (states++ % 5000 == 0) {
				++simulator;
				switch (simulator) {
				case 6:
					simulator = 0;
					cout << "\b\b\b\b\b\b\b\b\b\b";
					cout << "          ";
					cout << "\b\b\b\b\b\b\b\b\b\b";
					break;
				default:
					cout << " .";
				}
			}*/
			
			//add four neighbours
			neighbours.push_back(temp.nextMove(UP));
			neighbours.push_back(temp.nextMove(LEFT));
			neighbours.push_back(temp.nextMove(RIGHT));
			neighbours.push_back(temp.nextMove(DOWN));

			for (State& s : neighbours) {
				s.parent = &closed[k];
				setHeuristics(s);
				//cout << "Line 6\n";
				auto it = closed.find(generateMK(s));
				if (goalReached(&s)) {
					end = true; 
					goalNode = generateMK(s);
					closed[goalNode] = s;
					break;
				}
				else if (it == closed.end()) {
					open.push(s);
				}
				else if (it->second.f > s.f) {
					//cout << "Line 7\n";
					it->second.parent = s.parent;
					setHeuristics(it->second);
				}
			}
			if (end) break;
		}

		list <State> solution;
		State walker = closed[goalNode];

		while (walker.parent != NULL) {
			solution.push_front(walker);
			walker = *walker.parent;
		}

		if (print) cout << "\n\nStart: \n\n";
		if(print) b.printBoard();

		if (solution.size() == 0) {
			cout << "No solution for this starting position for goal: \n\n";
			Board(State(goal)).printBoard();
			return 0;
		}

		if (print) cout << "\n\nSolution: \n\n";
		for (Board s : solution) {
			if (print) {
				s.printBoard();
				cout << "\nMove: " << ++movesCount << " |-----------------------\n\n";
			}
			else {
				++movesCount;
			}
		}

		if (print) cout << "\n\nStates explored: " << states << endl;

		return movesCount;
	}
};
