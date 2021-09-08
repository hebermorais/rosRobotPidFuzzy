#define ROSSERIAL_ARDUINO_TCP

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"

#include "ConfigMotor.h"
#include "ConfigWifi.h"

ros::NodeHandle nh;

bool conectado = false;
float wheelbase = 0.09;
float L = 0.4;
float r = 0.016;

void onTwist(const geometry_msgs::Twist &msg) {

  Serial.print("LINEAR X: ");
  Serial.print(msg.linear.x);
  Serial.print("    ANGULAR Z: ");
  Serial.print(msg.angular.z);

  float vx= msg.linear.x;
  float w=  msg.angular.z;
             
  int v_right =-((w*L)/(2*r)) + (vx/r);
  int v_left =  ((w*L)/(2*r)) + (vx/r);

  Serial.print("    V_RIGHT: ");
  Serial.print(v_right);
  Serial.print("    V_LEFT: ");
  Serial.println(v_left);

  if (v_right < 0){
    v_right = v_right * -1;  
    mdT(v_right);
  }else{
    mdF(v_right);
  }

  if (v_left < 0){
    v_left = v_left * -1;  
    meT(v_left);
  }else{
    meF(v_left);
  }
  
}

ros::Subscriber<geometry_msgs::Twist> sub("robot_01/cmd_vel", onTwist);

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  configuraWifi();
  conectaROS();
  configuraMotores();
  nh.subscribe(sub);

}

void loop() {
  if (nh.connected()) {
    nh.spinOnce();
    delay(1);
  } else {
    Serial.println("Not Connected");
  }
  nh.spinOnce();

}

void conectaROS() {
  IPAddress server(192, 168, 0, 101);
  const uint16_t serverPort = 11411;

  nh.getHardware()->setConnection(server, serverPort);
  nh.initNode();

  Serial.print("IP = ");
  Serial.println(nh.getHardware()->getLocalIP());
  rosConnected();
}

bool rosConnected() {
  bool connected = nh.connected();
  conectado = connected;
  if (conectado != connected) {
    conectado = connected;
    Serial.println(connected ? "ROS connected" : "ROS disconnected");
  }
  digitalWrite(2, conectado ? HIGH : LOW);
  return connected;
}
