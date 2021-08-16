#pragma once

#include <sm_dance_bot/clients/cl_led/cl_led.h>
#include <smacc/smacc.h>

namespace sm_dance_bot
{
namespace cl_led
{
class CbLEDOff : public smacc::SmaccClientBehavior
{
public:
  cl_led::ClLED * ledActionClient_;

  void onEntry() override
  {
    this->requiresClient(ledActionClient_);

    cl_led::ClLED::Goal goal;
    goal.command = cl_led::ClLED::Goal::CMD_OFF;
    ledActionClient_->sendGoal(goal);
  }

  void onExit() override
  {
    //RCLCPP_INFO(getNode()->get_logger(),"Entering ToolClientBehavior");
  }
};
}  // namespace cl_led
}  // namespace sm_dance_bot
