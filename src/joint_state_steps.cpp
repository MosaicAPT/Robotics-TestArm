#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "Robotic_TestArm/ArmJointState.h"
#include "math.h"

// Init variables
Robotics_TestArm::ArmJointState arm_steps;
Robotics_TestArm::ArmJointState total;

// We are 16th's microstepping the motors
int stepsPerRevolution[7] = {160, 6400, 6400, 6400, 6400, 6400, 6400}; 
int joint_status = 0;
double cur_angle[7];
int joint_step[7];
double prev_angle[7] = {0,0,0,0,0,0,0}; 
double init_angle[7] = {0,0,0,0,0,0,0};
double total_steps[7] = {0,0,0,0,0,0,0};
int count = 0;
int momo = 0;

void cmd_cb(const sensor_msgs::JointState& cmd_arm)
{
  if (count==0){
    prev_angle[0] = cmd_arm.position[0];
    prev_angle[1] = cmd_arm.position[1];
    prev_angle[2] = cmd_arm.position[2];
    prev_angle[3] = cmd_arm.position[3];
    prev_angle[4] = cmd_arm.position[4];
    prev_angle[5] = cmd_arm.position[5];
    prev_angle[6] = cmd_arm.position[6];


    init_angle[0] = cmd_arm.position[0];
    init_angle[1] = cmd_arm.position[1];
    init_angle[2] = cmd_arm.position[2];
    init_angle[3] = cmd_arm.position[3];
    init_angle[4] = cmd_arm.position[4];
    init_angle[5] = cmd_arm.position[5];
    init_angle[6] = cmd_arm.position[6];

  }

  ROS_INFO_STREAM("Received /move_group/fake_controller_joint_states");

  if (prev_angle[0,1,2,3,4,5,6] == cmd_arm.position[0,1,2,3,4,5,6]){

    arm_steps.position1 = (int)((cmd_arm.position[0]-init_angle[0])*stepsPerRevolution[0]*(4.25)*1000);     //max rail distance=0.791367 m   ,   max steps for this value is = 17833
    arm_steps.position2 = (int)((cmd_arm.position[1]-init_angle[1])*stepsPerRevolution[1]*(4.25*2)/(2*M_PI));
    arm_steps.position3 = (int)((cmd_arm.position[2]-init_angle[2])*stepsPerRevolution[2]*(15.3*4)/(2*M_PI));
    arm_steps.position4 = (int)((cmd_arm.position[3]-init_angle[3] + 0)*stepsPerRevolution[3]*(5.18*4)/(2*M_PI));
    arm_steps.position5 = (int)((cmd_arm.position[4]-init_angle[4])*stepsPerRevolution[4]*(5.18*2)/(2*M_PI));
    arm_steps.position6 = (int)((cmd_arm.position[5]-init_angle[5])*stepsPerRevolution[5]*(5.18*2)/(2*M_PI));
    arm_steps.position7 = (int)((cmd_arm.position[6]-init_angle[6])*stepsPerRevolution[6]*(5.18*2)/(2*M_PI));

    momo = 1;
  }
 if (count!=0){
    prev_angle[0] = cmd_arm.position[0];
    prev_angle[1] = cmd_arm.position[1];
    prev_angle[2] = cmd_arm.position[2];
    prev_angle[3] = cmd_arm.position[3];
    prev_angle[4] = cmd_arm.position[4];
    prev_angle[5] = cmd_arm.position[5];
    prev_angle[6] = cmd_arm.position[6];

  }

  ROS_INFO_NAMED("test", "cmd_arm.position[0] %f", cmd_arm.position[0]);
  ROS_INFO_NAMED("test", "init_angle[0] %f", init_angle[0]);

  ROS_INFO_STREAM("Done conversion to /joint_steps");
  joint_status = 1;
  count=1;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "Robotics_TestArm_Converter");
  ros::NodeHandle nh;
  ROS_INFO_STREAM("In main function");
  ros::Subscriber sub = nh.subscribe("/joint_states",1000,cmd_cb);
  ros::Publisher pub = nh.advertise<Robotics_TestArm::ArmJointState>("/joint_steps",500);
  ros::Rate loop_rate(20);

  while(ros::ok())
  {
    if(momo == 1)
    {      
      momo = 0;
      pub.publish(arm_steps);
      ROS_INFO_STREAM("Published to /joint_steps");
    }
    ros::spinOnce();
  }
  ros::spin();
  return 0;
}
    