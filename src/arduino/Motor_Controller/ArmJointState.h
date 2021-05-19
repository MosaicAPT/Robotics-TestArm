#ifndef _ROS_Robotics_TestArm_ArmJointState_h
#define _ROS_Robotics_TestArm_ArmJointState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace Robotics_TestArm
{

  class ArmJointState : public ros::Msg
  {
    public:
      typedef float _position1_type;
      _position1_type position1;
      typedef float _position2_type;
      _position2_type position2;
      typedef float _position3_type;
      _position3_type position3;
      typedef float _position4_type;
      _position4_type position4;
      typedef float _position5_type;
      _position5_type position5;
      typedef float _position6_type;
      _position6_type position6;

    ArmJointState():
      position1(0),
      position2(0),
      position3(0),
      position4(0),
      position5(0),
      position6(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->position1);
      offset += serializeAvrFloat64(outbuffer + offset, this->position2);
      offset += serializeAvrFloat64(outbuffer + offset, this->position3);
      offset += serializeAvrFloat64(outbuffer + offset, this->position4);
      offset += serializeAvrFloat64(outbuffer + offset, this->position5);
      offset += serializeAvrFloat64(outbuffer + offset, this->position6);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position1));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position2));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position3));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position4));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position5));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->position6));
     return offset;
    }

    virtual const char * getType() override { return "Robotics_TestArm/ArmJointState"; };
    virtual const char * getMD5() override { return "f925d3d2a3564969ca247517de2c496c"; };

  };

}
#endif
