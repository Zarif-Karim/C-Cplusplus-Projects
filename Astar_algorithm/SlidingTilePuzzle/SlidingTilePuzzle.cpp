#include <iostream>
#include <conio.h>
#include <list>
#include <queue>
#include <unordered_map>
#include <assert.h>
#include <ctime>

#define LEFT 75
#define RIGHT 77

using namespace std;

class STP;

#include "Board.h"

int main()
{
    srand(time(0));

    Board STP;

    int m, p, choice;
    
    choice = -1;
    while (choice) {
            cout << "Current Board: \n";
            STP.print();
            cout << endl;
            cout <<
                    "1: Randomize Board\n"
                    "2: Astar Solve\n"
                    "3: Play Manual\n"
                    "4: Exit\n"
                    "\nSelection: ";

            cin >> choice;
            switch (choice) {
            case 1:
                    STP.boardRandomize();
                    break;
            case 2:
                    STP.solve_Astar();
                    break;
            case 3:
                    while (!STP.goalSelf()) {
                            STP.print();
                            cout << "Total Cost: " << STP.getCost() << endl << endl;
                            cout << "Moving (";
                            p = _getch() - 49;
                            cout << p + 1 << ", ";
                            m = _getch();
                            m = _getch();

                            if (m == 75) cout << "left";
                            else if (m == 77) cout << "right";
                            cout << ")\n";

                            if (!STP.move(m, p)) cout << "\n\nInvalid Move!!!\n\n\n";
                    }
                    break;
            case 4: 
                    choice = 0;
                    cout << "\n\nExiting...\n\n";
                    break;
            default:
                    cout << "\n\nInvalid choice! Enter again\n\n";
            }
    }

    return 0;
}
