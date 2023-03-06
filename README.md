# can send node 
A roapackage to publish sensor_msgs/Imu imu topic and convert it to euler angle, then send data through CAN, aided by https://github.com/ros-industrial/ros_canopen

## usage 

'' sudo ifconfig can0 down ''
'' sudo ip link set can0 type can bitrate 1000000 ''
'' sudo ifconfig can0 up ''
'' roslaunch can_send_node can_send.launch ''