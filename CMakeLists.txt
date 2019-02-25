cmake_minimum_required(VERSION 2.8.3)
project(canny_edge_my_face)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_camera
  cv_bridge
  image_transport
  roscpp
  rospy
  std_msgs
)

catkin_package(
#
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(canny_face src/canny_face.cpp)
target_link_libraries(canny_face ${catkin_LIBRARIES})

## Install canny_face
install(TARGETS canny_face
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# Install launch files
install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
