## 🐳 Docker Usage

To build the container:

```bash
docker build -t ros2_dds_benchmark .
```

To run the container with access to your bag files and logs:

```bash
docker run -it --rm --net=host \
  -v $(pwd)/bags:/ws/bags \
  -v $(pwd)/logs:/ws/logs \
  ros2_dds_benchmark
```

Inside the container, source the workspace:

```bash
source /opt/ros/humble/setup.bash
source /ws/install/setup.bash
ros2 launch launch/camera_dds_benchmark.launch.py
```

You can modify the Dockerfile to add tools, mount devices, or run analysis scripts directly.
