---
layout: post
category: blog
title: Motion Planning in Robotics 
snippet: Some good resources for learning motion planning in robotic manipulators.
tags: [papers, robotics]
---
There are many books and papers on robotics motion planning. Please dive deep into motion planning by some questions below.

### Q1. What is motion planning? 

Motion planning robotics arm is the process of finding a collision-free path for a robotic arm to move from its starting configuration to its goal configuration while avoiding obstacles. It is an essential component of robotics that enables robots to perform tasks autonomously and safely. Motion planning robotics arm involves finding the optimal path for the robot arm to move from its starting configuration to its goal configuration while avoiding obstacles and minimizing some objective function. The objective function can be related to energy consumption, time, or other performance metrics.

### Q2. What are some common motion planning algorithms used for robotic arms?

Some common motion planning algorithms used for robotic arms include:

1. **Rapidly-Exploring Random Tree (RRT)**: RRT is a popular algorithm for motion planning in robotics. It generates a tree of random configurations and expands it towards the
goal configuration, exploring the configuration space efficiently[1](https://dl.acm.org/doi/10.5555/1209344)
2. **Probabilistic Roadmap (PRM)**: PRM is another widely used algorithm that constructs a roadmap of valid configurations and connects them to form a graph. It then searches for a path on this graph to reach the goal configuration[1](https://dl.acm.org/doi/10.5555/1209344)
3. **Potential Field Methods**: Potential field methods use attractive and repulsive forces to guide
the robot arm towards the goal configuration while avoiding obstacles.
The robot arm moves along the gradient of the potential field to find a
collision-free path[2](https://control.com/technical-articles/common-control-concepts-used-in-robot-motion-planning/).
4. **Sampling-Based Methods**: Sampling-based methods, such as the Monte Carlo method, randomly sample the configuration space and check for collision-free paths. These
methods are efficient for high-dimensional spaces and can handle complex robot arm configurations[3](https://link.springer.com/chapter/10.1007/978-981-16-4803-8_7).
5. **Optimization-Based Methods**: Optimization-based methods formulate the motion planning problem as an optimization problem and use optimization algorithms, such as the
Newton-Raphson method or the Levenberg-Marquardt algorithm, to find the
optimal path or trajectory for the robot arm[4](https://www.cs.cmu.edu/~venkatrn/papers/icra14.pdf).
6. **Particle Swarm Optimization (PSO)**: PSO is a population-based optimization algorithm inspired by the behavior of bird flocking. It can be used for trajectory planning and
optimization of robot arm movements[5](https://www.sciencedirect.com/science/article/abs/pii/S095219762300283X).
7. **Motion planning with dynamic system:** 
A dynamic system approach to motion planning is a  framework that uses dynamical systems to generate and re-plan trajectories for robots in real-time. Dynamical systems are mathematical models that describe how systems change over time. In the context of robotics, they can be used to 
generate motion and force for contact tasks. This approach is useful because it allows robots to react to changes in their environment and adjust their trajectories accordingly. For example, if a robot is moving towards an object and the object moves, the robot can use a dynamic system approach to re-plan  its trajectory and still reach the object [6](https://www.roboticsproceedings.org/rss15/p21.pdf)

---
# Resources
## Opimization-Based Method:
> **_NOTE:_**  These motion planning algorithms are available in [Moveit](https://ros-planning.github.io/moveit_tutorials/doc/chomp_planner/chomp_planner_tutorial.html) 

- **CHOMP**: Covariant Hamiltonian Optimization for Motion Planning, which is a gradient-based trajectory optimization procedure for robotic motion planning. It uses functional gradient techniques to iteratively improve the quality of an initial trajectory, optimizing a functional that trades off between a smoothness cost and a collision cost. 
[7, pdf](https://www.ri.cmu.edu/pub_files/2013/5/CHOMP_IJRR.pdf)

- **STOMP**: Stochastic Trajectory Optimization for Motion Planning, which is an approach to motion planning that utilizes a stochastic trajectory optimization framework. The goal of STOMP is to find a smooth trajectory that minimizes costs associated with collisions and constraints. Unlike deterministic optimization methods, STOMP generates noisy trajectories and uses them to explore the search space. By incorporating randomness into the trajectory generation process, STOMP can efficiently find solutions for motion planning problems, even for robots with a high degree of freedom. [pdf](http://ros.fei.edu.br/roswiki/attachments/Papers(2f)ICRA2011_Kalakrishnan/kalakrishnan_icra2011.pdf)

- **TrajOpt**: TrajOpt planning is a trajectory optimization framework for generating robot trajectories by local optimization. It models the path planning problem as an optimization problem and uses Sequential Quadratic Programming (SQP) to find the optimal trajectory. TrajOpt is a sequential convex optimization algorithm for motion planning problems where the non-convex, non-affine equality, and non-equality constraints are handled by linearizing them around the current trajectory [pdf](http://joschu.net/docs/trajopt-paper.pdf)


----------------
# References

1. Bruno Siciliano and Oussama Khatib. 2007. Springer Handbook of Robotics. Springer-Verlag, Berlin, Heidelberg.
2. Common Control Concepts Used in Robot Motion Planning, April 16, 2021, Anish Devasia https://control.com/technical-articles/common-control-concepts-used-in-robot-motion-planning/

3. Liu, S., Liu, P. (2021). A Review of Motion Planning Algorithms for Robotic Arm Systems. In: Chew, E., et al. RiTA 2020. Lecture Notes in Mechanical Engineering. Springer, Singapore. https://doi.org/10.1007/978-981-16-4803-8_7

4. K. Gochev, V. Narayanan, B. Cohen, A. Safonova and M. Likhachev, "Motion planning for robotic manipulators with independent wrist joints," 2014 IEEE International Conference on Robotics and Automation (ICRA), Hong Kong, China, 2014, pp. 461-468, doi: 10.1109/ICRA.2014.6906896.

5. Özge Ekrem, Bekir Aksoy,"Trajectory planning for a 6-axis robotic arm with particle swarm optimization algorithm",
Engineering Applications of Artificial Intelligence,
Volume 122,2023,106099,ISSN 0952-1976,
https://doi.org/10.1016/j.engappai.2023.106099.

6. Amanhoud, Walid, Mahdi Khoramshahi and Aude Billard. “A Dynamical System Approach to Motion and Force Generation in Contact Tasks.” Robotics: Science and Systems XV (2019)

7. Matt Zucker, [Nathan Ratliff](https://www.nathanratliff.com/pedagogy/mathematics-for-intelligent-systems) , Dragan AD, et al. "CHOMP: Covariant Hamiltonian optimization for motion planning." The International Journal of Robotics Research. 2013;32(9-10):1164-1193. doi:10.1177/0278364913488805