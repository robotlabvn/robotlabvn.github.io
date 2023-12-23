---
layout: post
category: blog
title: What is the Inverse Kinematic (IK) in robotics
snippet: Explain the Inverse Kinematic (IK) and Python code example
tags: [robotics, python]
katex: True
---
{% include image.html url="/assets/2023-08-19-What-is-Null-space-motion/img.gif" description="in the context of robotics and linear algebra, refers to the motion of a robotic manipulator within the null space of its Jacobian matrix. " width="60%" %}

Inverse kinematics is a mathematical process used in robotics to determine the motion of a robot to reach a desired position. It is essentially the reverse operation of forward kinematics, which computes the workspace coordinates of the robot given a configuration as input. Inverse kinematics is used to calculate the variable joint parameters needed to place the end of a robot manipulator or animation character's skeleton in a given position and orientation relative to the start of the chain. Given the desired robot’s end-effector positions, inverse kinematics can determine an appropriate joint configuration for which the end-effectors reach the desired position. There are two methods to solve inverse kinematics: analytical and numerical. Analytical solutions give a closed-form expression that gives the inverse kinematics as a function of the end-effector's target pose and robot link lengths, while numerical solutions approximate a robot configuration that achieves specified goals and constraints.

## Some applications of inverse kinematics in robotics
Inverse kinematics in robotics has various applications, including:

- Robot Control: It is used to find the variables of actuator for giving position and orientation of the end effector, which is crucial for robot control

- Path Planning and Manipulation: It is essential for tasks like moving a tool along a specified path, manipulating objects, and observing scenes from a desired vantage point

- Automated Manufacturing: In applications such as automated bin picking, inverse kinematics is used to achieve precise motion from an initial position to a desired position between bins and manufacturing machines.

- 3D Animation and Game Programming: Inverse kinematics is important in 3D animation and game programming to move characters' limbs to desired positions and orientations, and to connect game characters physically to the virtual world

These are just a few examples of the many practical applications of inverse kinematics in robotics.

## DH Parameters
DH parameters, or Denavit-Hartenberg parameters, are a convention used in robotics to define the transformation matrices between adjacent links of a robotic system. The DH parameters consist of four parameters for each link:
- a: The distance between two consecutive links along the joint axis (the distance from the origin of frame $$i-1$$ to the origin of frame $$i$$)
- $$\alpha$$ The angle between two consecutive links around the joint axis (the angle from the $$z_i$$ axis to the $$z_{i+1}$$ axis, usually measured in degrees)
- $$d$$: The distance between two consecutive links along the common perpendicular axis (the distance from the origin of frame $$i$$ to the origin of frame $$i+1$$ along the $$x_{i+1}$$ axis)
- $$\theta$$: The angle between two consecutive links around the common perpendicular axis (the angle from the $$x_{i}$$ axis to the $$x_{i+1}$$
axis, usually measured in degrees)

These parameters are used to calculate the transformation matrices for each link in a robotic system, which are then combined to form the overall transformation matrix. This matrix is essential for calculating the inverse kinematics and controlling the robot's motion
# References

1. https://docs.duet3d.com/User_manual/Machine_configuration/Configuring_Robot_DH_parameters
2. https://abeuiuc.github.io/DH_1.html
3. https://www.marginallyclever.com/2020/04/what-are-d-h-parameters/