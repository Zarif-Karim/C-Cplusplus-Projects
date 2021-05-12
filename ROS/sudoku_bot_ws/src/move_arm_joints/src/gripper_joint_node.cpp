#include <ros/ros.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <lastlinereader.h>
#include <move_arm_joints/move_and_confirm.h>

bool mnc(move_arm_joints::move_and_confirm::Request &req,
                        move_arm_joints::move_and_confirm::Response &resp)
{	
	try
	{
		char call[50];
		sprintf(call, "./gripper_servo %lf", req.move);
		system(call);
		
		resp.confirm = std::stod(lastLineOfFile("gripper_servo_confirm.log"));
		ROS_INFO_STREAM("GRIPPER : " << req.move << " ---> " << resp.confirm);
		return true;
	}
	catch (...)
	{
		ROS_INFO_STREAM("GRIPPER : " << req.move << " FAILED!");
		return false;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "gripper_joint_node");
	ros::NodeHandle nh;
	ros::ServiceServer myServer = nh.advertiseService("gripper_joint_service", &mnc);

    ros::spin();

    return 0;

}
