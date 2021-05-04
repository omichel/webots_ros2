// Copyright 1996-2021 Cyberbotics Ltd.
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

#ifndef ROS2_GPS_HPP
#define ROS2_GPS_HPP

#include <webots/GPS.hpp>
#include <geometry_msgs/msg/point_stamped.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <sensor_msgs/msg/nav_sat_status.hpp>
#include <std_msgs/msg/float32.hpp>
#include <webots_ros2_cpp/PluginInterface.hpp>
#include <webots_ros2_cpp/WebotsNode.hpp>

namespace webots_ros2
{
  class Ros2GPS : public PluginInterface
  {
  public:
    void init(webots_ros2::WebotsNode *node, std::map<std::string, std::string> &parameters) override;
    void step() override;

  private:
    void pubishPoint();
    void publishGPS();

    webots::GPS *mGPS;
    webots_ros2::WebotsNode *mNode;

    rclcpp::Publisher<sensor_msgs::msg::NavSatFix>::SharedPtr mGPSPublisher;
    sensor_msgs::msg::NavSatFix mGPSMessage;

    rclcpp::Publisher<geometry_msgs::msg::PointStamped>::SharedPtr mPointPublisher;
    geometry_msgs::msg::PointStamped mPointMessage;

    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr mVelocityPublisher;

    double mLastUpdate;
    bool mIsEnabled;

    std::string mTopicName;
    std::string mFrameName;
    double mPublishTimestep;
    bool mAlwaysOn;
    int mPublishTimestepSyncedMs;
  };

}
#endif
