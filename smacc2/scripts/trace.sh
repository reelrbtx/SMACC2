#!/bin/bash
ros2 trace -u ros2:smacc_event ros2:client_behavior_on_exit_end ros2:client_behavior_on_exit_start ros2:client_behavior_on_entry_end ros2:client_behavior_on_entry_start ros2:client_behavior_on_runtimeConfigure_end ros2:client_behavior_on_runtimeConfigure_start ros2:state_onExit_end ros2:state_onExit_start ros2:state_onEntry_end ros2:state_onEntry_start ros2:update_end ros2:update_start ros2:spinOnce ros2:rcl_init ros2:rcl_node_init ros2:rcl_publisher_init ros2:rcl_publish ros2:rclcpp_publish ros2:rcl_subscription_init ros2:rclcpp_subscription_init ros2:rclcpp_subscription_callback_added ros2:rcl_service_init ros2:rclcpp_service_callback_added ros2:rcl_client_init ros2:rcl_timer_init ros2:rclcpp_timer_callback_added ros2:rclcpp_timer_link_node ros2:rclcpp_callback_register ros2:callback_start ros2:callback_end ros2:rcl_lifecycle_state_machine_init ros2:rcl_lifecycle_transition 
