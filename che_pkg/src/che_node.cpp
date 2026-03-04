//
// Created by mo806806 on 2026/2/4.
//
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>//速度类型包
#include <stdio.h>
#include <termios.h>
int GetCh()
{
    static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
    int c = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
    return c;
}
int main(int argc, char **argv)
{
    ros::init(argc,argv,"che_node");
    ros::NodeHandle nh;
    ros::Publisher vel_pub/*发布消息手机*/ = nh.advertise/*发布函数*/<geometry_msgs::Twist>("/cmd_vel",10);
    printf("键盘控制WPR机器人： \n");
    printf("w - 向前加速 \n");
    printf("s - 向后加速 \n");
    printf("a - 向左加速 \n");
    printf("d - 向右加速 \n");
    printf("q - 左旋加速 \n");
    printf("e - 右旋加速 \n");
    printf("空格 - 刹车 \n");
    printf("x - 退出 \n");
    printf("------------- \n");

    geometry_msgs::Twist msg;//多条消息把消息打包放在msg消息包
    msg.linear.x = 0.0;//平动
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;//转动
    msg.angular.y = 0.0;
    msg.angular.z = 0.0;//消息包的消息具体内容

  while(nh.ok())
  {
    int cKey = GetCh();
    if(cKey=='w')
    {
      msg.linear.x += 0.1;
      if(msg.linear.x > 0.1*3)
        msg.linear.x = 0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='s')
    {
      msg.linear.x += -0.1;

      if(msg.linear.x < -0.3)
        msg.linear.x = -0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='a')
    {
      msg.linear.y += 0.1;
      if(msg.linear.y > 0.3)
        msg.linear.y = 0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='d')
    {
      msg.linear.y += -0.1;
      if(msg.linear.y < -0.3)
        msg.linear.y = -0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='q')
    {
      msg.angular.z += 0.1;
      if(msg.angular.z > 0.3)
        msg.angular.z = 0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='e')
    {
      msg.angular.z += -0.1;
      if(msg.angular.z < -0.3)
        msg.angular.z = -0.3;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey==' ')
    {
      msg.linear.x = 0;
      msg.linear.y = 0;
      msg.angular.z = 0;
      vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
    }
    else if(cKey=='x')
    {
      msg.linear.x = 0;
      msg.linear.y = 0;
      msg.angular.z = 0;
     vel_pub.publish(msg);
      printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",msg.linear.x,msg.linear.y,msg.angular.z);
      printf("退出！ \n");
      return 0;
    }
    else
    {
       printf(" - 未定义指令 \n");
    }

  }
    return 0;

}