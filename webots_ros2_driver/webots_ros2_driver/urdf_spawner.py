#!/usr/bin/env python

# Copyright 1996-2022 Cyberbotics Ltd.
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

"""This process simply sends urdf information to the Spawner through a service."""

from launch.actions import ExecuteProcess


def get_webots_driver_node(event, driver_node):
    if "success=True" in event.text.decode().strip():
        return driver_node
    print("WARNING: the Spawner was not able to spawn an URDF robot.")
    return

class URDFSpawner(ExecuteProcess):
    def __init__(self, output='screen', name=None, urdf_path=None, translation=None, rotation=None, **kwargs):
        command = [
                'ros2',
                'service',
                'call',
                '/spawn_urdf_robot',
                'webots_ros2_msgs/srv/SetWbURDFRobot',
            ]

        message = '{ "robot": {'

        if name:
            message += '"name": "' + name + '",'
        if urdf_path:
            message += '"urdf_location": "' + urdf_path + '",'
        if translation:
            message += '"translation": "' + translation + '",'
        if rotation:
            message += '"rotation": "' + rotation + '",'

        message += '} }'
        command.append(message)

        super().__init__(
            output=output,
            cmd=command,
            **kwargs
        )
