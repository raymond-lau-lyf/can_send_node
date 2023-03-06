#include "ros/ros.h"
#include "can_msgs/Frame.h"
#include "sensor_msgs/Imu.h"

void Imu_msg_update(sensor_msgs::Imu *imu_msg_p);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"can_send");
    ros::NodeHandle nh;
    ros::Publisher pub=nh.advertise<sensor_msgs::Imu>("pub_imu_data",10);

    sensor_msgs::Imu imu_msg;
    imu_msg.header.seq=0;
    imu_msg.header.stamp=ros::Time::now();
    imu_msg.header.frame_id="imu";
    imu_msg.orientation.w=-0.5;
    imu_msg.orientation.x=0.5;
    imu_msg.orientation.y=0.5;
    imu_msg.orientation.z=0.5;
    ros::Rate rate(500);
    while (ros::ok())
    {
        ROS_INFO("发送成功！");
        Imu_msg_update(&imu_msg);
        pub.publish(imu_msg);
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}

void Imu_msg_update(sensor_msgs::Imu *imu_msg_p){
    imu_msg_p->header.stamp=ros::Time::now();
    imu_msg_p->header.frame_id="imu";
    imu_msg_p->orientation.w=-0.5;
    imu_msg_p->orientation.x=0.5;
    imu_msg_p->orientation.y=0.5;
    imu_msg_p->orientation.z=0.5;
}


// std_msgs/Header header
//   uint32 seq  
//   time stamp   // 时间戳
//   string frame_id   
// geometry_msgs/Quaternion orientation   // 姿态
//   float64 x
//   float64 y
//   float64 z
//   float64 w
// float64[9] orientation_covariance   // 姿态协方差
// geometry_msgs/Vector3 angular_velocity   // 角速度
//   float64 x
//   float64 y
//   float64 z
// float64[9] angular_velocity_covariance   // 角速度协方差
// geometry_msgs/Vector3 linear_acceleration  // 线加速度
//   float64 x
//   float64 y
//   float64 z
// float64[9] linear_acceleration_covariance   // 线加速度协方差
