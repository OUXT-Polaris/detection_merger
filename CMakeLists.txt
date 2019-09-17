cmake_minimum_required(VERSION 2.8.3)
project(detection_merger)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  message_filters
  nodelet
  pluginlib
  roscpp
  vision_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES detection_merger
  CATKIN_DEPENDS message_filters nodelet pluginlib roscpp vision_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(detection_merger src/detection_merger.cpp)
target_link_libraries(detection_merger ${catkin_LIBRARIES})
class_loader_hide_library_symbols(detection_merger)

add_executable(detection_merger_node src/detection_merger_node.cpp)
target_link_libraries(detection_merger_node ${catkin_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(
  TARGETS detection_merger_node detection_merger
  RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

foreach(dir config launch)
  install(DIRECTORY ${dir}/
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/${dir})
endforeach(dir)