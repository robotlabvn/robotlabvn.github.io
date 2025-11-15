<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ARMI Lab: Autonomous Robotics & Machine Intelligence</title>
    <!-- Load Tailwind CSS -->
    <script src="https://cdn.tailwindcss.com"></script>
    <!-- Configure Tailwind for Inter font and a modern color palette -->
    <style>
        @import url('https://fonts.googleapis.com/css2?family=Inter:wght@100..900&display=swap');
        body {
            font-family: 'Inter', sans-serif;
            transition: background-color 0.3s;
        }
        .card-container {
            /* Responsive maximum width, centered, and nice padding */
            max-width: 1200px;
            margin: 0 auto;
            /* White background, rounded corners, shadow */
            background-color: #ffffff;
            border-radius: 2rem; /* rounded-4xl */
            padding: 2.5rem; /* p-10 */
        }
        /* Simple dark mode styling */
        .dark .card-container {
            background-color: #1f2937; /* Gray-800 */
        }
        /* Custom card styling for research/projects */
        .project-card {
            display: flex;
            flex-direction: column;
            border-radius: 1rem;
            overflow: hidden;
            transition: all 0.3s ease;
            height: 100%;
        }
        .project-card:hover {
            transform: translateY(-5px);
            box-shadow: 0 10px 15px rgba(0, 0, 0, 0.1);
        }
        .link-icon {
            @apply inline-block ml-2 text-primary hover:text-secondary transition;
        }
        /* Style for the video player container in the modal (16:9 aspect ratio) */
        .video-wrapper {
            position: relative;
            padding-bottom: 56.25%; /* 16:9 ratio */
            height: 0;
            overflow: hidden;
            max-width: 100%;
            background: black;
        }
        .video-wrapper video {
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
        }
    </style>
    <script>
        tailwind.config = {
            darkMode: 'class', // Enable dark mode via class
            theme: {
                extend: {
                    colors: {
                        'primary': '#4f46e5', // Indigo-600 (Lab Blue)
                        'secondary': '#10b981', // Emerald-500 (Highlight Green)
                    },
                }
            }
        }
    </script>
