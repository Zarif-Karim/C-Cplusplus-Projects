
initial configuration:

	+---+---+---+---+---+---+---+
	| B | B | B |   | W | W | W |
	+---+---+---+---+---+---+---+
pos:	  1   2   3   4   5   6   7
key: (arrow keys) <- || ->

Attempts to move block in 'pos' to an empty spot in the direction
provided by 'key'. Blocks can only jump over 2 other blocks at max.

Goal: move all 'W' blocks left of 'B' blocks with least cost

Astar run:
/*States Visited*/
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17

/* Solution */
+---+---+---+---+---+---+---+
| B | B | B |   | W | W | W |
+---+---+---+---+---+---+---+
Move: 0 Cost: 0

+---+---+---+---+---+---+---+
| B |   | B | B | W | W | W |
+---+---+---+---+---+---+---+
Move: 1 Cost: 1

+---+---+---+---+---+---+---+
| B | W | B | B |   | W | W |
+---+---+---+---+---+---+---+
Move: 2 Cost: 3

+---+---+---+---+---+---+---+
| B | W | B | B | W | W |   |
+---+---+---+---+---+---+---+
Move: 3 Cost: 4

+---+---+---+---+---+---+---+
| B | W | B |   | W | W | B |
+---+---+---+---+---+---+---+
Move: 4 Cost: 6

+---+---+---+---+---+---+---+
|   | W | B | B | W | W | B |
+---+---+---+---+---+---+---+
Move: 5 Cost: 8

+---+---+---+---+---+---+---+
| W |   | B | B | W | W | B |
+---+---+---+---+---+---+---+
Move: 6 Cost: 9

+---+---+---+---+---+---+---+
| W | W | B | B |   | W | B |
+---+---+---+---+---+---+---+
Move: 7 Cost: 11

+---+---+---+---+---+---+---+
| W | W |   | B | B | W | B |
+---+---+---+---+---+---+---+
Move: 8 Cost: 12

+---+---+---+---+---+---+---+
| W | W | W | B | B |   | B |
+---+---+---+---+---+---+---+
Move: 9 Cost: 14

Player run example:
