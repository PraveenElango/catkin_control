// Copyright (c) 2017 Franka Emika GmbH
// Use of this source code is governed by the Apache-2.0 license, see LICENSE
#include <franka_example_controllers/cartesian_waypoints.h>

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

#include <controller_interface/controller_base.h>
#include <franka_hw/franka_cartesian_command_interface.h>
#include <hardware_interface/hardware_interface.h>
#include <pluginlib/class_list_macros.h>
#include <ros/ros.h>

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

namespace franka_example_controllers {

bool CartesianWaypointController::init(hardware_interface::RobotHW* robot_hardware,
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

  return true;
}

void CartesianWaypointController::starting(const ros::Time& /* time */) {
  initial_pose_ = cartesian_pose_handle_->getRobotState().O_T_EE_d;
  elapsed_time_ = ros::Duration(0.0);
}

void CartesianWaypointController::update(const ros::Time& /* time */, const ros::Duration& period) {
  elapsed_time_ += period;

  static const std::string PLANNING_GROUP = "panda_arm";

  ROS_INFO("Planning group set to panda arm");

  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  ROS_INFO("MoveGroupInterface declared");

  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

  ROS_INFO("PlanningSceneInterface declared");

  const robot_state::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  ROS_INFO("Planning frame: %s", move_group.getPlanningFrame().c_str());

  ROS_INFO("End effector link: %s", move_group.getEndEffectorLink().c_str());

  ROS_INFO("Available Planning Groups:");

  std::copy(move_group.getJointModelGroupNames().begin(),
            move_group.getJointModelGroupNames().end(),
            std::ostream_iterator<std::string>(std::cout, ", "));


  std::array<double, 16> new_pose = initial_pose_;
  double current_x = new_pose[12];
  double current_y = new_pose[13];
  double current_z = new_pose[14];

  ROS_INFO("Cartesian x is %lf", current_x);
  ROS_INFO("Cartesian y is %lf", current_y);
  ROS_INFO("Cartesian z is %lf", current_z);

  geometry_msgs::Pose target_pose1;
  target_pose1.orientation.w = 1.0;
  target_pose1.position.x = current_x+0.05;
  target_pose1.position.y = current_y;
  target_pose1.position.z = current_z;

  ROS_INFO("Pose 1 Cartesian x is %lf", target_pose1.position.x);

  robot_state::RobotState start_state(*move_group.getCurrentState());
  geometry_msgs::Pose start_pose2;
  start_pose2.orientation.w = 1.0;
  start_pose2.position.x = current_x+0.05;
  start_pose2.position.y = current_y;
  start_pose2.position.z = current_z;
  start_state.setFromIK(joint_model_group, start_pose2);
  move_group.setStartState(start_state);

  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
  bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

  std::vector<geometry_msgs::Pose> waypoints;
  waypoints.push_back(start_pose2);

  geometry_msgs::Pose target_pose3 = start_pose2;

  target_pose3.position.z -= 0.2;
  waypoints.push_back(target_pose3);  // down

  target_pose3.position.y -= 0.2;
  waypoints.push_back(target_pose3);  // right

  target_pose3.position.z += 0.2;
  target_pose3.position.y += 0.2;
  target_pose3.position.x -= 0.2;
  waypoints.push_back(target_pose3);  // up and left

  move_group.setMaxVelocityScalingFactor(0.1);

  moveit_msgs::RobotTrajectory trajectory;
  const double jump_threshold = 0.0;
  const double eef_step = 0.01;
  double fraction =
      move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
  ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)",
                 fraction * 100.0);
}

}  // namespace franka_example_controllers

PLUGINLIB_EXPORT_CLASS(franka_example_controllers::CartesianWaypointController,
                       controller_interface::ControllerBase)
