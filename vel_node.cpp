//基础运动控制（编译成功）
// Created by mo806806 on 2026/1/23.
//
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>//速度类型包
int main(int argc, char *argv[])
{
    ros::init(argc,argv,"vel_node");
    ros::NodeHandle n;
    ros::Publisher vel_pub/*发布消息手机*/ = n.advertise/*发布函数*/<geometry_msgs::Twist>("/cmd_vel",10);
    geometry_msgs::Twist msg;//多条消息把消息打包放在msg消息包
    msg.linear.x = 0.1;//平动
    msg.linear.y = 0.1;
    msg.linear.z = 0.1;
    msg.angular.x = 0.1;//转动
    msg.angular.y = 0.1;
    msg.angular.z = 0.1;//消息包的消息具体内容
    ros::Rate loop_rate(10);
    while(ros::ok())
    {
        vel_pub.publish(msg);
        loop_rate.sleep();
    }
    return 0;
}