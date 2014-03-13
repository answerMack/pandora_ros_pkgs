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
* Author: Manos Tsardoulias
* Author: Aris Thallas
*********************************************************************/

#include "target_selector.h"
#include "ros/ros.h"

#include <actionlib/client/simple_action_client.h>
#include <std_msgs/Int16.h>
#include <data_fusion_communications/GetVictimsAction.h>
#include "geometry_msgs/PoseStamped.h"


typedef actionlib::SimpleActionClient<data_fusion_communications::GetVictimsAction> VictimsClient;

class VictimTargetSelector: public TargetSelector{
	
protected:
	
	ros::NodeHandle _nh;
	//~ std::vector<geometry_msgs::PoseStamped> _victimsVector;
	
private:
	
	VictimsClient _getVictimsActionClient;
	ros::Publisher _selectedTargetIndexPublisher;
	
	geometry_msgs::PoseStamped chooseVictim( std::vector<geometry_msgs::PoseStamped>& victimsVector );
	
	
public:
	
	//~ VictimTargetSelector(void) {}
	VictimTargetSelector(MapAttributes& mapAttr, Coverage& cov);
	void selectTarget(PixelCoords* target);
	//~ void selectTarget(geometry_msgs::PoseStamped* target);
	bool selectTarget(geometry_msgs::PoseStamped* target);
	
};