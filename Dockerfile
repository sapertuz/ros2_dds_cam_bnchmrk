FROM ros:humble-ros-base

# Install dependencies
RUN apt-get update && apt-get install -y \
    python3-pip \
    ros-humble-rmw-cyclonedds-cpp \
    ros-humble-image-transport \
    ros-humble-rqt-image-view \
    ros-humble-rosbag2* \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Optional: for analyzing performance
RUN pip3 install pandas matplotlib

# Create workspace
RUN mkdir -p /ws/src
WORKDIR /ws

# Copy package into container at build time
COPY . /ws/src/ros2_dds_camera_benchmark

# Build ROS 2 workspace
RUN . /opt/ros/humble/setup.sh && \
    colcon build --symlink-install

# Set entrypoint
SHELL ["/bin/bash", "-c"]
ENTRYPOINT ["source /opt/ros/humble/setup.bash && source /ws/install/setup.bash && bash"]