</head>
<body class="bg-gray-100 text-gray-800 dark:bg-gray-900 dark:text-gray-200 p-4 md:p-10">

    <div class="card-container shadow-2xl lg:p-12 transition duration-500">

        <!-- Header and Lab Identity -->
        <header class="mb-12 border-b-4 pb-8 border-primary dark:border-primary">
            <h1 class="text-6xl font-extrabold text-primary mb-2">
                ARMI Lab
            </h1>
            <p class="text-3xl font-light text-gray-600 dark:text-gray-400">
                Autonomous Robotics and Machine Intelligence Laboratory
            </p>
            <p class="mt-4 text-xl leading-relaxed text-gray-700 dark:text-gray-300">
                <strong class="font-semibold text-secondary">Pioneering the next generation of intelligent, self-governing systems.</strong> We operate at the critical intersection of advanced robotics, machine learning, and control theory to deploy robust solutions in complex, real-world environments.
            </p>
        </header>

        <!-- Core Responsibilities (Adapted from original template section) -->
        <section id="responsibilities" class="mb-12">
            <h2 class="text-4xl font-bold mb-6 text-gray-800 dark:text-gray-100 border-l-4 border-secondary pl-4">
                Core Expertise & Technical Focus
            </h2>
            <ul class="grid grid-cols-1 md:grid-cols-2 gap-x-10 gap-y-5 text-lg text-gray-700 dark:text-gray-300">
                <li class="flex items-start">
                    <span class="text-secondary mr-3 mt-1">&#x25AA;</span>
                    <p>
                        <strong class="text-primary">System Design:</strong> Architect robotics software systems using middleware like <span class="font-mono bg-gray-200 dark:bg-gray-700 px-2 py-1 rounded">ROS/ROS2</span>, integrated with simulation tools like Gazebo and IsaacSim.
                    </p>
                </li>
                <li class="flex items-start">
                    <span class="text-secondary mr-3 mt-1">&#x25AA;</span>
                    <p>
                        <strong class="text-primary">Algorithm Development:</strong> Develop and optimize algorithms for **Imitation Learning** (ACT, Diffusion), **motion planning** (e.g., RRT), **inverse kinematics**, and advanced **perception** (SLAM).
                    </p>
                </li>
                <li class="flex items-start">
                    <span class="text-secondary mr-3 mt-1">&#x25AA;</span>
                    <p>
                        <strong class="text-primary">Simulation & Testing:</strong> Configure high-fidelity **Digital Twin** environments to rigorously validate robotics behavior, system stability, and performance.
                    </p>
                </li>
                <li class="flex items-start">
                    <span class="text-secondary mr-3 mt-1">&#x25AA;</span>
                    <p>
                        <strong class="text-primary">Integration:</strong> Interface specialized hardware with industrial robots (UR, Fanuc, Franka, etc.) and core components (sensors, actuators) via middleware like ROS/ROS 2.
                    </p>
                </li>
            </ul>
        </section>

        <!-- Research Experiences -->
        <section id="research" class="mb-12">
            <h2 class="text-4xl font-bold mb-8 text-gray-800 dark:text-gray-100 border-l-4 border-secondary pl-4">
                Selected Research Publications
            </h2>
            <div class="grid grid-cols-1 lg:grid-cols-2 xl:grid-cols-3 gap-8">

                <!-- Article 1: Digital Twin Framework (Video available) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="#" data-video-url="images/fulls/DT_Unity.mp4" class="video-trigger block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=Digital+Twin+Framework" alt="Digital Twin Framework" class="w-full h-full object-cover transition-opacity duration-300 group-hover:opacity-75">
                         <!-- Play button overlay -->
                        <div class="absolute inset-0 flex items-center justify-center bg-black bg-opacity-40 opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                            <svg xmlns="http://www.w3.org/2000/svg" class="h-16 w-16 text-white" viewBox="0 0 20 20" fill="currentColor">
                                <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clip-rule="evenodd" />
                            </svg>
                        </div>
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">ROS based Digital Twin Framework for Collaboration Robot</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">Proceedings of the International Conference on Sustainable Energy Technologies</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Presents a real-time machine health monitoring DT framework for robot machine-tending based on ISO 23247, utilizing OPC UA and ROS for communication and data exchange.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://link.springer.com/chapter/10.1007/978-981-97-1868-9_74" class="link-icon">Springer Link</a>
                        <a href="https://www.researchgate.net/publication/382224667_A_Digital_Twin_Implementation_Framework_for_a_Collaborative_Robot_Based_on_Iso_23247" class="link-icon">Preprint</a>
                        <a href="https://github.com/TriKnight/unity_universal_robots" class="link-icon">Code</a>
                    </div>
                </article>

                <!-- Article 2: Position-based Visual Servoing (Video available) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="#" data-video-url="images/fulls/UR_dual.mp4" class="video-trigger block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=Dual+Manipulator+PBVS" alt="Position-based Visual Servoing" class="w-full h-full object-cover">
                        <!-- Play button overlay -->
                        <div class="absolute inset-0 flex items-center justify-center bg-black bg-opacity-40 opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                            <svg xmlns="http://www.w3.org/2000/svg" class="h-16 w-16 text-white" viewBox="0 0 20 20" fill="currentColor">
                                <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clip-rule="evenodd" />
                            </svg>
                        </div>
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Position-based Visual Servoing with Dual Manipulators</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">Internal Research</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Focuses on designing a system for Position-based Visual Servoing (PBVS) with dual UR10e robots, using a Realsense D435 camera to track ARTag trajectories for real-time joint velocity control.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="images/fulls/UR_dual.mp4" class="link-icon">Video</a>
                        <a href="images/fulls/PBVS-UR.pdf" class="link-icon">PrePrint</a>
                    </div>
                </article>

                <!-- Article 3: Optimisation Algorithm for Reactive Motion Control (Video available) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="#" data-video-url="images/fulls/Reactive_motion.mp4" class="video-trigger block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=Reactive+Motion+Control" alt="Reactive Motion Control Manipulator" class="w-full h-full object-cover">
                        <!-- Play button overlay -->
                        <div class="absolute inset-0 flex items-center justify-center bg-black bg-opacity-40 opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                            <svg xmlns="http://www.w3.org/2000/svg" class="h-16 w-16 text-white" viewBox="0 0 20 20" fill="currentColor">
                                <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clip-rule="evenodd" />
                            </svg>
                        </div>
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Optimisation Algorithm for Reactive Motion Control Manipulator</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">Internal Research</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Designs an optimization algorithm for reactive motion controllers that enables manipulators to avoid static and dynamic obstacles while moving toward a desired end-effector pose.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="images/fulls/Reactive_motion.mp4" class="link-icon">Video</a>
                    </div>
                </article>

                <!-- Article 4: LiDAR-based Vehicle Detection (Video available) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="#" data-video-url="images/fulls/3DLidar.mp4" class="video-trigger block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=LiDAR+Detection+DBSCAN" alt="LiDAR Detection DBSCAN" class="w-full h-full object-cover">
                        <!-- Play button overlay -->
                        <div class="absolute inset-0 flex items-center justify-center bg-black bg-opacity-40 opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                            <svg xmlns="http://www.w3.org/2000/svg" class="h-16 w-16 text-white" viewBox="0 0 20 20" fill="currentColor">
                                <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clip-rule="evenodd" />
                            </svg>
                        </div>
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">LiDAR-based Vehicle Detection by using DBSCAN Unsupervised Clustering approach</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">ICCRI 2023</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Develops a high-performance, embedded LiDAR-based vehicle detection system using the DBSCAN unsupervised learning algorithm for point cloud recognition in complex roadway areas.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="images/fulls/3DLidar.mp4" class="link-icon">Video</a>
                        <a href="images/fulls/Tri_2023_PrePrint.pdf" class="link-icon">Preprint</a>
                    </div>
                </article>

                <!-- Article 5: Robot Gesture Control (Video available) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="#" data-video-url="images/fulls/Robot_Gesture_Control.mp4" class="video-trigger block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=Robot+Gesture+Control" alt="Robot Gesture Control" class="w-full h-full object-cover">
                        <!-- Play button overlay -->
                        <div class="absolute inset-0 flex items-center justify-center bg-black bg-opacity-40 opacity-0 group-hover:opacity-100 transition-opacity duration-300">
                            <svg xmlns="http://www.w3.org/2000/svg" class="h-16 w-16 text-white" viewBox="0 0 20 20" fill="currentColor">
                                <path fill-rule="evenodd" d="M10 18a8 8 0 100-16 8 8 0 000 16zM9.555 7.168A1 1 0 008 8v4a1 1 0 001.555.832l3-2a1 1 0 000-1.664l-3-2z" clip-rule="evenodd" />
                            </svg>
                        </div>
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Robot Gesture Control Using Online Feedback Data with Multi-Tracking Capture System.</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">AETA 2022</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Explores a wireless, low-latency gesture control method using a Vicon system to track a rigid-body object's motion and translate it into control signals for a KUKA youBot.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="images/fulls/Robot_Gesture_Control.mp4" class="link-icon">Video</a>
                        <a href="images/fulls/Robot Gesture Control Using Online Feedback Data with Multi-Tracking Capture System.pdf" class="link-icon">Preprint</a>
                    </div>
                </article>

                <!-- Article 6: MiniRos: an autonomous UGV robot (Link is to YouTube, cannot be used in a video tag, keeping as a link) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="https://www.youtube.com/watch?v=ZCQJhtsWnWg" target="_blank" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=MiniRos+UGV" alt="MiniRos UGV" class="w-full h-full object-cover">
                        <!-- Link to YouTube is outside the modal system -->
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">MiniRos: an autonomous UGV robot for education and research</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">ICSSE, 2021</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Details the development of MiniRos, a compact, ROS-based autonomous UGV with skid-steering kinematics for outdoor research, capable of 2D SLAM and navigation.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://www.youtube.com/watch?v=ZCQJhtsWnWg" class="link-icon">Video</a>
                        <a href="https://www.researchgate.net/publication/354362978_MiniRos_an_Autonomous_UGV_Robot_for_Education_and_Research" class="link-icon">Preprint</a>
                        <a href="https://github.com/TriKnight/miniros" class="link-icon">Code</a>
                    </div>
                </article>

                <!-- Article 7: V-frame Octocopter (Link is to YouTube, cannot be used in a video tag, keeping as a link) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="https://youtu.be/27bLHVEhebo" target="_blank" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=V-frame+Octocopter" alt="V-frame Octocopter" class="w-full h-full object-cover">
                        <!-- Link to YouTube is outside the modal system -->
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Development of a novel V-frame Octocopter: Design, Kinematic Analysis, and Simulation</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">International Journal of Intelligent Unmanned Systems, 2023</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Presents the kinematic analysis, CAD design (with FEM validation), and Simulink simulation of a new V-frame octocopter platform using PID controllers tuned with the Ziegler-Nichols method.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://youtu.be/27bLHVEhebo" class="link-icon">Video</a>
                        <a href="https://www.researchgate.net/publication/356438869_Design_Analysis_and_Simulation_of_V-frame_Octocopter" class="link-icon">Preprint</a>
                    </div>
                </article>

                <!-- Article 8: Adaptive Optimal Control (No video link provided in original) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="images/fulls/Upper_robot.png" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=Upper+Exoskeleton+Control" alt="Adaptive Optimal Control for Upper Exoskeleton" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Adaptive Optimal Control for Upper Exoskeleton following Saturation Function</h3>
                        <h6 class="text-sm font-semibold text-gray-500 dark:text-gray-400 mb-3">ICMT, 2021</h6>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Introduces a new optimal control based on a saturation function (similar to a sliding mode model) for the upper exoskeleton, demonstrating good tracking performance in simulation.
                        </p>
                    </div>
                </article>

            </div>
        </section>


        <!-- Robotics Projects -->
        <section id="projects" class="mb-12">
            <h2 class="text-4xl font-bold mb-8 text-gray-800 dark:text-gray-100 border-l-4 border-secondary pl-4">
                Robotics Project Portfolio
            </h2>
            <div class="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-8">

                <!-- Project 1: Upper body humanoid robot design -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="images/fulls/Upper_full.JPG" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=Humanoid+Upper+Body+CAD" alt="Upper body humanoid robot design" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Upper body humanoid robot design (14 DOF)</h3>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            A 14 DOF upper body humanoid robot design, integrated with a 3D depth camera, suitable for 3D printing and laser cutting for research and educational purposes.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://grabcad.com/library/upper-body-humanoid-robot-1" class="link-icon">3D File (GrabCAD)</a>
                    </div>
                </article>

                <!-- Project 2: Autonomous Service Robot (Link is to YouTube, keeping as a link) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="https://youtu.be/kqwAIAZnEu0" target="_blank" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=Autonomous+Service+Robot" alt="Autonomous Service Robot" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Autonomous Service Robot</h3>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            A ROS-based mobile robot implemented with 2D Lidar and an embedded computer, designed for SLAM and Autonomous Navigation in service environments (restaurants, hospitals).
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://youtu.be/kqwAIAZnEu0" class="link-icon">Video</a>
                    </div>
                </article>

                <!-- Project 3: Docking and Locking for Electric bike -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="images/thumbs/Bosch_Docking_Locking_White_3.JPG" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=E-Bike+Docking+Mechanism" alt="E-Bike Docking Mechanism" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Docking and Locking Mechanism for Electric Bike</h3>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            Innovative design of a charger docking and locking mechanism for electric motorbikes, developed for the "Bosch Green Challenge project" (Awarded "Certification of Innovation Activities and Development").
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://grabcad.com/library/docking-and-locking-pole-for-electric-bike-1" class="link-icon">3D File (GrabCAD)</a>
                    </div>
                </article>
                
                <!-- Project 4: Ant-like robot -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="images/fulls/Ant_full.JPG" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700">
                        <img src="https://placehold.co/800x400/10b981/ffffff?text=23-DOF+Ant-like+Robot" alt="Ant-like robot" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">Ant-like Robot (23 DOF)</h3>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            A 23-DOF, six-legged robot with 3 DOF per leg, utilizing servo actuators and a plastic frame, developed primarily for STEM education and complex gait analysis.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://grabcad.com/library/ant-like-robot-1" class="link-icon">3D File (GrabCAD)</a>
                    </div>
                </article>
                
                <!-- Project 5: RC Humanoid Robot (Link is to YouTube, keeping as a link) -->
                <article class="project-card bg-gray-50 dark:bg-gray-800 shadow-md">
                    <a href="https://youtu.be/RDtGJLPC5hI" target="_blank" class="block overflow-hidden h-48 bg-gray-200 dark:bg-gray-700 cursor-pointer relative group">
                        <img src="https://placehold.co/800x400/4f46e5/ffffff?text=RC+Humanoid+19-DOF" alt="RC Humanoid Robot with 19-DOF" class="w-full h-full object-cover">
                    </a>
                    <div class="p-6 flex-grow">
                        <h3 class="text-xl font-bold mb-2 text-primary">RC Humanoid Robot with 19-DOF</h3>
                        <p class="text-sm text-gray-600 dark:text-gray-300">
                            A fully remote-controlled humanoid model with 19 degrees of freedom, designed with manufacturing methods like 3D printing and laser cutting in mind, used for STEM teaching.
                        </p>
                    </div>
                    <div class="p-6 pt-0 border-t border-gray-200 dark:border-gray-700">
                        <a href="https://grabcad.com/library/humanoid-rc-robot-1" class="link-icon">3D File (GrabCAD)</a>
                        <a href="https://youtu.be/RDtGJLPC5hI" class="link-icon">Video</a>
                    </div>
                </article>
                
            </div>
        </section>

        <!-- Technical Capabilities -->
        <section id="capabilities" class="mb-12 p-8 bg-gray-50 dark:bg-gray-800 rounded-2xl shadow-inner">
            <h2 class="text-4xl font-bold mb-6 text-gray-800 dark:text-gray-100 border-l-4 border-secondary pl-4">
                Technical Capabilities
            </h2>
            <div class="grid grid-cols-1 md:grid-cols-3 gap-8">
                
                <!-- Programming Skills -->
                <div>
                    <h3 class="text-2xl font-semibold mb-3 text-primary">Programming & Frameworks</h3>
                    <p class="text-lg text-gray-700 dark:text-gray-300 mb-4">
                        Core development in low-level and high-level languages for robotics and AI.
                    </p>
                    <p align="left">
                        <!-- Using a common badge service to display skills -->
                        <img src="https://skillicons.dev/icons?i=python,cpp,ros,pytorch,git,latex" alt="Skills: Python, C++, ROS, PyTorch, Git, LaTeX" class="w-full h-auto"/>
                    </p>
                </div>
                
                <!-- Lab Tutorials / Teaching -->
                <div>
                    <h3 class="text-2xl font-semibold mb-3 text-primary">Lab Tutorials & Curriculum</h3>
                    <ul class="space-y-2 text-base text-gray-700 dark:text-gray-300 list-disc pl-5">
                        <li>Robotics and Autonomous Systems (ROS, Pytorch)</li>
                        <li>Embedded intelligent System (ROS, OpenCV) </li>
                        <li>Microcontroller / Digital Signal Processing</li>
                        <li>Robotics Workshop (CAD and PCB Design)</li>
                    </ul>   
                </div>
                
                <!-- Hand-on Hardware Experiments -->
                <div>
                    <h3 class="text-2xl font-semibold mb-3 text-primary">Hands-on Hardware Experience</h3>
                    <ul class="space-y-2 text-base text-gray-700 dark:text-gray-300 list-disc pl-5">
                        <li>**Robot Platforms:** UR10e, Kuka Youbot, Turtlebot 3, NAO, DJI Drone.</li>
                        <li>**Sensors:** Velodyne VLP-16, IMU-Xsens Mti-30, Intel Realsense, SICK Lidar.</li>
                        <li>**Embedded Computers:** Nvidia Jetson family, Raspi-Pi, NUC, Arduino.</li>
                        <li>**Actuators:** Servo, Linear motors, and various motor drivers.</li>
                    </ul>
                </div>
                
            </div>
            
            <!-- PCB Design Showcase -->
            <div class="mt-10">
                <h3 class="text-2xl font-semibold mb-3 text-primary">PCB Design Showcase</h3>
                <a href="images/fulls/PCB_Design.pdf" class="block overflow-hidden rounded-xl shadow-lg hover:shadow-xl transition duration-300">
                    <img src="https://placehold.co/1200x250/4f46e5/ffffff?text=Example+PCB+Design+Schematic" alt="PCB Design Example" class="w-full h-auto object-cover">
                </a>
            </div>
            
        </section>


    </div>
    
    <!-- Video Modal Structure -->
    <div id="video-modal" class="fixed inset-0 bg-black bg-opacity-90 flex items-center justify-center p-4 z-[100] hidden" onclick="closeVideoModal(event)">
        <div class="w-full max-w-5xl bg-gray-900 rounded-xl overflow-hidden shadow-2xl relative" onclick="event.stopPropagation()">
            <button onclick="closeVideoModal()" class="absolute top-4 right-4 text-white hover:text-red-500 z-10 transition">
                <svg xmlns="http://www.w3.org/2000/svg" class="h-8 w-8" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12" />
                </svg>
            </button>
            <div class="video-wrapper">
                <video id="video-player" controls preload="metadata" playsinline></video>
            </div>
        </div>
    </div>


    <!-- Simple Dark Mode Toggle -->
    <button onclick="document.documentElement.classList.toggle('dark')" class="fixed bottom-4 right-4 p-3 bg-primary text-white rounded-full shadow-lg hover:bg-indigo-700 transition duration-300 text-sm font-medium z-50">
        Toggle Theme
    </button>
    
    <script>
        // JavaScript for Modal Logic
        const videoModal = document.getElementById('video-modal');
        const videoPlayer = document.getElementById('video-player');

        function openVideoModal(url) {
            videoPlayer.src = url;
            videoModal.classList.remove('hidden');
            // Autoplay the video after a short delay to ensure modal visibility
            setTimeout(() => {
                videoPlayer.load();
                videoPlayer.play().catch(error => {
                    // Handle autoplay blocking if necessary, but keep the video loaded
                    console.warn("Autoplay was prevented:", error);
                });
            }, 100);
        }

        function closeVideoModal(event) {
            // Check if the click was outside the modal content, or on the close button
            if (!event || event.target.id === 'video-modal' || event.target.closest('button') === videoModal.querySelector('button')) {
                videoPlayer.pause();
                videoPlayer.currentTime = 0; // Reset video to start
                videoPlayer.removeAttribute('src'); // Clean up source to free memory
                videoModal.classList.add('hidden');
            }
        }
        
        // Event listener to attach click handlers to video triggers
        document.addEventListener('DOMContentLoaded', () => {
            document.querySelectorAll('.video-trigger').forEach(trigger => {
                trigger.addEventListener('click', (e) => {
                    e.preventDefault();
                    const videoUrl = trigger.getAttribute('data-video-url');
                    if (videoUrl) {
                        openVideoModal(videoUrl);
                    }
                });
            });
        });
    </script>

</body>
</html>