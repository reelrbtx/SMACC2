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
#pragma once

#include <move_base_z_client_plugin/move_base_z_client_plugin.h>
#include <smacc/smacc_asynchronous_client_behavior.h>

namespace cl_move_base_z
{
// waits a robot pose message. Usually used for the startup synchronization.
class CbWaitPose : public smacc::SmaccAsyncClientBehavior
{
public:
  CbWaitPose();
  virtual ~CbWaitPose();

  template <typename TOrthogonal, typename TSourceObject>
  void onOrthogonalAllocation()
  {
    this->requiresClient(moveBaseClient_);
    smacc::SmaccAsyncClientBehavior::onOrthogonalAllocation<TOrthogonal, TSourceObject>();
  }

  void onEntry() override;

protected:
  cl_move_base_z::ClMoveBaseZ * moveBaseClient_;
};
}  // namespace cl_move_base_z
