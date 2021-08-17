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

#include <smacc/smacc.h>

// CLIENTS
#include <ros_timer_client/cl_ros_timer.h>

//CLIENT BEHAVIORS
#include <ros_timer_client/client_behaviors/cb_timer_countdown_loop.h>
#include <ros_timer_client/client_behaviors/cb_timer_countdown_once.h>

// ORTHOGONALS
#include "orthogonals/or_timer.h"

using namespace boost;
using namespace smacc;

namespace sm_atomic
{
//STATE
class State1;
class State2;

//--------------------------------------------------------------------
//STATE_MACHINE
struct SmAtomic : public smacc::SmaccStateMachineBase<SmAtomic, State1>
{
  using SmaccStateMachineBase::SmaccStateMachineBase;

  virtual void onInitialize() override { this->createOrthogonal<OrTimer>(); }
};

}  // namespace sm_atomic

#include "states/st_state_1.h"
#include "states/st_state_2.h"
