#pragma once

const int bSize = 7;

class Board;

class State {
public:
	char b[7] = { 'B','B', 'B', ' ','W','W','W' };
	int cost = 0;
	float f = FLT_MAX, g = FLT_MAX, h = FLT_MAX;

	State* parent = NULL;

	State() { };
};

bool operator < (const State& obj, const State& obj2) {
	return (obj.f < obj2.f); 
}

class Board: public State {
	
	
	string generateMK(State s) {
		string k = "";
		for (char x : s.b) {
			k.push_back(x);
		}
		return k;
	}
	
	void setHeuristics(State& br) {
		/*float count = 0;

		for (int i = 0; i < 4; i++) {
			if (br.b[i] == 'W') count += 3;
			else if (br.b[i] == ' ') ;
			else count -= 1;
		}

		br.h = count;*/
		
		int w = 3, hn;

		for (int i = 0; i < bSize; i++) {
			if (br.b[i] == 'B') break;
			if (br.b[i] == 'W') --w;
		}
		hn = w;

		w = 3;
		int  h_n = 0;
		for (int i = 0; i < bSize && w > 0; i++) {
			if (br.b[i] == 'B') h_n += w;
			if (br.b[i] == 'W') --w;
		}

		br.h = -(hn + h_n);

		if (br.parent != NULL) br.g = br.parent->g + 1;
		else br.g = 0;

		br.f = br.h - (br.g/* + br.cost*/);



	}

	list<Board> children() {
		list<Board> c;

		int pos = 0;
		while (b[pos] != ' ') ++pos;
		for (int i = 1; i <= 3; ++i) {
			if (pos - i >= 0) {
				Board tmp = *this;
				tmp.move(RIGHT, pos - i);
				c.push_back(tmp);
			}
			if (pos + i < 7) {
				Board tmp = *this;
				tmp.move(LEFT, pos + i);
				c.push_back(tmp);
			}
		}

		return c;

	}

public:
	Board() {};
	Board(const State& obj) {
		for (int i = 0; i < bSize; i++) {
			this->b[i] = obj.b[i];
		}
		this->cost = obj.cost;

		this->f = obj.f;
		this->g = obj.g;
		this->h = obj.h;

		this->parent = obj.parent;
	}
	Board(const Board& obj) {
		for (int i = 0; i < bSize; i++) {
			this->b[i] = obj.b[i];
		}
		this->cost = obj.cost;

		this->f = obj.f;
		this->g = obj.g;
		this->h = obj.h;

		this->parent = obj.parent;
	}
	
	void print() {
		/*int r = 0;
		for (char c : b) {
			cout << "  "<< ++r <<" ";
		}*/
		cout << endl;
		for(char c: b) cout << "+---";
		cout << "+" << endl;
		for (int i = 0; i < bSize; i++) {
			cout << "| " << b[i] << " ";
		}
		cout << "|" << endl;
		for(char c: b) cout << "+---";
		cout << "+" << endl;
	}
	bool move(int key, int pos) {
		if (key == LEFT) key = -1;
		if (key == RIGHT) key = +1;

		char tmp = b[pos];
		int i;
		int cC = 0;

		for(i = 1;	
					(b[pos + key*i] != ' ') && 
					i < 3 && 
					(pos + key*i < bSize - 1 && pos + key*i > 0);
			i++) 
		{
			++cC;
		}
		if (i == 1) ++cC;
		if (b[pos + key * i] == ' ') {
			b[pos + key * i] = tmp;
			b[pos] = ' ';
			cost += cC;
			return true;
		}
		else return false;
	}
	bool goal(State& s) {
		int count = 0;

		for (char& c : s.b)
			if (c == 'W') ++count;
			else if (c == ' ') continue;
			else break;

		if (count == 3) return true;
		else return false;
	}
	bool goalSelf() {
		int count = 0;

		for (char& c : b)
			if (c == 'W') ++count;
			else if (c == ' ') continue;
			else break;

		if (count == 3) return true;
		else return false;
	}
	void boardRandomize() {
		for (int i = 0; i < 7; i++) {
			swap(b[i], b[rand() % 7]);
		}
	}
	int getCost() { return cost; }


	void solve_Astar() {
		//necessary containers
		priority_queue<State> open;
		unordered_map<string, State> closed;


		//open list initialization
		setHeuristics(*this);
		open.push(*this);

		//extras
		int states = 0;
		bool end = false;
		string goalNode;

		//search solution
		while (!open.empty() && states++ < 50000) {
			cout << states << "\n";
			string k = generateMK(open.top());
			closed[k] = open.top();
			open.pop();

			//add children
			Board tmpM = closed[k];

			for (State& s :	tmpM.children()) {
				s.parent = &closed[k];
				setHeuristics(s);

				auto it = closed.find(generateMK(s));
				if (goal(s)) {
					end = true;
					goalNode = generateMK(s);
					closed[goalNode] = s;
					break;
				}
				else if (it == closed.end()) {
					open.push(s);
				}
				else if (it->second.g > s.g) {
					assert(it->second.parent == NULL);

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
		solution.push_front(walker);

		int movesCount = 0;
		for (Board s : solution) {
			s.print();
			cout << "Move: " << movesCount++ << " Cost: " << s.cost << "\n";
		}
		system("PAUSE");
	}

};
