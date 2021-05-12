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
		sprintf(call, "./arm_shoulder_lift_servo %lf", req.move);
		system(call);
		
		resp.confirm = std::stod(lastLineOfFile("arm_shoulder_lift_servo_confirm.log"));
		ROS_INFO_STREAM("ARM_SHOULDER_LIFT : " << req.move << " ---> " << resp.confirm);
		return true;
	}
	catch (...)
	{
		ROS_INFO_STREAM("ARM_SHOULDER_LIFT : " << req.move << " FAILED!");
		return false;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "arm_shoulder_lift_joint_node");
	ros::NodeHandle nh;
	ros::ServiceServer myServer = nh.advertiseService("arm_shoulder_lift_joint_service", &mnc);

    ros::spin();

    return 0;

}
