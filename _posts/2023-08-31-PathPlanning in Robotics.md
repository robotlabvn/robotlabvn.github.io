---
layout: post
category: blog
title: Trajectory Generation in Robotics
snippet: Learn Trajectory Generation in robotics
tags: [robotics, math]
katex: True
---

**Main Goal:**

- Learn the fundamental knownledge and mathmatical theory of Trajectory Generation in manipulator.
- Demo Python code of Trajectory Generation.

## I. What is Trajectory Generation
During robot motion, the robot controller receives a 
continuous stream of goal positions and velocities to track. This 
specification of the robot's position as a function of time is called a **trajectory**. In some cases, the trajectory is completely determined by the task, such as when the end-effector needs to track a known moving object. In other cases, when the task is simply to move from one position to another in a given time, we have the freedom to design the trajectory to meet these constraints. This is the domain of **trajectory planning**. A trajectory should be a sufficiently smooth function of time and should respect any given limits on joint velocities, accelerations, or torques. We can consider a **trajectory** as the combination of a **path**, which is a purely geometric description of the sequence of configurations achieved by the robot, and a **time scaling** , which specifies the times when those configurations are reached. There are three cases to consider in trajectory planning:

1. **Point-to-point straight-line trajectories** in both joint space and task space.
2. **Trajectories passing through a sequence of timed via points**.
3. **Minimum-time trajectories** along specified paths, taking actuator limits into consideration

### Definition
A path $$\theta(s)$$ maps a scalar path parameter $$s$$, assumed to be 0 at the start
of the path and 1 at the end, to a point in the robot’s configuration space $$\Theta$$, 

$$\theta: [0, 1] \rightarrow \Theta$$ 

As $$s$$ increases from 0 to 1, the robot moves along the path.
Sometimes $$s$$ is taken to be time and is allowed to vary from time $$s = 0$$ to
the total motion time $$s = T$$, but it is often useful to separate the role of the
geometric path parameter $$s$$ from the time parameter $$t$$. A time scaling $$s(t)$$
assigns a value $$s$$ to each time $$t \in [0, T]$$, $$s : [0, T] \rightarrow [0, 1]$$.


Together, a path and a time scaling define a trajectory $$\theta(s(t))$$, or $$\theta(t)$$ for short. Using the chain rule, the velocity and acceleration along the trajectory can be written as

$$
\dot{\theta} = \frac{d\theta}{ds}\dot{s}, \quad \ddot{\theta} = \frac{d\theta}{ds}\ddot{s} + \frac{d^2\theta}{ds^2}\dot{s^2}.
$$


To ensure that the robot’s acceleration (and therefore dynamics) is well defined, each of $$\theta(s)$$ and $$s(t)$$ must be twice differentiable.


---
## 1. Point-to-Point Trajectories
The simplest type of motion is from rest at one configuration to rest at another, which is called point-to-point motion. For point-to-point motion, the simplest type of path is a straight line

## 1.1 Straight-Line Paths

### Straight-line path in configuration space

A “straight line” from a start configuration $$\theta_{\text{start}}$$ to an end configuration $$\theta_{\text{end}}$$ could be defined in joint space or in task space. The advantage of a straight-line path from $$\theta_{\text{start}}$$ to $$\theta_{\text{end}}$$ in joint space is simplicity: since joint limits typically take the form $$\theta_{i,\text{min}} \leq \theta_i \leq \theta_{i,\text{max}}$$ for each joint $$i$$, the allowable joint configurations form a convex set $$\Theta_{\text{free}}$$ in joint space, so the straight line between any two endpoints in $$\Theta_{\text{free}}$$ also lies in $$\Theta_{\text{free}}$$. The straight line can be written as:

$$
\theta(s) = \theta_{\text{start}} + s(\theta_{\text{end}} - \theta_{\text{start}})
$$ ,
$$
s \in [0, 1]
$$

with derivatives:

$$
\frac{d\theta}{ds} = \theta_{\text{end}} - \theta_{\text{start}}
$$


$$
\frac{d^2\theta}{ds^2} = 0
$$


Straight lines in joint space generally do not yield straight-line motion of the end-effector in task space. 

### Straight-line path in cartesian space
If task-space straight-line motions are desired, the start and end configurations can be specified by $$X_{\text{start}}$$ and $$X_{\text{end}}$$ in task space. If $$X_{\text{start}}$$ and $$X_{\text{end}}$$ are represented by a minimum set of coordinates, then a straight line is defined as:

$$
X(s) = X_{\text{start}} + s(X_{\text{end}} - X_{\text{start}})
$$


$$
s \in [0, 1]
$$


Compared with the case when joint coordinates are used, the following issues must be addressed:

- If the path passes near a kinematic singularity, the joint velocities may become unreasonably large for almost all time scalings of the path.
- Since the robot’s reachable task space may not be convex in $$X$$ coordinates, some points on a straight line between two reachable endpoints may not be reachable.

### Example

 {% include image.html url="/assets/2023-08-31-Trajectory-Generation/2R_robot_trajectory.png" description="A straight-line path in joint space and (top right) the corresponding motion of the end-effector in task space (dashed line)" width="80%" %}

(Left) A 2R robot with joint limits $$0^\circ \leq \theta_1 \leq 180^\circ$$, $$0^\circ \leq \theta_2 \leq 150^\circ$$. (Top center) A straight-line path in joint space and (top right) the corresponding motion of the end-effector in task space (dashed line). The reachable endpoint configurations, subject to joint limits, are indicated in gray. (Bottom center) This curved line in joint space and (bottom right) the corresponding straight-line path in task space (dashed line) would violate the joint limits.


---

- **Cubic Path**: A method of defining a geometric curve for the end-effector between two points using a cubic polynomial

- **Polynomial Path**: A method of defining a geometric curve for the end-effector between two points using a polynomial. This method is also used to create smooth and continuous curves for robot motion.

- **Non-polynomial Path Planning**: A method of defining a geometric curve for the end-effector between two points using non-polynomial equations. This method is used to create smooth and continuous curves for robot motion.

- **Forward Path Robot Motion**: A method of controlling the motion of a robot by specifying the desired path of the end-effector. This method is used to move the robot from its current position to a desired position.

- **Inverse Path Robot Motion**: A method of controlling the motion of a robot by specifying the desired path of the end-effector and calculating the required joint angles to achieve that path. This method is used to move the robot from its current position to a desired position while avoiding obstacles.

- **Rotational Path**: A method of defining a path for a robot that involves rotation around a fixed point. This method is used to create circular or spiral paths for robot motion.

# II. Mathematical form of each methods

- **Cubic Path**: A method of defining a geometric curve for the end-effector between two points using a cubic polynomial. This method is used to create smooth and continuous curves for robot motion.


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
In case that $$t_0=0$$, the coefficients simplify.

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

In this equation, $$p(t)$$ represents the position of the end-effector at time $$t$$, $$a_0$$ represents the initial position of the end-effector, $a_1$ represents the initial velocity of the end-effector, and $$a_2$$ and $$a_3$$ are the coefficients of the cubic polynomial. These coefficients are calculated using the initial and final conditions of the path, including the position, velocity, and acceleration. The Cubic Path method is used to generate smooth and continuous curves for robot motion.

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
In case that $$t_0=0$$, the coefficients simplify.

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
2. Kevin M. Lynch and Frank C. Park. 2017. Modern Robotics: Mechanics, Planning, and Control (1st. ed.). Cambridge University Press, USA.