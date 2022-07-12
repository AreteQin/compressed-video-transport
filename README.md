# compressed-video-transport
Transport compressed video using ROS image_transport to eliminate latency.

## Do the following three steps on both publisher and receiver

### Install dependencies
#### OpenCV
#### ROS

### Create ROS workspace and download this package
```
mkdir -p ~/video_transport/src
cd video_transport/src
catkin_init_workspace 
cd ..
catkin_make
cd src
git clone https://github.com/AreteQin/compressed-video-transport.git
```

### Make
```
cd ..
catkin_make
```

### Do the following steps on the publisher

### Check the IP address of publisher
`hostname -I`

### Config ROS IP for communication on two machines, if you are using one device, ignore this step
```
export ROS_IP=192.168.2.39 # change the IP according to hostname -I
export ROS_MASTER_URI=http://192.168.2.39:11311 # to make publisher as ROS master
```
### Start ROS master
`roscore`

### open a new terminal and run the publisher
```
source ./devel/setup.bash
export ROS_IP=192.168.2.39 # change the IP according to hostname -I
export ROS_MASTER_URI=http://192.168.2.39:11311 # to make publisher as ROS master
rosrun compressed-video-transport publisher
```

## Do the following steps on the receiver machine

### Check the IP address of receiver
`hostname -I`

### Config ROS IP for communication on two machines, if you are using one device, ignore this step
```
export ROS_IP=192.168.2.40 # change the IP according to hostname -I
export ROS_MASTER_URI=http://192.168.2.39:11311 # to make publisher as ROS master
source ./devel/setup.bash
```

### Run the receiver to subscribe raw image
`rosrun compressed-video-transport publisher _image_transport:=raw`

### Run the receiver to subscribe compressed image
`rosrun compressed-video-transport publisher _image_transport:=compressed`
