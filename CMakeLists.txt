cmake_minimum_required(VERSION 3.0)
project(lidar2d)

add_definitions(-std=c++11)
find_package(catkin REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  rospy
  dynamic_reconfigure
)

#add dynamic reconfigure api
generate_dynamic_reconfigure_options(
    cfg/Detect.cfg
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES lidar2d
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)

###########
## BUILD ##
###########

include_directories(
  ${catkin_INCLUDE_DIRS}
)

# detect
add_executable(detect src/detect.cpp)
add_dependencies(detect ${PROJECT_NAME}_gencfg)
target_link_libraries(detect ${catkin_LIBRARIES})
