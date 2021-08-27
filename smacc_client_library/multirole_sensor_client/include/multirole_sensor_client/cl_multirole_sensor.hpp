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

#pragma once

#include <optional>
#include <rclcpp/rclcpp.hpp>
#include <smacc/client_bases/smacc_subscriber_client.hpp>
#include <smacc/impl/smacc_state_machine_impl.hpp>
#include <smacc/smacc_signal.hpp>

namespace cl_multirole_sensor
{
using namespace smacc;

template <typename TSource, typename TOrthogonal>
struct EvTopicMessageTimeout : sc::event<EvTopicMessageTimeout<TSource, TOrthogonal>>
{
};

using namespace smacc::client_bases;

//---------------------------------------------------------------
template <typename MessageType>
class ClMultiroleSensor : public smacc::client_bases::SmaccSubscriberClient<MessageType>
{
public:
  typedef MessageType TMessageType;
  SmaccSignal<void()> onMessageTimeout_;

  ClMultiroleSensor() : smacc::client_bases::SmaccSubscriberClient<MessageType>()
  {
    //RCLCPP_INFO( getNode()->get_logger(),"[ClMultiroleSensor] constructor");
    initialized_ = false;
  }

  template <typename T>
  boost::signals2::connection onMessageTimeout(void (T::*callback)(), T * object)
  {
    return this->getStateMachine()->createSignalConnection(onMessageTimeout_, callback, object);
  }

  std::function<void()> postTimeoutMessageEvent;

  template <typename TOrthogonal, typename TSourceObject>
  void onOrthogonalAllocation()
  {
    SmaccSubscriberClient<MessageType>::template onOrthogonalAllocation<
      TOrthogonal, TSourceObject>();

    this->postTimeoutMessageEvent = [=]() {
      onMessageTimeout_();

      auto event = new EvTopicMessageTimeout<TSourceObject, TOrthogonal>();
      this->postEvent(event);
    };
  }

  void onInitialize() override
  {
    if (!initialized_)
    {
      SmaccSubscriberClient<MessageType>::onInitialize();

      this->onMessageReceived(&ClMultiroleSensor<MessageType>::resetTimer, this);

      if (timeout_)
      {
        auto ros_clock = rclcpp::Clock::make_shared();
        timeoutTimer_ = rclcpp::create_timer(
          this->getNode(), this->getNode()->get_clock(), *timeout_,
          std::bind(&ClMultiroleSensor<MessageType>::timeoutCallback, this));
        //timeoutTimer_->start();
        timeoutTimer_->reset();
      }
      else
      {
        RCLCPP_WARN(
          this->getNode()->get_logger(),
          "Timeout sensor client not set, skipping timeout watchdog funcionality");
      }

      initialized_ = true;
    }
  }

  std::optional<rclcpp::Duration> timeout_;

protected:
  void resetTimer(const MessageType & /*msg*/)
  {
    //resetting the timer
    timeoutTimer_->reset();
    //timeoutTimer_->stop();
    //timeoutTimer_->start();
  }

private:
  rclcpp::TimerBase::SharedPtr timeoutTimer_;
  bool initialized_;

  void timeoutCallback() { postTimeoutMessageEvent(); }
};
}  // namespace cl_multirole_sensor
