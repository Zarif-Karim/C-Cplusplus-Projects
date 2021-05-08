#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

const int vertices = 20;

struct city {
    string name;
    city* parent = NULL;
    int pathCost = INT_MAX;
};

//map names to numbers and vice versa

//string to int
unordered_map<string, int> romania;

//integer to string
unordered_map<int, city> romaniaItoS;

//set map names to numbers and vice versa 
void setVertices() {
    romania["Oradea"] = 0;
    romania["Zerind"] = 1;
    romania["Arad"] = 2;
    romania["Sibiu"] = 3;
    romania["Timisoara"] = 4;
    romania["Fagaras"] = 5;
    romania["Rimnicu Vilcea"] = 6;
    romania["Lugoj"] = 7;
    romania["Pitesti"] = 8;
    romania["Mehadia"] = 9;
    romania["Dobreta"] = 10;
    romania["Craiova"] = 11;
    romania["Bucharest"] = 12;
    romania["Giurgiu"] = 13;
    romania["Urziceni"] = 14;
    romania["Hirsova"] = 15;
    romania["Eforie"] = 16;
    romania["Vaslui"] = 17;
    romania["Iasi"] = 18;
    romania["Neamt"] = 19;
    
    romaniaItoS[0].name = "Oradea";
    romaniaItoS[1].name = "Zerind";
    romaniaItoS[2].name = "Arad";
    romaniaItoS[3].name = "Sibiu";
    romaniaItoS[4].name = "Timisoara";
    romaniaItoS[5].name = "Fagaras";
    romaniaItoS[6].name = "Rimnicu Vilcea";
    romaniaItoS[7].name = "Lugoj";
    romaniaItoS[8].name = "Pitesti";
    romaniaItoS[9].name = "Mehadia";
    romaniaItoS[10].name = "Dobreta";
    romaniaItoS[11].name = "Craiova";
    romaniaItoS[12].name = "Bucharest";
    romaniaItoS[13].name = "Giurgiu";
    romaniaItoS[14].name = "Urziceni";
    romaniaItoS[15].name = "Hirsova";
    romaniaItoS[16].name = "Eforie";
    romaniaItoS[17].name = "Vaslui";
    romaniaItoS[18].name = "Iasi";
    romaniaItoS[19].name = "Neamt";
}

//reset to initial state
void resetPP() {
    for (auto& x : romaniaItoS) {
        x.second.parent = NULL;
        x.second.pathCost = INT_MAX;
    }
}

/*
Graph class

create 2D vector of int with rows and columns of size 'vert'(number of vertices)
initial value of the matrix is INT_MAX for all positions/connections
*/
class Graph {
public:
    vector<vector<int>> graph; // made public for simplicity

    Graph(int vert): 
        graph(vert)
    {
        for (vector<int>& x : graph) x.assign(vert, INT_MAX);
    }

    void addEdge(string src, int weight, string dest){

        if (romania.find(src) == romania.end()) {
            cout << src << ": NOT FOUND!\n";
            cout << "Reenter src: ";
            cin >> src;
        }
        if (romania.find(dest) == romania.end()) {
            cout << dest << ": NOT FOUND!\n";
            cout << "Reenter dest: ";
            cin >> dest;
        }

        //un-directed graph
        graph[romania[src]][romania[dest]] = weight;
        graph[romania[dest]][romania[src]] = weight;
    }
};

//graph of romania
Graph r(vertices);
void setEdges() {
    r.addEdge("Oradea", 71, "Zerind");
    r.addEdge("Oradea", 151, "Sibiu");
    r.addEdge("Arad", 75, "Zerind");
    r.addEdge("Arad", 140, "Sibiu");
    r.addEdge("Arad", 118, "Timisoara");
    r.addEdge("Lugoj", 111, "Timisoara");
    r.addEdge("Lugoj", 70, "Mehadia");
    r.addEdge("Dobreta", 75, "Mehadia");
    r.addEdge("Dobreta", 120, "Craiova");
    r.addEdge("Rimnicu Vilcea", 80, "Sibiu");
    r.addEdge("Rimnicu Vilcea", 146, "Craiova");
    r.addEdge("Rimnicu Vilcea", 97, "Pitesti");
    r.addEdge("Craiova", 138, "Pitesti");
    r.addEdge("Bucharest", 101, "Pitesti");
    r.addEdge("Bucharest", 90, "Giurgiu");
    r.addEdge("Bucharest", 85, "Urziceni");
    r.addEdge("Bucharest", 211, "Fagaras");
    r.addEdge("Sibiu", 99, "Fagaras");
    r.addEdge("Hirsova", 98, "Urziceni");
    r.addEdge("Hirsova", 86, "Eforie");
    r.addEdge("Vaslui", 142, "Urziceni");
    r.addEdge("Vaslui", 92, "Iasi");
    r.addEdge("Neamt", 87, "Iasi");
}

//Algorithm to find shortest path through breath first search
void findShortestPath(string src, string dest) {
    //find shortest path using breath-first traversal
    list<int> open;

    //set pathcost to zero for starting node
    romaniaItoS[romania[src]].pathCost = 0;

    open.push_back(romania[src]);
    for (auto it = open.begin(); it != open.end(); it++) {
        cout << romaniaItoS[*it].name << " -> "; // printing out bfs order

        for (int i = 0; i < vertices; i++) {
            if (r.graph[*it][i] != INT_MAX) /*if there is a path from current node*/
            {
                if (find(open.begin(), open.end(), i) == open.end()) /*if node not already in list*/
                {
                    //set parent    
                    romaniaItoS[i].parent = &romaniaItoS[*it];
                    //set cumulative path cost
                    romaniaItoS[i].pathCost = r.graph[*it][i] + romaniaItoS[*it].pathCost;
                    //add to search list
                    open.push_back(i);
                }
                else  /*if node already in list*/
                {
                    /*if this pathcost less than saved pathcost*/
                    if (r.graph[*it][i] + romaniaItoS[*it].pathCost < romaniaItoS[i].pathCost) 
                    {
                        //update parent and pathcost
                        romaniaItoS[i].parent = &romaniaItoS[*it];
                        romaniaItoS[i].pathCost = r.graph[*it][i] + romaniaItoS[*it].pathCost;
                    }
                }
            }
        }
    }

    //print out solution:
    list<string> solution;
    city walker = romaniaItoS[romania[dest]];

    int recalPathCost = 0;

    //get solution by walking from dest to src
    while (walker.parent != NULL) {
        solution.push_front(walker.name);
        recalPathCost += r.graph[romania[walker.name]][romania[walker.parent->name]];
        walker = *walker.parent;
    } 
    solution.push_front(walker.name);

    //print solution from src to dest
    cout << "\n\nShortest Path: \n";
    for (auto it = solution.begin(); it != solution.end(); it++) {
        if (it != solution.begin()) {
                                //path cost
            cout << " -(" << r.graph[romania[*it]][romania[romaniaItoS[romania[*it]].parent->name]] << ")-> ";
        }
        //name
        cout << *it;
    }
    cout << "." << endl;

    cout << "\nPath Cost : " << recalPathCost << "\n";
}

int main()
{
        //setting up graph
    setVertices();
    setEdges();
    
    int x = 1;
    string src, dest;
    while (x) {
        cout << "From: ";
        cin >> src;
        cout << "To: ";
        cin >> dest;
        findShortestPath(src, dest);
        cout << "\n\n Find new path? (1/0): ";
        cin >> x;
        if (x) resetPP();
    }
    
    return 0;
}

