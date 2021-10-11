// Copyright 2021 RobosoftAI Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*****************************************************************************************************************
 *
 * 	 Authors: Pablo Inigo Blasco, Brett Aldrich
 *
 ******************************************************************************************************************/
#include <move_base_z_client_plugin/client_behaviors/cb_pause_slam.hpp>

namespace cl_move_base_z
{
CbPauseSlam::CbPauseSlam(std::string serviceName)
  : smacc2::client_behaviors::CbServiceCall<slam_toolbox::srv::Pause>(serviceName.c_str())
{
}

void CbPauseSlam::onEntry()
{
  this->requiresComponent(this->slam_);

  auto currentState = slam_->getState();

  if (currentState == CpSlamToolbox::SlamToolboxState::Resumed)
  {
    RCLCPP_INFO(getLogger(), "[CbPauseSlam] calling pause service to toggle from resumed to paused");
    smacc2::client_behaviors::CbServiceCall<slam_toolbox::srv::Pause>::onEntry();
  }
  else
  {
      RCLCPP_INFO(getLogger(), "[CbPauseSlam] calling skipped. The current slam state is already paused.");
  }
}

}  // namespace cl_move_base_z
