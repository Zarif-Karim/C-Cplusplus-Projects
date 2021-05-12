#include <ros/ros.h>
#include <sudoku_pub/grid_num.h>
#include <sudoku_pub/grid_num_vector.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

const int GRID_SIZE = 16;

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "sudokuPublisher");
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<sudoku_pub::grid_num_vector>("num_grids/vector", 1000);

	sudoku_pub::grid_num_vector solMsgs;


	int grid[GRID_SIZE][GRID_SIZE] = {
		{ 6, 10,  0, 12,  9, 16,  0,  5,  0,  0,  2,  0, 14,  8,  0, 11},
		{ 1,  7,  0, 11, 10, 14,  4,  0,  5,  0,  0,  8,  2,  0, 13, 15},
		{ 9,  0,  4,  2,  0,  8,  0,  0, 16, 13,  0,  0, 12,  6,  0, 10},
		{ 0, 14,  8, 13,  0, 15,  0, 12,  0,  0,  1,  0,  0,  3,  4,  0},
		{15,  0,  0,  0,  0,  1, 12,  0,  8,  0,  0,  0,  0,  0,  7, 14},
		{ 3, 11,  0,  5, 13,  9,  0,  0,  0,  0,  0, 15,  1,  2,  0,  0},
		{ 4,  0,  0, 16,  6, 11,  5,  3,  0,  2, 14,  0,  0, 10,  0, 13},
		{12,  0,  0,  0, 15, 10,  0, 16,  9,  7,  0, 11,  6,  0,  3,  0},
		{ 0,  0,  0,  0, 14,  0,  9,  0, 11,  8,  0, 12,  0,  0,  0,  0},
		{ 0,  9, 14,  0,  0,  0,  6,  2,  4,  0,  0,  0,  0,  0, 16,  7},
		{10,  0,  0,  6,  7,  3,  0,  0,  0,  0,  0,  0,  0, 11, 12,  1},
		{ 0, 16,  0,  0,  4, 13, 10, 11,  0,  1,  6,  0,  5,  0,  9,  8},
		{ 0,  0, 11,  3,  5,  0,  0,  1,  2,  4,  8,  0, 13,  0,  0,  9},
		{ 8, 12,  5,  0,  0,  0,  0,  0,  0,  9,  0,  0,  0,  0,  0,  4},
		{ 0,  2,  0,  7,  0,  4, 14,  0,  0, 11, 15, 16,  8,  0,  0,  3},
		{14,  0,  0,  9,  8,  0,  0, 10,  0,  0,  0,  5,  0,  1,  0,  2}
	};

	/*int grid[GRID_SIZE][GRID_SIZE = {
		{0,0,0,4,1,0,0,0,0},
		{0,0,8,9,2,0,0,0,0},
		{0,0,9,7,3,0,0,0,0},
		{0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,2,0,0,0,0,0},
		{0,0,0,6,4,0,0,0,0},
		{0,0,0,5,0,0,0,0,0},
		{0,0,0,8,0,0,0,0,0}
	};*/


	for(int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (grid[i][j] > 0)
			{
				sudoku_pub::grid_num g;
				g.row = i + 1;
				g.col = j + 1;
				g.num = grid[i][j];

				//save to grid_num_vector
				solMsgs.numbered_grids.push_back(g);
				//ROS_INFO_STREAM("MES: " << solMsgs.numbered_grids[i]);
			}
		}
	}
	
	//if(ros::ok()) pub.publish(solMsgs);
	//std::string publish;
	/*ros::Rate rate(1);*/
	while (ros::ok())
	{
		int publish;
		//publish
		std::cout << "Enter 1 to publish message: ";
		std::cin >> publish;
		if(publish == 1)
		{
			pub.publish(solMsgs);
			ROS_INFO_STREAM(" STARTING SUDOKU PUZZLE PUBLISHED" << "\n\n");
			break;
			/*rate.sleep();*/
		}
	}

	if (ros::ok()) ros::shutdown();
	
	return 0;
}
