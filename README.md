# lidar2d

*Base configuration for installation and interaction with 2d HOKUYO URG lidar*


**This package is currently WIP**

## Install

Clone this repository into your src folder

Install deps:

```
rosdep install --from-paths src --ignore-src -r -y
```

## Running

To launch the lidar and detect nodes:

```
roslaunch lidar2d lidar2d.launch
```

To launch the interactive interface:

```
roslaunch lidar2d interactive.rviz
```
