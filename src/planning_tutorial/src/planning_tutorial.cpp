#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <moveit_visual_tools/moveit_visual_tools.h>

int main(int argc, char** argv)
{
//initsialiseerib ROSi, Node'i nimi "planning_tutorial
  ros::init(argc, argv, "planning_tutorial");
  //esimene nodehandle initsialiseerib node'i
  ros::NodeHandle node_handle;
  ros::AsyncSpinner spinner(1);
  spinner.start();

  static const std::string PLANNING_GROUP = "sia5";

  //planning_groupi nimi, mida kontrollida ja plaanida tahad
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);


  // Cartesian Paths
  // ^^^^^^^^^^^^^^^
  //planeerid cartesian pathi, selleks t2psustad teekonnapunktid, millest end-effector läbi peab minema
 
  geometry_msgs::Pose target_pose = move_group.getCurrentPose().pose;

  std::vector<geometry_msgs::Pose> waypoints;
  waypoints.push_back(target_pose);

  target_pose.position.z -= 0.2;
  waypoints.push_back(target_pose);  // down

  target_pose.position.y -= 0.2;
  waypoints.push_back(target_pose);  // right

  target_pose.position.z += 0.2;
  target_pose.position.y += 0.2;
  waypoints.push_back(target_pose);  // up and left

  // Now, we call the planner to compute the plan and visualize it.
  // Note that we are just planning, not asking move_group
  // to actually move the robot.
  //arvutab plaani ja visualiseerib selle
  moveit::planning_interface::MoveGroupInterface::Plan my_plan;
//bool success = (move_group.plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  // We want the Cartesian path to be interpolated at a resolution of 1 cm
  // which is why we will specify 0.01 as the max step in Cartesian
  // translation.  We will specify the jump threshold as 0.0, effectively disabling it.
  // Warning - disabling the jump threshold while operating real hardware can cause
  // large unpredictable motions of redundant joints and could be a safety issue
  moveit_msgs::RobotTrajectory trajectory;
  //inerts nulliks
  const double jump_threshold = 0.0;
  //sammusuurus 1 cm tagant punkt
  const double eef_step = 0.01;
  //kalkuleerib trajektoori 	
  double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);

//leia minu plaanist objekt trajectory ja selle v22rtuseks trajectory, mis just tegime
my_plan.trajectory_ = trajectory;
//execute'i plaan
move_group.execute(my_plan);
  // END_TUTORIAL

  ros::shutdown();
  return 0;
}
