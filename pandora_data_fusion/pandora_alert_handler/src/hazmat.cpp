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
 * Authors: 
 *   Tsirigotis Christos <tsirif@gmail.com>
 *********************************************************************/

#include "alert_handler/hazmat.h"

namespace pandora_data_fusion
{
  namespace pandora_alert_handler
  {

    Hazmat::Hazmat() {}

    bool Hazmat::isSameObject(const ObjectConstPtr& object) const
    {
      bool cond = Object<Hazmat>::isSameObject(object) 
        && pattern_ == 
        boost::dynamic_pointer_cast<const Hazmat>(object)->getPattern();

      return cond;
    }

    void Hazmat::fillGeotiff(pandora_data_fusion_msgs::
        DatafusionGeotiffSrv::Response* res) const
    {
      res->hazmatx.push_back( pose_.position.x );
      res->hazmaty.push_back( pose_.position.y );
      res->pattern.push_back( pattern_ );
    }

    void Hazmat::getVisualization(visualization_msgs::
        MarkerArray* markers) const
    {
      visualization_msgs::Marker marker;
      marker.header.frame_id = getFrameId();
      marker.header.stamp = ros::Time::now();
      marker.ns = type_;
      marker.id = id_;
      marker.pose = pose_;
      marker.type = visualization_msgs::Marker::SPHERE;
      marker.scale.x = 0.1;
      marker.scale.y = 0.1;
      marker.scale.z = 0.1;
      marker.color.r = 1;
      marker.color.g = 0.65;
      marker.color.b = 0;
      marker.color.a = 0.7;
      markers->markers.push_back(marker);

      visualization_msgs::Marker description;
      description.header.frame_id = getFrameId();
      description.header.stamp = ros::Time::now();
      description.ns = type_;
      description.id = id_;
      description.pose = pose_;
      description.pose.position.z = pose_.position.z + 0.1;
      description.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
      description.text = type_ + "_" + boost::to_string(id_) + "_" + 
        boost::to_string(pattern_);
      description.scale.z = 0.1;
      description.color.r = 1;
      description.color.g = 0.65;
      description.color.b = 0;
      description.color.a = 0.7;
      markers->markers.push_back(description);
    }

}  // namespace pandora_alert_handler
}  // namespace pandora_data_fusion

