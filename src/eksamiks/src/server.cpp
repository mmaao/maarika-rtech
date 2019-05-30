#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>


void liigu(eksamiks::paneLiikuma::Request &req)
{

 if (req == 1){
  ROS_INFO("move forward");
  geometry msgs::Twist move;
  move.linear.x=-0.1;
  move.angular.z = 0;
  }
  else{
  ROS_INFO("turn");
  geometry msgs::Twist move;
  move.linear.x=0;
  move.angular.z = 0.2;
  }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("pane_liikuma", liigu);
  ROS_INFO("Moving");
    ros::Rate r(100);
  while(n.ok()){
  
  ros::spinOnce();
  
  }


  return 0;
}
