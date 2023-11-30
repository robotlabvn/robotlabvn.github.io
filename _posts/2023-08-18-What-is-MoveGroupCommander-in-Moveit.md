---
layout: post
category: blog
title: What is the MoveGroupCommander in Moveit
snippet: Explain the MoveGroupCommander in Moveit and python code.
tags: [robotics]
---
The ```moveit_commander.MoveGroupCommander(group_name)``` is a class in the MoveIt! package for ROS (Robot Operating System) that provides a simple Python interface to a planning group, which is a group of joints on a robot. It can be used to plan and execute motions, set joint or pose goals, create motion plans, move the robot, add objects into the environment, and attach/detach objects from the robot. The group_name parameter specifies the name of the planning group that the MoveGroupCommander will interface with. [move_group_python_interface_tutorial](https://ros-planning.github.io/moveit_tutorials/doc/move_group_python_interface/move_group_python_interface_tutorial.html)



## How to use MoveGroupCommander
To use MoveGroupCommander in MoveIt!, follow these steps:
- 1. Create an instance of MoveGroupCommander: Instantiate the MoveGroupCommander class with the desired group name and robot description. For example:
```
from moveit_commander.move_group import MoveGroupCommander
move_group = MoveGroupCommander("my_robot_group", robot_description="robot_description")
```
- 2.  Set the start state: Specify the initial joint values for the robot group using the set_start_state method. For example:
```
move_group.set_start_state(moveit_msgs.RobotState(joint_values=[0.0, 0.0, 0.0, 0.0, 0.0, 0.0]))
```
- 3.  Plan a motion: Use the plan method to plan a motion for the robot group. For example:
```
move_group.plan()
```
- 4. Execute the motion: Use the go method to execute the planned motion. For example:
```
move_group.go()
```
- 5.  Attach an object to a link: Use the attach_object method to attach an object to a specific link. For example:
```
move_group.attach_object("my_object", "my_robot_group/my_link")
```

-  6. Detach an object from a link: Use the detach_object method to detach an object from a specific link. For example:
```
move_group.detach_object("my_object")
```

## Here is an example code for using MoveGroupCommander in MoveIt!:
Set the pose of the end-effector, if one is available. The expected input is a Pose message, a PoseStamped message or a list of 6 floats: [x, y, z, rot_x, rot_y, rot_z] or a list of 7 floats [x, y, z, qx, qy, qz, qw] 

MovegroupCommander.py
{:.filename}
 ```python
import sys
import copy
import rospy
import moveit_commander
import moveit_msgs.msg
import geometry_msgs.msg

# Initialize moveit_commander and rospy
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a RobotCommander object
robot = moveit_commander.RobotCommander()

# Instantiate a PlanningSceneInterface object
scene = moveit_commander.PlanningSceneInterface()

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("my_robot_group")

# Set the start state
group.set_start_state_to_current_state()

# Set the pose target
pose_target = geometry_msgs.msg.Pose()
pose_target.orientation.w = 1.0
pose_target.position.x = 0.5
pose_target.position.y = 0.0
pose_target.position.z = 0.5
group.set_pose_target(pose_target)

# Plan and execute the motion
plan = group.go(wait=True)

# Print the execution result
print("Execution result: ", plan)

# Clean up
moveit_commander.roscpp_shutdown()
 ```

This code initializes moveit_commander and rospy, creates instances of ```RobotCommander, PlanningSceneInterface,``` and ```MoveGroupCommander```, sets the start state, sets the pose target, plans and executes the motion, and prints the execution result. Finally, it shuts down ```moveit_commander``` and ```rospy```. Note that you need to replace ```"my_robot_group"``` with the name of your planning group.

## Here is an example code for using MoveGroupCommander.set_pose_targets in MoveIt!:
The moveit_commander.move_group.MoveGroupCommander.set_pose_targets() method is used to set multiple pose targets for the end-effector. The expected input is **a list of poses**, where each pose can be a Pose message, a list of 6 floats ```[x, y, z, rot_x, rot_y, rot_z], or a list of 7 floats [x, y, z, qx, qy, qz, qw]```

MovegroupCommander.py
{:.filename}
 ```python
import moveit_commander
import geometry_msgs.msg

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Create a list of pose targets
pose_targets = []
pose_target = geometry_msgs.msg.Pose()
pose_target.orientation.w = 1.0
pose_target.position.x = 0.5
pose_target.position.y = 0.0
pose_target.position.z = 0.5
pose_targets.append(pose_target)

pose_target = geometry_msgs.msg.Pose()
pose_target.orientation.w = 1.0
pose_target.position.x = 0.5
pose_target.position.y = 0.5
pose_target.position.z = 0.5
pose_targets.append(pose_target)

# Set the pose targets
group.set_pose_targets(pose_targets)

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
 ```

## How to use moveit_commander with OMPL planner
To use ```moveit_commander``` with an ```OMPL planner```, you can set the planner id for the ```MoveGroupCommander's``` planning interface. Here's an example of how to do this in Python:

MovegroupCommander.py
{:.filename}
 ```python
import moveit_commander
from moveit_commander import PlanningSceneInterface
from moveit_commander import roscpp_initialize, roscpp_shutdown
import rospy

# Initialize moveit_commander
roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a RobotCommander object
robot = moveit_commander.RobotCommander()

# Instantiate a PlanningSceneInterface object
scene = PlanningSceneInterface()

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("arm")

# Set the planner id
group.set_planner_id("RRTConnectkConfigDefault")

# Set the planning time
group.set_planning_time(5)

# Set the start state
group.set_start_state_to_current_state()

# Set the goal
group.set_pose_target(pose_target)

# Plan and execute the motion
plan = group.go(wait=True)

# Print the execution result
print("Execution result: ", plan)

# Clean up
roscpp_shutdown()
```

In this example, the set_planner_id method is used to set the planner to "RRTConnectkConfigDefault", which is an OMPL planner. The set_planning_time method is used to set the maximum time the planner is allowed to run. After setting the planner and planning time, the rest of the code is similar to using MoveGroupCommander without an OMPL planner.

## Here is an example code for using MoveGroupCommander.shift_pose_target() in MoveIt!:
The ```moveit_commander.move_group.MoveGroupCommander.shift_pose_target()``` method is used to modify the position of the end effector along a specific axis and set the new pose as the pose target. However, it does not directly support shifting the pose in multiple axes in a single call. To achieve the desired effect of shifting the pose in both the X and Z axes, multiple calls to shift_pose_target() would be needed.
MovegroupCommander_shift_pose_target.py
{:.filename}
 ```python

import moveit_commander

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Get the current pose target
current_pose = group.get_current_pose().pose

# Shift the pose target along the X axis by 0.2
group.shift_pose_target(0, 0.2)

# Shift the pose target along the Z axis by 0.2
group.shift_pose_target(2, 0.2)

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
```
In this example, the current pose target is retrieved, and then the pose target is shifted along the X axis by 0.2 and along the Z axis by 0.2 in separate calls to shift_pose_target(). Finally, the motion is planned and executed.

## Here is an example code for using MoveGroupCommander.set_rpy_target() in MoveIt!:
The moveit_commander.move_group.MoveGroupCommander.set_rpy_target() method is used to specify a target orientation for the end-effector using roll, pitch, and yaw angles. Here's an example of how to use it:

MovegroupCommander_set_rpy_target.py
{:.filename}
 ```python
import moveit_commander
import geometry_msgs.msg

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Create a pose target
pose_target = geometry_msgs.msg.Pose()
pose_target.orientation.w = 1.0
pose_target.position.x = 0.5
pose_target.position.y = 0.0
pose_target.position.z = 0.5

# Set the pose target
group.set_pose_target(pose_target)

# Specify a target orientation using roll, pitch, and yaw angles
group.set_rpy_target([0.0, 0.0, 1.57])

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
```
In this example, a pose target is set for the end-effector, and then a target orientation is specified using roll, pitch, and yaw angles. The motion is planned and executed using the specified target orientation.

## Here is an example code for using MoveGroupCommander.set_path_constraints() in MoveIt!:
The ```moveit_commander.move_group.MoveGroupCommander.set_path_constraints()``` method is used to set the path constraints for the motion planning of the MoveGroupCommander's planning group. Path constraints can be used to restrict the motion of the robot, for example, by specifying that a certain link must stay within a certain distance of a certain pose or that a certain link must stay within a certain orientation range.

MovegroupCommander_set_path_constraints.py
{:.filename}
 ```python
import moveit_commander
import moveit_msgs.msg

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Define the path constraint
constraint = moveit_msgs.msg.Constraints()
orientation_constraint = moveit_msgs.msg.OrientationConstraint()
orientation_constraint.link_name = "end_effector_link"
orientation_constraint.header.frame_id = "base_link"
orientation_constraint.orientation.w = 1.0
orientation_constraint.absolute_x_axis_tolerance = 0.1
orientation_constraint.absolute_y_axis_tolerance = 0.1
orientation_constraint.absolute_z_axis_tolerance = 0.1
orientation_constraint.weight = 1.0
constraint.orientation_constraints.append(orientation_constraint)

# Set the path constraints
group.set_path_constraints(constraint)

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
 ```
In this example, a path constraint is defined to restrict the orientation of the end effector link, and then the ```set_path_constraints()``` method is called on the MoveGroupCommander object to set the path constraints. The motion is planned and executed using the specified path constraints.

## Here is an example code for using MoveGroupCommander.set_num_planning_attempts() in MoveIt!:
The moveit_commander.move_group.MoveGroupCommander.set_num_planning_attempts() method is used to set the number of times the motion plan is to be computed from scratch before the shortest solution is returned. The default value is 1.
Here's an example of how to use set_num_planning_attempts():

MovegroupCommander_set_num_planning_attempts.py
{:.filename}
 ```python
import moveit_commander

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Set the number of planning attempts
group.set_num_planning_attempts(5)

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
 ```
## Here is an example code for using MoveGroupCommander.compute_cartesian_path() in MoveIt!:

MovegroupCommander_compute_cartesian_path.py
{:.filename}
 ```python
import moveit_commander

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Define the waypoints
waypoints = [
    group.get_current_pose(),
    group.get_random_pose("base_link"),
    group.get_random_pose("base_link")
]

# Compute the cartesian path
cartesian_path, eef_step, jump_threshold, avoid_collisions, path_constraints = group.compute_cartesian_path(waypoints, eef_step=0.1, jump_threshold=0.2, avoid_collisions=True)

# Plan and execute the motion
plan = group.go(cartesian_path, wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
 ```
In this example, the compute_cartesian_path() method is used to plan a cartesian path between the current pose of the robot and two randomly generated poses. The wait=True parameter ensures that the robot waits for the motion plan to be executed before stopping.

## Here is an example code for using MoveGroupCommander.allow_replanning() in MoveIt!:
The moveit_commander.move_group.MoveGroupCommander.allow_replanning() method is used to enable or disable replanning during motion planning. When replanning is enabled, the motion planner will continuously recompute the motion plan as the environment changes, allowing the robot to adapt to new obstacles or constraints. Here's an example of how to use allow_replanning():

MovegroupCommander_compute_cartesian_path.py
{:.filename}
 ```python
import moveit_commander

# Initialize the moveit_commander
moveit_commander.roscpp_initialize(sys.argv)
rospy.init_node('move_group_python_interface', anonymous=True)

# Instantiate a MoveGroupCommander object
group = moveit_commander.MoveGroupCommander("manipulator")

# Enable replanning
group.allow_replanning(True)

# Plan and execute the motion
plan = group.go(wait=True)

# Clean up
moveit_commander.roscpp_shutdown()
 ```


# References

1. https://ros-planning.github.io/moveit_tutorials/doc/move_group_python_interface/move_group_python_interface_tutorial.html
2. http://docs.ros.org/en/indigo/api/moveit_commander/html/classmoveit__commander_1_1move__group_1_1MoveGroupCommander.html#a51bc4850dbeecbe086a0d1e90c2981b6