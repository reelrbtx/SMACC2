#include <smacc2/smacc.hpp>

namespace sm_aws_warehouse_navigation
{
// STATE DECLARATION
struct StState1 : smacc2::SmaccState<StState1, SmAwsWarehouseNavigation>
{
  using SmaccState::SmaccState;

  // TRANSITION TABLE

  // STATE FUNCTIONS
  static void staticConfigure() {}

  void runtimeConfigure() {}

  void onEntry() { RCLCPP_INFO(getLogger(), "Hello world!"); }

  void onExit() {}
};
}  // namespace sm_aws_warehouse_navigation
