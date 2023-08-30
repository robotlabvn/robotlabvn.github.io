# Installing ROS Humble

# Installing Moveit
https://moveit.ros.org/install-moveit2/source/
## Intalling the Moveit Tutorial:
cd ~/ws_moveit2/src
git clone https://github.com/ros-planning/moveit2_tutorials --depth 1
vcs import < moveit2_tutorials/moveit2_tutorials.repos
sudo apt update && rosdep install -r --from-paths . --ignore-src --rosdistro $ROS_DISTRO -y
colcon build --cmake-args -DCMAKE_BUILD_TYPE=Release
## Installing UR_RO2_Package
https://github.com/UniversalRobots/Universal_Robots_ROS2_Driver/tree/humble
## Running robot
https://docs.ros.org/en/ros2_packages/humble/api/ur_robot_driver/overview.html

### Calibartion
ros2 launch ur_calibration calibration_correction.launch.py \
robot_ip:=192.168.1.201 target_filename:="${HOME}/my_robot_calibration.yaml"

### Bringup the UR Robot
```
ros2 launch ur_robot_driver ur_control.launch.py ur_type:=ur10e robot_ip:=192.168.1.201 initial_joint_controller:=joint_trajectory_controller launch_rviz:=true
```
Before running any commands, first check the controllers’ state using ```ros2 control list_controllers```
See the list of controller:
```
forward_position_controller[position_controllers/JointGroupPositionController] inactive  
joint_trajectory_controller[joint_trajectory_controller/JointTrajectoryController] active    
speed_scaling_state_broadcaster[ur_controllers/SpeedScalingStateBroadcaster] active    
joint_state_broadcaster[joint_state_broadcaster/JointStateBroadcaster] active    
io_and_status_controller[ur_controllers/GPIOController] active    
force_torque_sensor_broadcaster[force_torque_sensor_broadcaster/ForceTorqueSensorBroadcaster] active  
```
Make sure the ```joint_trajectory_controller``` active. If not active please run this code bellow:
```
ros2 control set_controller_state joint_trajectory_controller active
```

### Basic Moving package

```
ros2 launch simple_ur_ros2 test_joint_move.launch.py
```

## Using Moveit
ros2 launch ur_moveit_config ur_moveit.launch.py ur_type:=ur10e launch_rviz:=true
# Troubleshooting
echo 'export LC_NUMERIC="en_US.UTF-8"' >>~/.bashrc