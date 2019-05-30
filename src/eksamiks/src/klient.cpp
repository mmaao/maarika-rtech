#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "klient");
  if (argc != 2)
  {
    ROS_INFO("usage: klient X");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<eksamiks::paneLiikuma>("pane_liikuma");
  eksamiks::pane_liikuma srv;
  srv.request.a = atoll(argv[1]);
  if (client.call(srv))
  {
    ROS_INFO("ready to move");
  }
  else
  {
    ROS_ERROR("Failed to call service pane_liikuma");
    return 1;
  }

  return 0;
}

