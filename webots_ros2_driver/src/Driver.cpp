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

#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <webots_ros2_driver/WebotsNode.hpp>

#include <string>
#include <iostream>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  //webots::Car* robot = new webots::Car();

  std::cout << "Before robot";

  webots::Supervisor* robot = new webots::Driver();

  // Check if the robot can be a driver, if not create a simple Supervisor
  if (!robot){
    robot = new webots::Supervisor();
  }

  std::cout << "After robot";

  //webots::Car* car = dynamic_cast<webots::Car*>(robot);
  //if(car)
    //robot = car;

  std::string robotName = robot->getName();
  for (char notAllowedChar : " -.)(")
    std::replace(robotName.begin(), robotName.end(), notAllowedChar, '_');

  std::shared_ptr<webots_ros2_driver::WebotsNode> node = std::make_shared<webots_ros2_driver::WebotsNode>(robotName, robot);
  node->init();

  rclcpp::spin(node);
  delete robot;
  rclcpp::shutdown();
  return 0;
}
