---
layout: post
category: blog
title: Path Planning in Robotics
snippet: Learn Path Planning in robotics
tags: [robotics, math]
katex: True
---

**Main Goal:**

- Learn the rigid body geometry in 3D: rotational matrix, transformation matrix, quaternion and Euler angle.
- Learn *Eigen* library matrix and geometry module

## I. What is Path Planning
Path planning is a crucial aspect of robotics that involves planning the path of a robot from its current position to a desired position. The purpose of path planning is to create smooth and continuous paths for the robot to follow, while avoiding obstacles and ensuring that the robot reaches its destination in the most efficient way possible.

 Path planning involves defining a geometric curve for the end-effector between two points, defining a rotational motion between two orientations, and defining a time function for variation of a coordinate between two given values. There are several methods used in path planning, including cubic path, polynomial path, and non-polynomial path planning.  Additionally, there are methods for controlling the motion of a robot, including forward path robot motion and inverse path robot motion. The overall goal of path planning is to create a safe and efficient path for the robot to follow, while ensuring that it avoids obstacles and reaches its destination in the most efficient way possible.



- **Polynomial Path**: A method of defining a geometric curve for the end-effector between two points using a polynomial. This method is also used to create smooth and continuous curves for robot motion.

- **Non-polynomial Path Planning**: A method of defining a geometric curve for the end-effector between two points using non-polynomial equations. This method is used to create smooth and continuous curves for robot motion.

- **Forward Path Robot Motion**: A method of controlling the motion of a robot by specifying the desired path of the end-effector. This method is used to move the robot from its current position to a desired position.

- **Inverse Path Robot Motion**: A method of controlling the motion of a robot by specifying the desired path of the end-effector and calculating the required joint angles to achieve that path. This method is used to move the robot from its current position to a desired position while avoiding obstacles.

- **Rotational Path**: A method of defining a path for a robot that involves rotation around a fixed point. This method is used to create circular or spiral paths for robot motion.

# II. Mathematical form of each methods

1. **Cubic Path**: A method of defining a geometric curve for the end-effector between two points using a cubic polynomial. This method is used to create smooth and continuous curves for robot motion.
$$p(t) = a_0 + a_1t + a_2t^2 + a_3t^3$$
$$
\begin{aligned}
& q(t)=a_0+a_1 t+a_2 t^2+a_3 t^3 \\
& \dot{q}(t)=a_1+2 a_2 t+3 a_3 t^2
\end{aligned}
$$
generates four equations for the coefficients of the path.
$$
\left[\begin{array}{cccc}
1 & t_0 & t_0^2 & t_0^3 \\
0 & 1 & 2 t_0 & 3 t_0^2 \\
1 & t_f & t_f^2 & t_f^3 \\
0 & 1 & 2 t_f & 3 t_f^2
\end{array}\right]\left[\begin{array}{l}
a_0 \\
a_1 \\
a_2 \\
a_3
\end{array}\right]=\left[\begin{array}{c}
q_0 \\
q_0^{\prime} \\
q_f \\
q_f^{\prime}
\end{array}\right]
$$
Their solutions are given in (12.2)-(12.5).
In case that $t_0=0$, the coefficients simplify.
$$
\begin{aligned}
& a_0=q_0 \\
& a_1=q_0^{\prime} \\
& a_2=\frac{3\left(q_f-q_0\right)-\left(2 q_0^{\prime}+q_f^{\prime}\right) t_f}{t_f^2} \\
& a_3=\frac{-2\left(q_f-q_0\right)+\left(q_0^{\prime}+q_f^{\prime}\right) t_f}{t_f^3}
\end{aligned}
$$
It is also possible to employ a time shift and search for a cubic polynomial of $\left(t-t_0\right)$.
$$
q(t)=a_0+a_1\left(t-t_0\right)+a_2\left(t-t_0\right)^2+a_3\left(t-t_0\right)^3
$$
Now, the boundary conditions (12.6) generate a set of equations
$$
\left[\begin{array}{cccc}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
1\left(t_f-t_0\right) & \left(t_f-t_0\right)^2 & \left(t_f-t_0\right)^3 \\
0 & 1 & 2\left(t_f-t_0\right) & 3\left(t_f-t_0\right)^2
\end{array}\right]\left[\begin{array}{l}
a_0 \\
a_1 \\
a_2 \\
a_3
\end{array}\right]=\left[\begin{array}{l}
q_0 \\
q_0^{\prime} \\
q_f \\
q_f^{\prime}
\end{array}\right]
$$
In this equation, $p(t)$ represents the position of the end-effector at time $t$, $a_0$ represents the initial position of the end-effector, $a_1$ represents the initial velocity of the end-effector, and $a_2$ and $a_3$ are the coefficients of the cubic polynomial. These coefficients are calculated using the initial and final conditions of the path, including the position, velocity, and acceleration. The Cubic Path method is used to generate smooth and continuous curves for robot motion.
$$
\begin{aligned}
& q(t)=a_0+a_1 t+a_2 t^2+a_3 t^3 \\
& \dot{q}(t)=a_1+2 a_2 t+3 a_3 t^2
\end{aligned}
$$
generates four equations for the coefficients of the path.
$$
\left[\begin{array}{cccc}
1 & t_0 & t_0^2 & t_0^3 \\
0 & 1 & 2 t_0 & 3 t_0^2 \\
1 & t_f & t_f^2 & t_f^3 \\
0 & 1 & 2 t_f & 3 t_f^2
\end{array}\right]\left[\begin{array}{l}
a_0 \\
a_1 \\
a_2 \\
a_3
\end{array}\right]=\left[\begin{array}{c}
q_0 \\
q_0^{\prime} \\
q_f \\
q_f^{\prime}
\end{array}\right]
$$
Their solutions are given in (12.2)-(12.5).
In case that $t_0=0$, the coefficients simplify.
$$
\begin{aligned}
& a_0=q_0 \\
& a_1=q_0^{\prime} \\
& a_2=\frac{3\left(q_f-q_0\right)-\left(2 q_0^{\prime}+q_f^{\prime}\right) t_f}{t_f^2} \\
& a_3=\frac{-2\left(q_f-q_0\right)+\left(q_0^{\prime}+q_f^{\prime}\right) t_f}{t_f^3}
\end{aligned}
$$
It is also possible to employ a time shift and search for a cubic polynomial of $\left(t-t_0\right)$.
$$
q(t)=a_0+a_1\left(t-t_0\right)+a_2\left(t-t_0\right)^2+a_3\left(t-t_0\right)^3
$$
Now, the boundary conditions (12.6) generate a set of equations
$$
\left[\begin{array}{cccc}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
1\left(t_f-t_0\right) & \left(t_f-t_0\right)^2 & \left(t_f-t_0\right)^3 \\
0 & 1 & 2\left(t_f-t_0\right) & 3\left(t_f-t_0\right)^2
\end{array}\right]\left[\begin{array}{l}
a_0 \\
a_1 \\
a_2 \\
a_3
\end{array}\right]=\left[\begin{array}{l}
q_0 \\
q_0^{\prime} \\
q_f \\
q_f^{\prime}
\end{array}\right]
$$
# References
1. Reza N. Jazar. 2007. Theory of Applied Robotics: Kinematics, Dynamics, and Control. Springer Publishing Company, Incorporated.
