//订阅激光雷达消息并发布速度控制（编译成功）
// Created by mo806806 on 2026/1/23.
//

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>/*激光雷达传感器消息包*/
#include <geometry_msgs/Twist.h>//速度类
ros::Publisher vel_pub;//声明，使变为全局变量
int a=0;
void LidarCallback(const sensor_msgs::LaserScan msg)
{
    float fMidDist = msg.ranges[180]/*这个是消息包中保存测距信息的数组360项中的第180项，1度1项*/ ;
    ROS_INFO("%f\n",fMidDist);/*输出*/
    geometry_msgs::Twist su;//速度消息包
    if (a>0)
    {
        a--;
        return;
    }
    if (fMidDist <1.5)
    {
        su.angular.z = 0.3;a=50;
    }else
    {
        su.linear.x = 0.3;
    }
    vel_pub.publish(su);//发布
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");//让INFO可以输出
     ros::init(argc,argv,"lidar_node");
    ros::NodeHandle n;
    ros::Subscriber ludar_sub =n.subscribe("/scan",10,&LidarCallback/*回调函数*/);
    vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel",10);//发布
    ros::spin();/*保持节点处于运行状态*/
    return 0;
}