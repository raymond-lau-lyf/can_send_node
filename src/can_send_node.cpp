#include "can_send_node/can_send_node.h"

void Imu_msg_update(can_msgs::Frame *send_msg_p);
void ImuCallback(const sensor_msgs::ImuConstPtr &imu_msg){

}
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "can_send");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::Imu>("/sub_imu_data", 10,ImuCallback);
    ros::Publisher pub_imu = nh.advertise<can_msgs::Frame>("pub_can_imu_data", 10);

    sensor_msgs::Imu imu_msg;
    imu_msg.header.seq = 0;
    imu_msg.header.stamp = ros::Time::now();
    imu_msg.header.frame_id = "imu";
    imu_msg.orientation.w = -0.5;
    imu_msg.orientation.x = 0.5;
    imu_msg.orientation.y = 0.5;
    imu_msg.orientation.z = 0.5;

    can_msgs::Frame can_imu_msg;
    can_imu_msg.id= 0x001;
    can_imu_msg.dlc=8;
    can_imu_msg.data[0]=1;
    can_imu_msg.data[1]=0;
    can_imu_msg.data[2]=1;
    can_imu_msg.data[3]=0;
    can_imu_msg.data[4]=1;
    can_imu_msg.data[5]=0;
    can_imu_msg.data[6]=1;
    can_imu_msg.data[7]=0;

    ros::Rate rate(200);
    while (ros::ok()) {
        ROS_INFO("Sending");
        Imu_msg_update(&can_imu_msg);
        pub_imu.publish(can_imu_msg);
        rate.sleep();
        ros::spinOnce();
    }

    return 0;
}

void Imu_msg_update(can_msgs::Frame *send_msg_p) {
    send_msg_p->data[0]=1;
    send_msg_p->data[1]=0;
    send_msg_p->data[2]=1;
    send_msg_p->data[3]=0;
    send_msg_p->data[4]=1;
    send_msg_p->data[5]=0;
    send_msg_p->data[6]=1;
    send_msg_p->data[7]=0;
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
