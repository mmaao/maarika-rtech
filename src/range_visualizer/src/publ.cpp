#include "ros/ros.h"
#include "sensor_msgs/Range.h"

#include <sstream>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "publ");
  ros::NodeHandle n;
  ros::Publisher range_pub = n.advertise<sensor_msgs::Range>("range", 1000);
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    sensor_msgs::Range msg;
    msg.header.frame_id = "bla";
    msg.min_range = 0.02;
    msg.max_range = 4;
    msg.field_of_view = 0.785;
    msg.range = msg.min_range + ((float)rand()/ RAND_MAX) * (msg.max_range - msg.min_range);
    
    ROS_INFO("%f", msg.range);
    range_pub.publish(msg);

    loop_rate.sleep();
  }


  return 0;
}
