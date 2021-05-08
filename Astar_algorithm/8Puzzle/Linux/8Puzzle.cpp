#include <iostream>
#include <algorithm>
#include <time.h>
//#include <conio.h>
#include <string>

#include <queue>
#include <list>
#include <unordered_map>

using namespace std;

#define UP    72
#define LEFT  75
#define RIGHT 77
#define DOWN  80

class Puzzle;

#include "Board.h"
#include "Game.h"
//#include "Game-backup.h"


/*

test inputs: 
2 8 3 1 6 4 7 0 5
2 1 6 4 0 8 7 5 3
5 7 2 0 8 6 4 1 3
0 6 5 4 1 7 3 2 8
0 6 5 4 1 8 3 7 2
6 5 7 4 1 0 3 2 8
6 5 7 4 0 1 3 2 8
6 5 7 4 2 1 3 0 8
5 6 7 0 4 8 3 2 1
6 5 7 4 2 1 3 8 0
0 5 7 6 4 1 3 2 8
5 6 7 4 0 8 3 2 1
2 0 4 1 3 5 7 8 6
*/


int main()
{
    srand(time(NULL));
   
    /* 
    For batch testing mode:
        change while condition to number of test cases
        change A_Star parameter to 0
    */

    int n = 1;
    while (n <= /*13*/1) {
        Puzzle p;
        //p.play();
        cout << "Case "<< n << "# " << p.A_Star(1) << " moves\n\n";
        n++;
    }
    
    
    /*
    //Human player
    Puzzle P;
    P.play();*/

    return 0;
    
}

