#!/bin/bash

source devel/setup.bash
roslaunch move_arm_joints mrj_launch.launch &
rosrun mover_client mover_client_exec &
rosrun interface interface_exec &
sleep 4
rosrun sudoku_pub sudoku_pub_exec
