# This repo for collection motion planning algorithms 

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

### Q3. What are the advantages and disadvantages of using RRT for planning in joint space versus cartesian space in OMPL
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

### OMPL Tutorial
1. https://theairlab.org/summer2020/,  [Motion Planning Tutorial](https://bitbucket.org/castacks/core_planning_tutorial/raw/c8da578242cf8313aafbb986e5f265a9823ad6c1/doc/planning_presentation.pdf)
2. https://bitbucket.org/castacks/core_planning_tutorial/src/master/
# References: 
1. https://ompl.kavrakilab.org/geometricPlanningSE3.html