from setuptools import setup
import glob
import os
package_name = 'webots_ros2_husarion'
data_files = []
data_files.append(('share/ament_index/resource_index/packages', ['resource/' + package_name]))
data_files.append(('share/' + package_name + '/launch', ['launch/robot_launch.py']))
data_files.append(('share/' + package_name + '/resource', ['resource/rosbot_controllers.yaml']))
data_files.append(('share/' + package_name + '/resource', ['resource/ekf.yaml']))
data_files.append(('share/' + package_name + '/resource/', ['resource/Rosbot.proto']))
data_files.append(('share/' + package_name + '/resource/', ['resource/RpLidarA2.proto']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/black_ports.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/body.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/cover.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/metallic_connections.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/proximity_sensors.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/screw.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/wheel_rim.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/wheel_tire.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/rplidar_bottom.obj']))
data_files.append(('share/' + package_name + '/resource/meshes/', ['resource/meshes/rplidar_top.obj']))


data_files.append(('share/' + package_name + '/worlds', ['worlds/rosbot.wbt']))
data_files.append(('share/' + package_name, ['package.xml']))

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=data_files,
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='Jakub Delicat',
    maintainer_email='jakub.delicat@husarion.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
        ],
    },
)
