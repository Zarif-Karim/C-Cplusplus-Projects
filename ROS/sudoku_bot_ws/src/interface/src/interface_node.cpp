#include <ros/ros.h>
#include <mover_client/grid_num.h>
#include <mover_client/grid_num_vector.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

mover_client::grid_num_vector solMsgs;
bool publish = false;

void gridGenerator(const mover_client::grid_num_vector& msgs)
{
	ROS_INFO_STREAM("------ INTERFACE : INVOKED ------");
	//encode as ASP facts
	ofstream fout("my_sudoku_facts.lp", ios::trunc); //open new file
	for (int i = 0; i < msgs.numbered_grids.size(); i++)
	{
		string fact = "gridNum(" + to_string(msgs.numbered_grids[i].row) + "," + to_string(msgs.numbered_grids[i].col) + "," + to_string(msgs.numbered_grids[i].num) + ").";
		fout << fact << endl;
	}
	fout.close();

	//call ASP solver
	system("clingo my_sudoku_facts.lp my_sudoku_ASP_program_16.lp > result.txt"); //outputs gridNumSol(row,col,num). ...

	//read from result.txt, parse and store
	ifstream fin("result.txt");
	if (!fin.is_open())
	{
		ROS_INFO_STREAM("INTERFACE : Could not open result.txt");
	}
	else 
	{
		ROS_INFO_STREAM("INTERFACE : " << "Generating solution");
		string sol;
		int until = 5;
		while (until--) getline(fin, sol);
		fin.close();
		
		stringstream ss(sol);

		mover_client::grid_num g;
		solMsgs.numbered_grids.clear();
		while (ss >> sol)
		{
			int prePos, postPos;

			//row
			prePos = sol.find('(') + 1;
			postPos = sol.find(',');
			g.row = stoi(sol.substr(prePos, postPos - prePos));

			//col
			prePos = postPos + 1;
			postPos = sol.find(',', prePos);
			g.col = stoi(sol.substr(prePos, postPos - prePos));

			//num
			prePos = postPos + 1;
			postPos = sol.find(')');
			g.num = stoi(sol.substr(prePos, postPos - prePos));
			
			//save to grid_num_vector
			solMsgs.numbered_grids.push_back(g);
		}
		ROS_INFO_STREAM("INTERFACE : " << "Solution generated\n");
		publish = true;
	}
	
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "interface_node");
	ros::NodeHandle nh;
	
	ros::Subscriber sub = nh.subscribe("num_grids/vector", 1000, &gridGenerator);
	ros::Publisher pub = nh.advertise<mover_client::grid_num_vector>("num_grids_sol/vector", 1000);

	while (ros::ok())
	{
		ros::spinOnce();
		if (publish)
		{
			pub.publish(solMsgs);
			publish = false;
		}
	}
}