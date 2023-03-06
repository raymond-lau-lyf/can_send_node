#include "can_send_node/can_send_node.h"

unsigned char data_updated = false;
sensor_msgs::Imu imu_msg;
float roll, pitch, yaw;

static void toEulerAngle(const double x, const double y, const double z, const double w) {
    // roll (x-axis rotation)
    double sinr_cosp = +2.0 * (w * x + y * z);
    double cosr_cosp = +1.0 - 2.0 * (x * x + y * y);
    roll = atan2(sinr_cosp, cosr_cosp);
    // pitch (y-axis rotation)
    double sinp = +2.0 * (w * y - z * x);
    if (fabs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp);  // use 90 degrees if out of range
    else
        pitch = asin(sinp);
    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * (w * z + x * y);
    double cosy_cosp = +1.0 - 2.0 * (y * y + z * z);
    yaw = atan2(siny_cosp, cosy_cosp);
}

void Imu_msg_update(can_msgs::Frame *send_msg_p);
void ImuCallback(const sensor_msgs::ImuConstPtr &imu_msg) {
    toEulerAngle(imu_msg->orientation.x, imu_msg->orientation.y, imu_msg->orientation.z, imu_msg->orientation.w);
    data_updated = true;
}
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "can_send");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe<sensor_msgs::Imu>("/imu/data_raw", 10, ImuCallback);
    ros::Publisher pub_imu = nh.advertise<can_msgs::Frame>("/pub_can_imu_data", 10);

    can_msgs::Frame can_imu_msg;
    can_imu_msg.id = 0x001;
    can_imu_msg.dlc = 8;

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

bool start = true;
unsigned char c[sizeof(float)];
void Imu_msg_update(can_msgs::Frame *send_msg_p) {
    if (start) {
        send_msg_p->data[0] = 's';
        memcpy(c, &roll, sizeof(roll));
        send_msg_p->data[1] = c[0];
        send_msg_p->data[2] = c[1];
        send_msg_p->data[3] = c[2];
        send_msg_p->data[4] = c[3];
        memcpy(c, &pitch, sizeof(pitch));
        send_msg_p->data[5] = c[0];
        send_msg_p->data[6] = c[1];
        send_msg_p->data[7] = c[2];
        start = false;
    } else {
        memcpy(c, &pitch, sizeof(pitch));
        send_msg_p->data[0] = c[3];
        memcpy(c, &yaw, sizeof(yaw));
        send_msg_p->data[1] = c[0];
        send_msg_p->data[2] = c[1];
        send_msg_p->data[3] = c[2];
        send_msg_p->data[4] = c[3];
        send_msg_p->data[5] = data_updated;
        send_msg_p->data[6] = 'e';
        start = true;
    }
    data_updated = false;  // set upd flag to false
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
