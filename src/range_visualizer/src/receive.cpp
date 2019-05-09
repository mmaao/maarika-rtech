#include "ros/ros.h"
#include "sensor_msgs/Range.h"

#include <sstream>
sensor_msgs::Range msg;
//Kutsutakse välja kui topicule uus sonum tuleb
void chatterCallback(sensor_msgs::Range sensor)
{
   msg.range=sensor.range/2;
}

int main(int argc, char **argv)
{
//initsialiseerib ROSi. Node'i nimi "receive"
  ros::init(argc, argv, "receive");
  //esimene nodehandle initsialiseerib node'i
  ros::NodeHandle n;
  //subscribe'ib topicule "ultrasound/raw", ROS kutsub valja chatterCallback funktsiooni kui uus sonum saabub
  ros::Subscriber sub = n.subscribe("ultrasound/raw", 1000, chatterCallback);
  //publishib sonumi tyybiga "sensor_msgs::Range", topicuga "ultrasound/filtered", puhvri suurus 1000, puhvrisse kuni 1000 sonumit, enne kui vanu 2ra viskama hakkab
  ros::Publisher publ = n.advertise<sensor_msgs::Range>("ultrasound/filtered", 1000);
  //defineerib sonumi sisu
  msg.header.frame_id = "bla";
  msg.min_range = 0.02;
  msg.max_range = 4;
  msg.field_of_view = 0.785;
  //loopi sagedus
  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    //ns kontrolliks, prindib cmd line'i selle
    ROS_INFO("%f", msg.range);
    //publishib sonumi
    publ.publish(msg);
    //poleks vaja kui subscriberit poleks, aga kui on, siis ilma callback'i ei kutsutaks v2lja
    ros::spinOnce();
    // 10 Hz sageduse hoidmiseks. viivitab kuni ok
    loop_rate.sleep();
  }



  return 0;
}
