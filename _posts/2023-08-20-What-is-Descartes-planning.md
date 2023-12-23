---
layout: post
category: blog
title: What is the Descartes path planning
snippet: Explain and tutorial the Descartes path planning
tags: [robotics, ROS, C++]
---
{% include image.html url="/assets/2023-08-19-What-is-Descartes-planning/Puzzle_Piece_Demo.gif" description=" Descartes Descartes Motion Planner Puzzle Piece " width="80%" %}

Descartes is a ROS-Industrial project that performs path-planning on under-defined Cartesian trajectories. It uses trajectory points, robot models, and planners to generate a joint-trajectory that complies with the constraints of a given process. Trajectory points define an individual point in time along a path, robot models define the physical characteristics of a robot that must complete a given trajectory, and planners are responsible for finding valid and optimal solutions through a sequence of trajectory points for a given robot model. Each of these major components has a separate package which provides reference implementations. More information can be found in the ROSCon 2015 talk by Shaun Edwards entitled, ["The Descartes Planning Library for Semi-Constrained Cartesian Trajectories"](https://roscon.ros.org/2015/presentations/ROSCon_Descartes.pdf)

ROS Link: [http://wiki.ros.org/descartes](http://wiki.ros.org/descartes)

Descartes planning library for semi-constrained trajectories
**• Requirements**
– Generate common sense plans

– Find easy solutions fast, hard solutions
with time

– Handle hybrid trajectories (joint,
Cartesian, specialized points)

– Fast re-planning/cached planning


## Key Features

{% include image.html url="/assets/2023-08-19-What-is-Descartes-planning/Descartes_planning_2.png" description=" Descartes is a ROS-Industrial project that performs path-planning on under-defined Cartesian trajectories " width="100%" %}


Descartes, as a path planning library, is often compared to MoveIt. However, it differs from MoveIt in several key ways:

- **Cartesian Planning**: While MoveIt plans free space motion (i.e. move from A to B), Descartes plans robot joint motion for semi-constrained Cartesian paths (i.e. ones whose waypoints may have less than a fully specified 6DOF pose).

- **Efficient, Repeatable, Scale-able Planning**: The paths that result from Descartes appear very similar to human generated paths, but without all the effort. The plans are also repeatable and scale-able to the complexity of the problem (easy paths are planned very quickly, hard paths take time but are still solved).

- **Dynamic Re-planning**: Path planning structures are maintained in memory after planning is complete. When changes are made to the desired path, an updated robot joint trajectory can be generated nearly instantaneously.

- **Offline Planning**: Similar to MoveIt, but different than other planners, Descartes is primarily focused on offline or sense/plan/act applications. Real-time planning is not a feature of Descartes. 

## Installation

Install all ROS dependences
```
https://github.com/ros-industrial-consortium/descartes
https://github.com/ros-industrial-consortium/descartes_tutorials/
https://github.com/ros-industrial/industrial_core
https://github.com/ros-industrial/abb
```
Running
```
roslaunch descartes_tutorials setup.launch
rosrun descartes_tutorials tutorial1
```
Robot ABB will execute a line by using Descartes planning

{% include image.html url="/assets/2023-08-19-What-is-Descartes-planning/Descartes_planning.gif" description=" Descartes is a ROS-Industrial project that performs path-planning on under-defined Cartesian trajectories " width="100%" %}

## What are the advantages of descartes' path planning over other planners
The advantages of Descartes' path planning over other planners include:

- Semi-Constrained Cartesian Paths: Descartes plans robot joint motion for semi-constrained Cartesian paths, allowing for planning in scenarios where waypoints may have less than a fully specified 6DOF pose

- Efficient and Repeatable Planning: The paths generated by Descartes are efficient, repeatable, and scalable to the complexity of the problem. They resemble human-generated paths without the same level of effort

- Dynamic Re-planning: Descartes maintains path planning structures in memory, enabling the generation of an updated robot joint trajectory nearly instantaneously when changes are made to the desired path
    
- Offline Planning Focus: Descartes is primarily focused on offline or sense/plan/act applications, making it suitable for applications where real-time planning is not a requirement
    
- Path Optimization and Collision Avoidance: Descartes offers path optimization, collision avoidance, and a plug-in architecture, making it suitable for various robotic applications.

These advantages position Descartes as a suitable choice for applications requiring efficient, repeatable, and scalable path planning in semi-constrained Cartesian environments, where real-time planning is not a necessity

    
{% include youtube.html id="IFZOyh4kpOQ" %}

# References

1. https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html
2. http://wiki.ros.org/descartes