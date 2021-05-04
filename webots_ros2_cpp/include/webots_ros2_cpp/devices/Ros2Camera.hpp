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

#ifndef ROS2_CAMERA_HPP
#define ROS2_CAMERA_HPP

#include <map>

#include <webots/Camera.hpp>

#include <geometry_msgs/msg/quaternion.hpp>
#include <geometry_msgs/msg/point.hpp>
#include <sensor_msgs/image_encodings.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <std_msgs/msg/color_rgba.hpp>
#include <vision_msgs/msg/detection2_d.hpp>
#include <vision_msgs/msg/detection2_d_array.hpp>
#include <vision_msgs/msg/object_hypothesis_with_pose.hpp>

#include <webots_ros2_msgs/msg/wb_camera_recognition_object.hpp>
#include <webots_ros2_msgs/msg/wb_camera_recognition_objects.hpp>
#include <webots_ros2_cpp/utils/Math.hpp>
#include <webots_ros2_cpp/PluginInterface.hpp>
#include <webots_ros2_cpp/WebotsNode.hpp>


namespace webots_ros2
{

  class Ros2Camera : public PluginInterface
  {
  public:
    void init(webots_ros2::WebotsNode *node, std::map<std::string, std::string> &parameters) override;
    void step() override;

  private:
    void publishImage();
    void publishRecognition();

    webots::Camera* mCamera;
    webots_ros2::WebotsNode *mNode;

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr mImagePublisher;
    sensor_msgs::msg::Image mImageMessage;

    rclcpp::Publisher<sensor_msgs::msg::CameraInfo>::SharedPtr mCameraInfoPublisher;
    sensor_msgs::msg::CameraInfo mCameraInfoMessage;

    rclcpp::Publisher<vision_msgs::msg::Detection2DArray>::SharedPtr mRecogntionPublisher;
    rclcpp::Publisher<webots_ros2_msgs::msg::WbCameraRecognitionObjects>::SharedPtr mWebotsRecognitionPublisher;
    vision_msgs::msg::Detection2DArray mRecogntionMessage;
    webots_ros2_msgs::msg::WbCameraRecognitionObjects mWebotsRecognitionMessage;

    std::string mTopicName;
    std::string mFrameName;
    double mPublishTimestep;
    bool mAlwaysOn;
    int mPublishTimestepSyncedMs;

    double mLastUpdate;
    bool mIsEnabled;
  };

}

#endif
