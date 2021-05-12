#include <ros/ros.h>
#include <move_arm_joints/move_and_confirm.h>
#include <mover_client/grid_num_vector.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <sstream>

using namespace std;

#include <param100.h>

//from subscribed topic
void fst(const mover_client::grid_num_vector& msgs)
{
	ROS_INFO_STREAM("\nRecieved Vector Size: " << msgs.numbered_grids.size() << endl);
	
	//load parameters from file to map
	unordered_map<string, string> params;
	loadParams(params);
	unordered_map<string, string>::iterator it;
	
	string key;
	string value;

	ros::NodeHandle nhfst;

	ros::ServiceClient sp = nhfst.serviceClient<move_arm_joints::move_and_confirm>("arm_shoulder_pan_joint_service");
	ros::ServiceClient ef = nhfst.serviceClient<move_arm_joints::move_and_confirm>("arm_elbow_flex_joint_service");
	ros::ServiceClient wf = nhfst.serviceClient<move_arm_joints::move_and_confirm>("arm_wrist_flex_joint_service");
	ros::ServiceClient sl = nhfst.serviceClient<move_arm_joints::move_and_confirm>("arm_shoulder_lift_joint_service");
	ros::ServiceClient g =  nhfst.serviceClient<move_arm_joints::move_and_confirm>("gripper_joint_service");

	//for all the values in the messages vector
	for (int i = 0; i < msgs.numbered_grids.size(); i++)
	{
		move_arm_joints::move_and_confirm::Request req;
		move_arm_joints::move_and_confirm::Response resp;
		
		key = to_string(msgs.numbered_grids[i].row) + "," + to_string(msgs.numbered_grids[i].col) + "," + to_string(msgs.numbered_grids[i].num);
		ROS_INFO_STREAM(i+1 << ") MOVING : " << key);
		it = params.find(key);
		if (it == params.end())
		{
			//error
			ROS_INFO_STREAM("Failed to retrieve values!");
			return;
		}

		stringstream ss(it->second);	//all values for the 5 prefixes comma separated


		//for arm_shoulder_pan
		getline(ss, value, ',');	//get arm_shoulder_pan value
		req.move = stod(value);		//set value to request variable
		if (sp.call(req, resp))		//call service for asp
		{
			//ROS_INFO_STREAM("Made call : SP\n");
			while (req.move != resp.confirm)  //Keep calling until successful
			{
				if (!sp.call(req, resp))
				{
					//error
					ROS_INFO_STREAM("Failed to make call : SP\n");
					return;
				}
			}
		} 
		else
		{
			//error
			ROS_INFO_STREAM("Failed to make call : SP\n");
			return;
		}

		
		//for arm_elbow_flex
		getline(ss, value, ',');	//get arm_shoulder_pan value
		req.move = stod(value);		//set value to request variable
		if (ef.call(req, resp))		//call service for asp
		{
			//ROS_INFO_STREAM("Made call : EF\n");
			while (req.move != resp.confirm)  //Keep calling until successful
			{
				if (!ef.call(req, resp))
				{
					//error
					ROS_INFO_STREAM("Failed to make call : SP\n");
					return;
				}
			}
		}
		else
		{
			//error
			//ROS_INFO_STREAM("Failed to make call : EF\n");
			return;
		}


		//for arm_wrist_flex
		getline(ss, value, ',');	//get arm_shoulder_pan value
		req.move = stod(value);		//set value to request variable
		if (wf.call(req, resp))		//call service for asp
		{
			//ROS_INFO_STREAM("Made call : WF\n");
			while (req.move != resp.confirm)  //Keep calling until successful
			{
				if (!wf.call(req, resp))
				{
					//error
					ROS_INFO_STREAM("Failed to make call : SP\n");
					return;
				}
			}
		}
		else
		{
			//error
			//ROS_INFO_STREAM("Failed to make call : WF\n");
			return;
		}


		//for arm_shoulder_lift
		getline(ss, value, ',');	//get arm_shoulder_pan value
		req.move = stod(value);		//set value to request variable
		if (sl.call(req, resp))		//call service for asp
		{
			//ROS_INFO_STREAM("Made call : SL\n");
			while (req.move != resp.confirm)  //Keep calling until successful
			{
				if (!sl.call(req, resp))
				{
					//error
					ROS_INFO_STREAM("Failed to make call : SP\n");
					return;
				}
			}
		}
		else
		{
			//error
			ROS_INFO_STREAM("Failed to make call : SL\n");
			return;
		}


		//for gripper
		getline(ss, value);		//get arm_shoulder_pan value
		req.move = stod(value);		//set value to request variable
		if (g.call(req, resp))		//call service for asp
		{
			//ROS_INFO_STREAM("Made call : G\n");
			while (req.move != resp.confirm)  //Keep calling until successful
			{
				if (!g.call(req, resp))
				{
					//error
					ROS_INFO_STREAM("Failed to make call : SP\n");
					return;
				}
			}
		}
		else
		{
			//error
			ROS_INFO_STREAM("Failed to make call : G\n");
			return;
		}

		ROS_INFO_STREAM(i+1 << ") MOVING : " << key << " : DONE\n");
	}

}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "mover_client");
	ros::NodeHandle nh;
	
	ros::Subscriber sub = nh.subscribe("num_grids_sol/vector", 1000, &fst);

	ros::spin(); // from subscriber file
	/*
	while(ros::ok())
	{ 

		req.triple_vect.clear();

		for( int i = 0; i < 10; i++ ) //give the server some random 10 triple of nubmers to add
		{
	    		triple.A = rand()%10; //some random numbers between 1 and 10
			triple.B = rand()%10;
			triple.C = rand()%10;
			req.triple_vect.push_back(triple);            
		}		

		bool success = myClient.call(req, resp);

		if(success)
		{

			for( int i = 0; i < resp.sum_vect.size(); i++ )
			{
				 //resp.sum_vect.push_back(req.triple_vect[i].A + req.triple_vect[i].B + req.triple_vect[i].C);
				 ROS_INFO_STREAM("Server says sum of triples: " << resp.sum_vect[i]);

				if( i+1 != resp.sum_vect.size() )
				 	ROS_INFO_STREAM(", ");
			}           			            
		}
		else
		{
			ROS_INFO_STREAM("Failed to contact service. ");
		}
	}
	*/
}
