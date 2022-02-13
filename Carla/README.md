# Carla Instruction
## Carla
Download the package using [this list](https://github.com/carla-simulator/carla/blob/master/Docs/download.md). 
The full carla repo is 80 GB while this package is only 6 GB. 
If we are using ROS, please download [0.9.12](https://github.com/carla-simulator/carla/releases/tag/0.9.12/). The latest is 0.9.13. 

Remember to install pygame: 
```
pip3 install pygame
```

To launch the Carla server:
```
./CarlaUE4.sh
```
This launches the whole world, which might lag behind the computer. 
In versions after 0.9.12, to launch the Carla server without the rendering of the whole map (off-screen mode): 
```
./CarlaUE4.sh -RenderOffScreen
```

We need the following command for the previous executible to work: 
```
export PYTHONPATH=$PYTHONPATH:$HOME/<path to carla>/CARLA_0.9.12/PythonAPI/carla/dist/carla-0.9.12-py3.7-linux-x86_64.egg
```
I would recommend putting it in .bashrc

Within directory CARLA_0.9.12/PythonAPI/examples: 
To launch the control screen: 
```
python3 manual_control.py
```
To spawn traffic: 
```
python3 generate_traffic.py
```

## ROS
To have a ROS environment, clone [this repo](https://github.com/carla-simulator/ros-bridge).

carla_ros_bridge has the main launch file (ego vehicle).

carla_spawn_objects has the config (json) for vehicles. 

