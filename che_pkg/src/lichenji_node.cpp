//
// Created by mo806806 on 2026/2/9.
//
#include <cmath>
#include <ctime>
#include <bits/locale_classes.h>
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <std_msgs/Float32.h>
#include <math.h>
double g_x=0.0, g_y=0.0,g_yaw=0;
void zuoqian_callback (std_msgs::Float32 msg)
{
    static  double a = msg.data;
}
void zuohou_callback (std_msgs::Float32 msg)
{
    static  double b = msg.data;
}
void youqian_callback (std_msgs::Float32 msg)
{
   static  double c = msg.data;
}
void youhou_callback (std_msgs::Float32 msg)
{
    static  double d = msg.data;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"lichenji");
    ros::NodeHandle n;
    ros::Subsctf.hriber sub = n.subscribe("zuoqian", 10, zuoqian_callback);
    ros::Subscriber sub2 = n.subscribe("youqian", 10, youqian_callback);
    ros::Subscriber sub3 = n.subscribe("zuohou", 10, zuohou_callback);
    ros::Subscriber sub4 = n.subscribe("youhou", 10, youhou_callback);
    ros::Publisher odom_sub = n.advertise<nav_msgs::Odometry>("odom",10);
    ros::Time time = ros::Time::now();
    ros::Publisher odom_pub;
    tf::TransformBroadcaster br;//里程计发布
    while (ros::ok())
    {
        double vx =(a+b+c+d)/4.0*0.05;
        double vy =(b-a+c-d)/4.0*0.05;
        double vz = (c+d-a-a)/4.0;
        ros::Time now = ros::Time::now();
        double t = (now-time).toSec();
        time = now;
        double vxx =((vx*cos(g_yaw))-(vy*sin(g_yaw)))*t;
        double vyy =((vy*cos(g_yaw))+(vx*sin(g_yaw)))*t;
        g_x += vxx;
        g_y += vyy;
        g_yaw = vz*t;
        tf::Transform odom_tf;
        odom_tf.setOrigin(tf::Vector3(g_x,g_y,0));//三为向量类TF库固定初坐标系
        tf::Quaternion odom_quat;//四元数倒入TF四元数写入odom_quat
        odom_quat.setRPY(0,0,g_yaw);//改为欧拉角
        odom_tf.setRotation(odom_quat);//方向角变寺院数

        br.sendTransform(tf::StampedTransform(odom_tf, time, "odom", "base_link"));//发布带时间的坐标变换
        nav_msgs::Odometry odom;
        odom.header.frame_id = "odom";
        odom.child_frame_id = "base_link";
        odom.header.stamp = time;
        odom.pose/*带协方差位资*/.pose/*位资*/.position.x = g_x;
        odom.pose.pose.position.y = g_y;
        odom.pose.pose.position.z = 0.0;

        odom.pose.pose.orientation = tf::createQuaternionMsgFromYaw(g_yaw);//角度改为4元数发布
        odom_pub.publish(odom);



    }


    return 0;

}