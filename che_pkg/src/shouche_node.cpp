//
// Created by mo806806 on 2026/2/4.
//
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>/*速度类型包*/
#include  <math.h>
#include <std_msgs/Float32.h>
void che_callback (geometry_msgs::Twist msg)
{
    ros::NodeHandle n;
    ros::Publisher pub/*发送消息的工具（能在话题里发消息的手机）*/ = n.advertise<std_msgs::Float32>("zuoqian",10);
    ros::Publisher pub2/*发送消息的工具（能在话题里发消息的手机）*/ = n.advertise<std_msgs::Float32>("youqian",10);
    ros::Publisher pub3/*发送消息的工具（能在话题里发消息的手机）*/ = n.advertise<std_msgs::Float32>("zuohou",10);
    ros::Publisher pub4/*发送消息的工具（能在话题里发消息的手机）*/ = n.advertise<std_msgs::Float32>("youhou",10);
    std_msgs::Float32 zuoqian;
    std_msgs::Float32 youqian;
    std_msgs::Float32 zuohou;
    std_msgs::Float32 youhou;
    float a=msg.linear.x,b=msg.linear.y;
    zuoqian.data=(a-b)/0.05;
    youqian.data=(a+b)/0.05;
    zuohou.data=(a+b)/0.05;
    youhou.data=(a-b)/0.05;
    pub.publish(zuoqian);
    pub2.publish(youqian);
    pub3.publish(zuohou);
    pub4.publish(youhou);
 
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"shouche_node");//初始化
    ros::NodeHandle nh;//ROS的管理者，负责在我们的需求给他
    ros::Subscriber sub/*发送消息的工具（能在话题里发消息的手机）*/  = nh.subscribe/*订阅函数*/("/cmd_vel"/*订阅话题名称*/,10/*缓存长度*/,che_callback/*回调函数命名*/);
    while(ros::ok())
    {
        ros::spinOnce();//保证可以一直接受消息而不是困于while循环
    }
    return 0;
}