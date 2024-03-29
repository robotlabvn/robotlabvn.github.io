---
layout: post
category: blog
title: Evaluate the reach capability of a robot system
snippet: A tool that allows users to visualize and quantitatively evaluate the reach capability of a robot system for a given workpiece.
tags: [robotics, ROS]
katex: True
---

**Quantitatively evaluate the reach capability**

{% include image.html url="/assets/2024-01-11-Reach-package-quantitatively-reach-analysis/reach_study_demo.gif" description=" a ROS package is a tool that allows users to visualize and quantitatively evaluate the reach capability of a robot system for a given workpiece " width="90%" %}

The ROS package is a tool that allows users to visualize and quantitatively evaluate the reach capability of a robot system for a given workpiece. It contains ROS-based plugins for kinematics, evaluation, and display interfaces. The package can be used to calculate a numerical "fitness" score of an inverse kinematics (IK) solution at a given Cartesian target pose, with higher values indicating better reachability. The package can also generate a point cloud of target points on the workpiece and create a configuration YAML file defining the parameters of the reach study and the configuration of the interface plugins. The package can be installed by cloning the repository into a catkin workspace and installing the dependencies. The ROS package can be used with ROS1 infrastructure and plugins, or with ROS2-based plugins. 


## I. How to use this ros package

The package can also generate a point cloud of target points on the workpiece and create a configuration YAML file defining the parameters of the reach study and the configuration of the interface plugins. The package contains ROS-based plugins for kinematics, evaluation, and display interfaces. The interfaces described above are exposed as plugins using the boost_plugin_loader library to support custom implementations.

To use this, follow these general steps:

1. Install the reach ros package
2. Prepare necessary files for your robot system, such as URDF, SRDF, kinematics file, joint limits file, etc.
3. Generate a mesh model of the workpiece if needed.
4. Create a point cloud of the target points on the workpiece using a command line tool like PCL 1.8:
```
pcl_mesh_sampling <workpiece_mesh>.ply <output_cloud>.pcd -n_samples <number of samples> -leaf_size <leaf_size>
```
5. Create a configuration YAML file defining the parameters of the reach study and the configuration of the interface plugins.
6. Run the setup launch file and the reach study analysis.

## II. Result of this ros package

This package is a tool that allows users to visualize and quantitatively evaluate the reach capability of a robot system for a given workpiece. The reach_ros and reach_ros2 repositories provide ROS-based plugins, capability demos, and general usage instructions for the reach package

{% include youtube.html id="vbiBiJssqnM" %}

## References
1. [GitHub](https://github.com/ros-industrial/reach)
