cmake_minimum_required(VERSION 3.0.2)
project(Robotics_TestArm)

# Get the information about this package's buildtime dependencies
find_package(catkin REQUIRED
 COMPONENTS 
    roscpp 
    std_msgs 
    sensor_msgs 
    moveit_core
    moveit_ros_planning
    moveit_ros_planning_interface)

include_directories(${catkin_INCLUDE_DIRS})

# Declare the message files to be built
add_message_files(FILES 
  ArmJointState.msg 
)

# Declare the service files to be built
#   add_service_files(FILES
#     MyService.srv
#   )

# Actually generate the language-specific message and service files
generate_messages(DEPENDENCIES std_msgs sensor_msgs)

# Declare that this catkin package's runtime dependencies
catkin_package(
  CATKIN_DEPENDS 
    roscpp 
    std_msgs 
    sensor_msgs 
    moveit_core
    moveit_ros_planning_interface
)

# define executable using MyMessage1 etc.
add_executable(step_converter src/joint_state_steps.cpp)
add_dependencies(step_converter ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(step_converter
   ${catkin_LIBRARIES}
 )

# define executable not using any messages/services provided by this package
#   add_executable(does_not_use_local_messages_program src/main.cpp)
#   add_dependencies(does_not_use_local_messages_program ${catkin_EXPORTED_TARGETS})

# install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})