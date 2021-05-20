#include "Motor_Controller.h"
#include <Servo.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <math.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt16.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include "Robotics_TestArm/ArmJointState.h"

int count = 0;

AccelStepper base(1, BASE_MOTOR_CLK_PIN, BASE_MOTOR_CW_PIN);
AccelStepper shoulder1(1, SHOULDER_MOTOR_1_CLK_PIN, SHOULDER_MOTOR_1_CW_PIN);
AccelStepper shoulder2(1, SHOULDER_MOTOR_2_CLK_PIN, SHOULDER_MOTOR_2_CW_PIN);
AccelStepper elbow(1, ELBOW_MOTOR_CLK_PIN, ELBOW_MOTOR_CW_PIN);
AccelStepper wrist1(1, WRIST_MOTOR_1_CLK_PIN, WRIST_MOTOR_1_CW_PIN);
AccelStepper wrist2(1, WRIST_MOTOR_2_CLK_PIN, WRIST_MOTOR_2_CW_PIN);

MultiStepper steppers;

float joint_step[6];
int joint_status = 0;

ros::NodeHandle nh;
std_msgs::UInt16 msg;

// ArmJointState Callback function
void arm_cb(const Robotics_TestArm::ArmJointState& arm_steps) {
  joint_status = 1;
  joint_step[0] = arm_steps.position1;
  joint_step[1] = arm_steps.position2;
  joint_step[2] = arm_steps.position3;
  joint_step[3] = arm_steps.position4;
  joint_step[4] = arm_steps.position5;
  joint_step[5] = arm_steps.position6;
}

ros::Subscriber<Robotics_TestArm::ArmJointState> arm_sub("/joint_steps", arm_cb);

void setup() {
  //put your setup code here, to run once:
  joint_status = 1;

  nh.initNode();
  nh.subscribe(arm_sub);

  // Configure each stepper
  base.setMaxSpeed(12000);
  shoulder1.setMaxSpeed(4000);
  shoulder2.setMaxSpeed(4000);   /// try to add acceleration
  elbow.setMaxSpeed(4000);
  wrist1.setMaxSpeed(4000);
  wrist2.setMaxSpeed(4000);

  // Then give them to MultiStepper to manage
  steppers.addStepper(base);
  steppers.addStepper(shoulder1);
  steppers.addStepper(shoulder2);
  steppers.addStepper(elbow);
  steppers.addStepper(wrist1);
  steppers.addStepper(wrist2);

  // Configure gripper servo
//  gripper.attach(9);

  digitalWrite(13, 1); //toggle led
}

void loop() {
  if (joint_status == 1) // If command callback (arm_cb) is being called, execute stepper command
  {
    long positions[6];  // Array of desired stepper positions must be long
    positions[0] = joint_step[0]; // negated since the real robot rotates in the opposite direction as ROS
    positions[1] = joint_step[1];
    positions[2] = joint_step[1];
    positions[3] = -joint_step[2];
    positions[4] = -joint_step[3];
    positions[5] = joint_step[4];

    steppers.moveTo(positions);
    //nh.spinOnce();
    steppers.runSpeedToPosition(); // Blocks until all are in position
    //    delay(1000); 
  }

  joint_status = 0;
  nh.spinOnce();
  delay(1);

}
