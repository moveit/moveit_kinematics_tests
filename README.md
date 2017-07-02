# kinematics base tests
This repo contains unit tests for validating various implementation of the moveit_core::KinematicsBase interface class that are exposed as plugins.  These implementations include ikfast, kdl and the pr2 arms. The tests consist of invoking commonly used methods such as initialize, searchPositionIK, searchPositionIK (with callback), getPositionIK and getPositionIK (with multiple solutions).  The ikfast unit tests load up the ikfast kinematics solvers for the KukakR210 and Motoman SIA20d robots.  The MotomanSIA20d arm is used here in order to verify that ikfast handles the redundant joint case appropriately.

### Installation

- Install [wstool](http://wiki.ros.org/wstool) in order manage the repos inside the workspace
  ```
  sudo apt-get install python-wstool
  sud
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
