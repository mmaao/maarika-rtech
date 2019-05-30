#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

int main(int argc, char **argv)
{
ros::init(argc, argv, "move_pub");
ros::NodeHandle n;
ros::Publisher movement_pub = n.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity",1); 
ros::Rate rate(10);

while (ros::ok()) 
{
    geometry_msgs::Twist move;
    //velocity controls
    move.linear.x = -0.1; //speed value m/s
    move.angular.z = 0;
    movement_pub.publish(move);

    ros::spinOnce();
    rate.sleep();
}
return 0;
}
