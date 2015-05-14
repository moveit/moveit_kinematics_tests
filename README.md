# kinematics base tests
This repo contains unit test for validating upgrades to the moveit KinematicsBase interface class proposed [here](https://github.com/ros-planning/moveit_core/pull/231).  The ikfast unit test loads up a ikfast kinematics solver for the KukakR210 robot as a plugin.  It mimics the unit test for the [pr2 arm](https://github.com/ros-planning/moveit_pr2/blob/indigo-devel/pr2_moveit_tests/kinematics/src/test_kinematics_as_plugin.cpp) by making several calls to the searchPositionIK, searchPositionIK (with callback), getPositionIK and getPositionIK (with multiple solutions).  

### Installation

- Install [wstool](http://wiki.ros.org/wstool) in order manage the repos inside the workspace
  ```
  sudo apt-get install python-wstool
  ```

- Cd into the 'src' directory of your catkin workspace and run the following:
  ```
  wstool init . 
  wstool merge https://raw.githubusercontent.com/jrgnicho/kinematics_base_tests/indigo-devel/install.rosinstall
  wstool update
  rosdep install --from-paths . --ignore-src
  cd ..
  catkin_make
  ```
  
### Build ROS unit test

- Cd into the catkin workspace directory and run the following

  ```
  catkin_make kinematics_base_test_ikfast
  ```
  
### Run ROS unit test
- Cd into the catkin workspace directory and run the following

  ```
  catkin_make run_tests_kinematics_base_test
  ```
