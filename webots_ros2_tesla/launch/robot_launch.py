#!/usr/bin/env python

# Copyright 1996-2023 Cyberbotics Ltd.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Launch Webots Tesla driver."""

import os
import pathlib
import launch
from launch.substitutions import LaunchConfiguration
from launch.actions import DeclareLaunchArgument
from launch.substitutions.path_join_substitution import PathJoinSubstitution
from launch import LaunchDescription
from ament_index_python.packages import get_package_share_directory
from launch_ros.actions import Node
from webots_ros2_driver.webots_launcher import WebotsLauncher
from webots_ros2_driver.utils import controller_url_prefix


def generate_launch_description():
    package_dir = get_package_share_directory('webots_ros2_tesla')
    world = LaunchConfiguration('world')

    webots = WebotsLauncher(
        world=PathJoinSubstitution([package_dir, 'worlds', world])
    )

    robot_description = pathlib.Path(os.path.join(package_dir, 'resource', 'tesla_webots.urdf')).read_text()
    tesla_driver = Node(
        package='webots_ros2_driver',
        executable='driver',
        output='screen',
        additional_env={'WEBOTS_CONTROLLER_URL': controller_url_prefix() + 'vehicle'},
        parameters=[
            {'robot_description': robot_description},
        ],
        respawn=True
    )
    lane_follower = Node(
        package='webots_ros2_tesla',
        executable='lane_follower',
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world',
            default_value='tesla_world.wbt',
            description='Choose one of the world files from `/webots_ros2_tesla/worlds` directory'
        ),
        webots,
        tesla_driver,
        lane_follower,

        # This action will kill all nodes once the Webots simulation has exited
        launch.actions.RegisterEventHandler(
            event_handler=launch.event_handlers.OnProcessExit(
                target_action=webots,
                on_exit=[
                    launch.actions.EmitEvent(event=launch.events.Shutdown())
                ],
            )
        )
    ])
