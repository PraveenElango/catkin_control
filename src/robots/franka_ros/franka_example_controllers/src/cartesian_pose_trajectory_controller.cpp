// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#include <franka_example_controllers/cartesian_pose_trajectory_controller.h>

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

#include <controller_interface/controller_base.h>
#include <franka_hw/franka_cartesian_command_interface.h>
#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>

namespace franka_example_controllers {

bool CartesianPoseTrajectoryController::init(hardware_interface::RobotHW* robot_hardware,
                                          ros::NodeHandle& node_handle) {
  cartesian_pose_interface_ = robot_hardware->get<franka_hw::FrankaPoseCartesianInterface>();
  if (cartesian_pose_interface_ == nullptr) {
    ROS_ERROR(
        "CartesianPoseExampleController: Could not get Cartesian Pose "
        "interface from hardware");
    return false;
  }

  std::string arm_id;
  if (!node_handle.getParam("arm_id", arm_id)) {
    ROS_ERROR("CartesianPoseExampleController: Could not get parameter arm_id");
    return false;
  }

  try {
    cartesian_pose_handle_ = std::make_unique<franka_hw::FrankaCartesianPoseHandle>(
        cartesian_pose_interface_->getHandle(arm_id + "_robot"));
  } catch (const hardware_interface::HardwareInterfaceException& e) {
    ROS_ERROR_STREAM(
        "CartesianPoseExampleController: Exception getting Cartesian handle: " << e.what());
    return false;
  }

  auto state_interface = robot_hardware->get<franka_hw::FrankaStateInterface>();
  if (state_interface == nullptr) {
    ROS_ERROR("CartesianPoseExampleController: Could not get state interface from hardware");
    return false;
  }

  try {
    auto state_handle = state_interface->getHandle(arm_id + "_robot");

    std::array<double, 7> q_start{{0, -M_PI_4, 0, -3 * M_PI_4, 0, M_PI_2, M_PI_4}};
    for (size_t i = 0; i < q_start.size(); i++) {
      if (std::abs(state_handle.getRobotState().q_d[i] - q_start[i]) > 0.1) {
        ROS_ERROR_STREAM(
            "CartesianPoseExampleController: Robot is not in the expected starting position for "
            "running this example. Run `roslaunch franka_example_controllers move_to_start.launch "
            "robot_ip:=<robot-ip> load_gripper:=<has-attached-gripper>` first.");
        return false;
      }
    }
  } catch (const hardware_interface::HardwareInterfaceException& e) {
    ROS_ERROR_STREAM(
        "CartesianPoseExampleController: Exception getting state handle: " << e.what());
    return false;
  }

  pose_command_subscriber = node_handle.subscribe("cartesian_pose",
                                                       10,
                                                       &CartesianPoseTrajectoryController::cartesian_pose_callback,
                                                       this);

  return true;
}



void CartesianPoseTrajectoryController::starting(const ros::Time& /* time */) {
  initial_pose_ = cartesian_pose_handle_->getRobotState().O_T_EE_d;
  elapsed_time_ = ros::Duration(0.0);
  count2 = 0;
}

void CartesianPoseTrajectoryController::cartesian_pose_callback(const geometry_msgs::Twist::ConstPtr& msg) {
  // Callback for ROS message
  pos_command[0] = msg->linear.x;
  pos_command[1] = msg->linear.y;
  pos_command[2] = msg->linear.z;
  //pos_command[3] = msg->angular.x;
  //pos_command[4] = msg->angular.y;
  //pos_command[5] = msg->angular.z;
  //pos_command = msg -> traj;
  time_since_last_command = ros::Duration(0.0);
}


void CartesianPoseTrajectoryController::update(const ros::Time& /* time */,
                                            const ros::Duration& period) {
  // elapsed_time_ += period;
  //std::cout << elapsed_time_ << "\n";
  //std::cout << "\n";
  //std::cout << "this is it" << pos_command[0];
  //std::cout << "\n";
  // double radius = 0.3;
  // count = count + 1;
  //std::cout << count << "its\n";

  //std::cout << pos_command[0] << "ah\n";
  //double angle = M_PI / 4 * (1 - std::cos(M_PI / 5.0 * elapsed_time_.toSec()));
  //double angle = pos_command[0];

  //std::cout << angle << "\n";
  //double delta_x = radius * std::sin(angle);
  //double delta_z = radius * (std::cos(angle) - 1);
  // std::array<double, 16> new_pose = initial_pose_;
  // new_pose[12] += 0.001 * elapsed_time_.toSec();
  //new_pose[14] -= delta_z;
  // cartesian_pose_handle_->setCommand(new_pose);

  elapsed_time_ += period;

  double radius = 0.3;
  double angle = M_PI / 4 * (1 - std::cos(M_PI / 5.0 * elapsed_time_.toSec()));
  double delta_x = radius * std::sin(angle);
  double delta_z = radius * (std::cos(angle) - 1);
  //std::cout << elapsed_time_ << "\n";
  std::array<double, 16> new_pose = initial_pose_;
  if (angle < 1.57 && count2 == 0){
    count = 10000 * std::sin(angle);
    if (angle > 1.55){
      count2 = 1;
    }
  }
  std::cout << count << "\n";
  std::cout << count2 << "\n";
  new_pose[12] += 0.00001 * elapsed_time_.toSec() * count;
  //new_pose[14] -= delta_z;
  cartesian_pose_handle_->setCommand(new_pose);

}

}  // namespace franka_example_controllers

PLUGINLIB_EXPORT_CLASS(franka_example_controllers::CartesianPoseTrajectoryController,
                       controller_interface::ControllerBase)
