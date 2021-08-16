#pragma once
#include <smacc/common.h>
#include <smacc/smacc_state_reactor.h>
#include <boost/statechart/event.hpp>
#include <map>
#include <typeinfo>

namespace smacc
{
namespace state_reactors
{
template <typename TSource, typename TObjectTag = EmptyObjectTag>
struct EvAllGo : sc::event<EvAllGo<TSource, TObjectTag>>
{
};

class SrAllEventsGo : public StateReactor
{
  std::map<const std::type_info *, bool> triggeredEvents;

public:
  SrAllEventsGo() {}

  void onInitialized() override;
  void onEventNotified(const std::type_info * eventType) override;
  bool triggers() override;
};
}  // namespace state_reactors
}  // namespace smacc
