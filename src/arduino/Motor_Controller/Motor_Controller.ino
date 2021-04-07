#include "Motor_Controller.h"

// ROS Setup 
ros::NodeHandle nh;
geometry_msgs::Twist msg;

// Motor Functions

Motor::Motor(const int& clkPin, const int& cwPin, const String& joint)
{
  this->clkPin = clkPin;
  this->cwPin = cwPin;
  this->joint = joint;
  pinMode(this->clkPin, OUTPUT);
  pinMode(this->cwPin, OUTPUT);
  digitalWrite(this->clkPin, LOW);
  digitalWrite(this->cwPin, LOW);
}

Motor::Motor() {}

void Motor::MoveMotor(const int& speed, const String& dir)
{
  // Set Direction
  if (dir == "cw") {
    digitalWrite(this->cwPin, HIGH);
  }
  else {
    digitalWrite(this->cwPin, LOW);
  }
  // Set PWM to the speed
  analogWrite(this->clkPin, speed);
}

// Set up the motors
Motor baseMotor = Motor(BASE_MOTOR_CLK_PIN, BASE_MOTOR_CW_PIN, "Base");
Motor shoulderMotor1 = Motor(SHOULDER_MOTOR_1_CLK_PIN, SHOULDER_MOTOR_1_CW_PIN, "Shoulder1");
Motor shoulderMotor2 = Motor(SHOULDER_MOTOR_2_CLK_PIN, SHOULDER_MOTOR_2_CW_PIN, "Shoulder2");
Motor elbowMotor = Motor(ELBOW_MOTOR_CLK_PIN, ELBOW_MOTOR_CW_PIN, "Elbow");
Motor wristMotor1 = Motor(WRIST_MOTOR_1_CLK_PIN, WRIST_MOTOR_1_CW_PIN, "Wrist1");
Motor wristMotor2 = Motor(WRIST_MOTOR_2_CLK_PIN, WRIST_MOTOR_2_CW_PIN, "Wrist2");

// Initialize speed variables
int base_speed = 0;
int shoulder_speed = 0;
int elbow_speed = 0;
int wrist1_speed = 0;
int wrist2_speed = 0;


// Create Callback for ROS Subscriber
void motorCallBack(const geometry_msgs::Twist& cmd_vel)
{
  base_speed = cmd_vel.linear.x * 510;
  shoulder_speed = cmd_vel.linear.y * 510;
  elbow_speed = cmd_vel.linear.z * 510;
  wrist1_speed = cmd_vel.angular.x * 510;
  wrist2_speed = cmd_vel.angular.y * 510;
  if (base_speed > 0) {
    baseMotor.MoveMotor(abs(base_speed), "cw");
  }
  else {
    baseMotor.MoveMotor(abs(base_speed), "ccw");
  }
  if (shoulder_speed > 0) {
    shoulderMotor1.MoveMotor(abs(shoulder_speed), "cw");
    shoulderMotor2.MoveMotor(abs(shoulder_speed), "cw");
  }
  else {
    shoulderMotor1.MoveMotor(abs(shoulder_speed), "ccw");
    shoulderMotor2.MoveMotor(abs(shoulder_speed), "ccw");
  }
  if (elbow_speed > 0) {
    elbowMotor.MoveMotor(abs(elbow_speed), "cw");
  }
  else {
    elbowMotor.MoveMotor(abs(elbow_speed), "ccw");
  }
  if (wrist1_speed > 0) {
    wristMotor1.MoveMotor(abs(wrist1_speed), "cw");
  }
  else {
    wristMotor1.MoveMotor(abs(wrist1_speed), "ccw");
  }
  if (wrist2_speed > 0) {
    wristMotor2.MoveMotor(abs(wrist2_speed), "cw");
  }
  else {
    wristMotor2.MoveMotor(abs(wrist2_speed), "ccw");
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", motorCallBack);

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1);
}
