#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "sensor_msgs/Imu.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"can_send");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<sensor_msgs::Imu>("pub_imu_data",10);

    sensor_msgs::Imu imu_msg;
    // learning_vehicle::Frame t_message;
    // t_message.id=161;
    // t_message.dlc=8;
    // t_message.data[0]=1;
    // t_message.data[1]=0;
    // t_message.data[2]=0;
    // t_message.data[3]=0;
    // t_message.data[4]=0;
    // t_message.data[5]=0;
    // t_message.data[6]=0;
    // t_message.data[7]=0;

    ros::Rate rate(10);
    while (ros::ok())
    {
        ROS_INFO("发送成功！");
        pub.publish(imu_msg);
        rate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
