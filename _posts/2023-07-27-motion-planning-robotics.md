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
## Rapidly-Exploring Random Tree (RRT):
- **RRT**: Rapidly-Exploring Random Tree, which is an algorithm designed to efficiently search nonconvex, high-dimensional spaces by randomly building a space-filling tree. The tree is constructed incrementally from samples drawn randomly from the search space and is inherently biased to grow towards large unsearched areas of the problem. RRTs were developed by Steven M. LaValle and James J. Kuffner Jr [pdf](http://msl.cs.uiuc.edu/~lavalle/papers/Lav98c.pdf)

- **RRT-Connect**:  a variation of the Rapidly-Exploring Random Tree (RRT) algorithm that is used for single-query path planning in high-dimensional configuration spaces. It is an efficient approach that aims to find a path from a start configuration to a goal configuration by growing two trees simultaneously, one from the start and one from the goal, until they meet [pdf](https://www.cs.cmu.edu/afs/cs/academic/class/15494-s12/readings/kuffner_icra2000.pdf)

## Opimization-Based Method:

- **CHOMP**: Covariant Hamiltonian Optimization for Motion Planning, which is a gradient-based trajectory optimization procedure for robotic motion planning. It uses functional gradient techniques to iteratively improve the quality of an initial trajectory, optimizing a functional that trades off between a smoothness cost and a collision cost. 
[pdf](https://www.ri.cmu.edu/pub_files/2013/5/CHOMP_IJRR.pdf)

- **STOMP**: Stochastic Trajectory Optimization for Motion Planning, which is an approach to motion planning that utilizes a stochastic trajectory optimization framework. The goal of STOMP is to find a smooth trajectory that minimizes costs associated with collisions and constraints. Unlike deterministic optimization methods, STOMP generates noisy trajectories and uses them to explore the search space. By incorporating randomness into the trajectory generation process, STOMP can efficiently find solutions for motion planning problems, even for robots with a high degree of freedom. [pdf](http://ros.fei.edu.br/roswiki/attachments/Papers(2f)ICRA2011_Kalakrishnan/kalakrishnan_icra2011.pdf)

- **TrajOpt**: TrajOpt planning is a trajectory optimization framework for generating robot trajectories by local optimization. It models the path planning problem as an optimization problem and uses Sequential Quadratic Programming (SQP) to find the optimal trajectory. TrajOpt is a sequential convex optimization algorithm for motion planning problems where the non-convex, non-affine equality, and non-equality constraints are handled by linearizing them around the current trajectory [pdf](http://joschu.net/docs/trajopt-paper.pdf)

- **NEO**: Novel Expeditious Optimisation Algorithm is a reactive motion controller for manipulators that can avoid static and dynamic obstacles while moving toward the desired goal. It is a fast and purely reactive motion controller that uses optimization techniques to generate smooth and collision-free trajectories in real-time. NEO is designed to be used as a local controller in conjunction with a global motion planner for more complex scenes [pdf](https://arxiv.org/pdf/2010.08686.pdf)

## Moveit Q&A

### Q1. What are differences between joint space and cartesian space in Moveit?
The differences between joint space and Cartesian space in MoveIt are as follows:
Joint space:

- Joint space refers to the space of all possible joint configurations of the robot[6](https://robotics.stackexchange.com/questions/2422/is-configuration-space-same-as-joint-space).
- It is defined by the values of the robot's joint angles, which determine the position of each joint.
- Joint space planning involves specifying exact joint positions to achieve a desired end-effector position or trajectory[3](https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html).
- Joint space planning is useful for precise control of the robot's motion and can be used for tasks such as pick-and-place
operations[1](https://www.sciencedirect.com/science/article/pii/S0736584523000352).

Cartesian space:

- Cartesian space refers to the space of all possible end-effector positions and orientations of the robot[3](https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html).
- It is defined by the position and orientation of the robot's end-effector in three-dimensional space.
- Cartesian space planning involves specifying a desired end-effector position or trajectory to achieve a task[3](https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html).
- Cartesian space planning is useful for tasks that
require the robot to follow a specific path or trajectory, such as
painting or welding[3](https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html).

In MoveIt, depending on the planning problem, the planner
 can choose between joint space and Cartesian space for problem 
representation [2](https://ros-planning.github.io/moveit_tutorials/doc/move_group_interface/move_group_interface_tutorial.html). Joint space planning involves specifying exact joint positions, while 
Cartesian space planning involves specifying desired end-effector 
positions or trajectories [3](https://picknik.ai/cartesian%20planners/moveit/motion%20planning/2021/01/07/guide-to-cartesian-planners-in-moveit.html). The choice between joint space and Cartesian space depends on the 
specific task requirements and the level of control needed over the 
robot's motion.
### Q2. Can RRT be used for planning in both joint space and cartesian space in OMPL?
RRT (Rapidly-exploring Random Tree) in OMPL can be used in both joint space and Cartesian space[1](https://books.google.com/books?dq=rrt+in+ompl+can+be+used+in+both+joint+space+and+cartesian+space.+ompl+provides+planners+for+both+joint+space+and+cartesian+space%2C+including+rrt%2C+allowing+users+to+choose+the+appropriate+space+for+their+planning+problem.&hl=en&id=SyO7BQAAQBAJ&lpg=PA539&ots=proUR9lrl4&pg=PA539&sa=X&sig=ACfU3U08bTea0f2uT-meImF80DFucBx3eA&source=bl&ved=2ahUKEwiA8oexxcKAAxVoRjABHYCbCPkQ6AF6BAgAEAE)[2](https://ros-planning.github.io/moveit_tutorials/doc/ompl_interface/ompl_interface_tutorial.html)[4](https://ompl.kavrakilab.org/classompl_1_1geometric_1_1RRT.html)[5](http://docs.ros.org/en/melodic/api/moveit_tutorials/html/doc/ompl_interface/ompl_interface_tutorial.html).
 OMPL provides planners for both joint space and Cartesian space, 
including RRT, allowing users to choose the appropriate space for their 
planning problem[1](https://books.google.com/books?dq=rrt+in+ompl+can+be+used+in+both+joint+space+and+cartesian+space.+ompl+provides+planners+for+both+joint+space+and+cartesian+space%2C+including+rrt%2C+allowing+users+to+choose+the+appropriate+space+for+their+planning+problem.&hl=en&id=SyO7BQAAQBAJ&lpg=PA539&ots=proUR9lrl4&pg=PA539&sa=X&sig=ACfU3U08bTea0f2uT-meImF80DFucBx3eA&source=bl&ved=2ahUKEwiA8oexxcKAAxVoRjABHYCbCPkQ6AF6BAgAEAE).
 The implementation of RRT in OMPL is built on top of the Open Motion 
Planning Library, which allows the user to define a custom state space 
and control space[1](https://books.google.com/books?dq=rrt+in+ompl+can+be+used+in+both+joint+space+and+cartesian+space.+ompl+provides+planners+for+both+joint+space+and+cartesian+space%2C+including+rrt%2C+allowing+users+to+choose+the+appropriate+space+for+their+planning+problem.&hl=en&id=SyO7BQAAQBAJ&lpg=PA539&ots=proUR9lrl4&pg=PA539&sa=X&sig=ACfU3U08bTea0f2uT-meImF80DFucBx3eA&source=bl&ved=2ahUKEwiA8oexxcKAAxVoRjABHYCbCPkQ6AF6BAgAEAE).
 Therefore, RRT in OMPL can be used in both joint space and Cartesian 
space, depending on the specific planning problem and the user's 
preference.

### Q3. RRT for planning in joint space versus cartesian space in OMPL
Advantages and disadvantages of using RRT for planning in joint space versus Cartesian space in OMPL are:
Advantages of using RRT in joint space:

- Joint space planning is useful for precise control of the robot's motion, and RRT can provide a feasible path to achieve a
desired end-effector position or trajectory[1](https://books.google.com/books?dq=rrt+in+ompl+can+be+used+in+both+joint+space+and+cartesian+space.+ompl+provides+planners+for+both+joint+space+and+cartesian+space%2C+including+rrt%2C+allowing+users+to+choose+the+appropriate+space+for+their+planning+problem.&hl=en&id=SyO7BQAAQBAJ&lpg=PA539&ots=proUR9lrl4&pg=PA539&sa=X&sig=ACfU3U08bTea0f2uT-meImF80DFucBx3eA&source=bl&ved=2ahUKEwiA8oexxcKAAxVoRjABHYCbCPkQ6AF6BAgAEAE)[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).
- Joint space planning can be faster than Cartesian space planning, especially for low-dimensional robots[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).
- Joint space planning can handle complex constraints, such as joint limits, singularities, and collisions[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).

Disadvantages of using RRT in joint space:

- Joint space planning can be computationally expensive for high-dimensional robots[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).
- Joint space planning may not be suitable for tasks
that require the robot to follow a specific path or trajectory in
Cartesian space[3](https://kavrakilab.org/iros2011/IROS_2011_MP_Tutorial.pdf).
- Joint space planning may require a good initial guess for the joint angles to find a feasible path[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).

Advantages of using RRT in Cartesian space:

- Cartesian space planning can handle tasks that
require the robot to follow a specific path or trajectory in Cartesian
space, such as painting or welding[3](https://kavrakilab.org/iros2011/IROS_2011_MP_Tutorial.pdf).
- Cartesian space planning can be more intuitive for users who are not familiar with the robot's joint angles[3](https://kavrakilab.org/iros2011/IROS_2011_MP_Tutorial.pdf).
- Cartesian space planning can be faster for high-dimensional robots with complex kinematics[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).

Disadvantages of using RRT in Cartesian space:

- Cartesian space planning can be computationally expensive, especially for high-dimensional robots[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).
- Cartesian space planning may not be able to handle complex constraints, such as joint limits, singularities, and collisions[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).
- Cartesian space planning may require a good initial guess for the end-effector position to find a feasible path[2](https://answers.ros.org/question/53745/cartesian-rrt-or-sbpl-motion-planning-for-non-pr2/).

Overall, the choice between joint space and Cartesian 
space planning with RRT in OMPL depends on the specific planning problem
 and the user's preference. Joint space planning is suitable for precise
 control of the robot's motion, while Cartesian space planning is 
suitable for tasks that require the robot to follow a specific path or 
trajectory in Cartesian space.



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

### OMPL Tutorial
8. https://theairlab.org/summer2020/,  [Motion Planning Tutorial](https://bitbucket.org/castacks/core_planning_tutorial/raw/c8da578242cf8313aafbb986e5f265a9823ad6c1/doc/planning_presentation.pdf)
9. https://bitbucket.org/castacks/core_planning_tutorial/src/master/
10. https://ompl.kavrakilab.org/geometricPlanningSE3.html
