/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
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
 *   * Neither the name of Willow Garage, Inc. nor the names of its
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
 */

/** \author Dalibor Matura, Jia Pan */

#include "fcl/articulated_model/model_config.h"
#include "fcl/articulated_model/joint.h"
#include <algorithm>

// Define for boost version < 1.47
#ifndef BOOST_ASSERT_MSG
#define BOOST_ASSERT_MSG(expr, msg) ((void)0)
#endif

namespace fcl
{

ModelConfig::ModelConfig() {}

ModelConfig::ModelConfig(const ModelConfig& model_cfg) :
  joint_cfgs_map_(model_cfg.joint_cfgs_map_)
{}

ModelConfig::ModelConfig(std::map<std::string, boost::shared_ptr<Joint> > joints_map)
{
  std::map<std::string, boost::shared_ptr<Joint> >::iterator it;
  for(it = joints_map.begin(); it != joints_map.end(); ++it)
    joint_cfgs_map_[it->first] = JointConfig(it->second);
}

JointConfig ModelConfig::getJointConfigByJointName(const std::string& joint_name) const
{
  std::map<std::string, JointConfig>::const_iterator it = joint_cfgs_map_.find(joint_name);
  BOOST_ASSERT_MSG((it != joint_cfgs_map_.end()), "Joint name not valid");

  return it->second;
}

JointConfig& ModelConfig::getJointConfigByJointName(const std::string& joint_name)
{
  std::map<std::string, JointConfig>::iterator it = joint_cfgs_map_.find(joint_name);
  BOOST_ASSERT_MSG((it != joint_cfgs_map_.end()), "Joint name not valid");

  return it->second;
}

JointConfig ModelConfig::getJointConfigByJoint(boost::shared_ptr<Joint> joint) const
{
  return getJointConfigByJointName(joint->getName());
}

JointConfig& ModelConfig::getJointConfigByJoint(boost::shared_ptr<Joint> joint)
{
  return getJointConfigByJointName(joint->getName());
}


}
