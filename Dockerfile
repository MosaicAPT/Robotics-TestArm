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

# ROS dep
RUN sudo apt install python-rosdep -y
RUN sudo rosdep init
RUN rosdep update
