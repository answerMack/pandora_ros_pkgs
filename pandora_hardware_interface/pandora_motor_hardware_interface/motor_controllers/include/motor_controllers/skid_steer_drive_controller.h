/*********************************************************************
*
* Software License Agreement (BSD License)
*
*  Copyright (c) 2014, P.A.N.D.O.R.A. Team.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the P.A.N.D.O.R.A. Team nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
* Author:  Evangelos Apostolidis
*********************************************************************/
#ifndef MOTOR_CONTROLLERS_SKID_STEER_DRIVE_CONTROLLER_H
#define MOTOR_CONTROLLERS_SKID_STEER_DRIVE_CONTROLLER_H

#include <controller_interface/controller.h>
#include <hardware_interface/joint_command_interface.h>
#include <pluginlib/class_list_macros.h>
#include <realtime_tools/realtime_buffer.h>
#include <realtime_tools/realtime_publisher.h>
#include <geometry_msgs/Twist.h>

#define COMMAND_DELAY_THRESHOLD 3

namespace pandora_hardware_interface
{
namespace motor
{

  class SkidSteerDriveController
  :
    public controller_interface::Controller<
      hardware_interface::VelocityJointInterface>
  {
  private:
    const ros::NodeHandle* rootNodeHandle_;
    hardware_interface::VelocityJointInterface* velocityJointInterface_;
    realtime_tools::RealtimeBuffer< std::vector<double> > commandBuffer_;
    std::vector<double> command_;
    ros::Subscriber commandSubscriber_;
    std::vector<hardware_interface::JointHandle> jointHandles_;

    double wheelSeparation_;
    double wheelRadius_;
    double maxAngularVelocity_;  // in RPM
    int gearbox_ratio_;

    void twistCallback(const geometry_msgs::Twist& twist);
    void setMotorCommands(
      const double leftVelocity, const double rightVelocity);

  public:
    SkidSteerDriveController();
    ~SkidSteerDriveController();

    bool init(
      hardware_interface::VelocityJointInterface* velocityJointInterface,
      ros::NodeHandle& rootNodeHandle,
      ros::NodeHandle& controllerNodeHandle);

    void update(const ros::Time& time, const ros::Duration& period);

    void starting(const ros::Time& time);

    void stopping(const ros::Time& time);
  };
}  // namespace motor
}  // namespace pandora_hardware_interface
#endif  // MOTOR_CONTROLLERS_SKID_STEER_DRIVE_CONTROLLER_H
