# kinematics base tests
This repo runs unit tests on several implementations of the moveit_core::KinematicsBase interface that are available as plugins.  These implementations include the ikfast and kdl solvers. The tests consist of calling commonly used interface methods such as initialize, searchPositionIK, searchPositionIK (with callback), getPositionIK and getPositionIK (with multiple solutions).  The ik_fast solvers tested here are those for the KukakR210 and Motoman SIA20d robots.  The MotomanSIA20d arm is a 7 DOF and so it allows testing the redundant joint case.

### Installation

- Install [wstool](http://wiki.ros.org/wstool) in order manage the repos inside the workspace
  ```
  sudo apt-get install python-wstool
  ```

- Cd into the 'src' directory of your catkin workspace and run the following:
  ```
  wstool init . 
  wstool merge https://raw.githubusercontent.com/ros-planning/moveit_kinematics_tests/jade-devel/install.rosinstall
  wstool update
  rosdep install --from-paths . --ignore-src
  cd ..
  catkin build
  ```
  
### Run ROS unit test
- Cd into the catkin workspace directory and run the following

  ```
  catkin run_tests kinematics_base_test
  ```

### See tests summary
- Run the following:

  ```
  catkin_test_results
  ```
