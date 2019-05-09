#include <ros.h>
#include <sensor_msgs/Range.h>

int echoPin = A4;
int trigPin = A5;

ros::NodeHandle nh;
sensor_msgs::Range msg;
ros::Publisher range("ultrasound/raw", &msg);
void setup()

{
  nh.initNode();
  nh.advertise(range);
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
    float us = getSonarReadingMillimeters(); //Get distance from wall with ultrasonic sensor
    //sensor_msgs::Range msg;
    msg.header.frame_id = "bla";
    msg.min_range = 0.02;
    msg.max_range = 4;
    msg.field_of_view = 0.785;
    double reading = getSonarReadingMillimeters();
    msg.range = us/1000;
    range.publish(&msg);
    nh.spinOnce();
    delay(100);
  }
