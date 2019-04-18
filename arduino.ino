#include <ros.h>
#include <sensor_msgs/Range.h>

  ros::init(argc, argv, "arduino");
  ros::NodeHandle nh;
  ros::Publisher range_pub = n.advertise<sensor_msgs::Range>("range", 1000);

void setup()
{
  Serial.begin(9600);
  pinMode(echoPin,INPUT);
  pinMode(trigPin,OUTPUT);
}

long getSonarReadingMillimeters()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration_us = pulseIn(echoPin, HIGH);
  long distance_mm = (duration_us / 58.0) * 10;
  return distance_mm;
}

void loop()
{
    sensor_msgs::Range msg;
    msg.header.frame_id = "bla";
    msg.range = distance_mm;    
    range_pub.publish(msg);
    delay(1000);
  }

