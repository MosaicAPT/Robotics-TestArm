FROM dokken/ubuntu-18.04

# This Dockerfile should provide all the steps to install ros and run a robotic arm software
# Setup to install ROS
RUN sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
RUN sudo apt install curl -y
RUN curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
RUN sudo apt update

# Install ROS
RUN sudo apt install ros-melodic-desktop-full -y

# Setup Bashrc
RUN echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
RUN /bin/bash -c "source ~/.bashrc"

# Install important packages
RUN sudo apt install python-rosdep python-rosinstall \
    python-rosinstall-generator python-wstool build-essential -y

RUN sudo apt intall python3-pip -y
RUN pip3 install bosdyn-client bosdyn-mission bosdyn-api bosdyn-core cython empy
# mkdir catkin_ws/src
# git clone https://github.com/clearpathrobotics/spot_ros.git
# git clone https://github.com/ros/geometry2 --branch 0.6.5
# cd catkin_ws
# rosdep install --from-paths src --ignore-src -y
# catkin_make --cmake-args -DCMAKE_BUILD_TYPE=Release -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.6m -DPYTHON_LIBRARY=/usr/lib/x86_64-linux-gnu/libpython3.6m.so


# ROS dep
RUN sudo apt install python-rosdep -y
RUN sudo rosdep init
RUN rosdep update
