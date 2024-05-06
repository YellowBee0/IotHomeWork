#include <sstream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
	//初始化节点
	ros::init(argc, argv, "publisher");
	//创建节点句柄
	ros::NodeHandle n;
	//创建publisher，发布话题[/turtle1/cmd_vel]，消息类型[geometry_msgs::Twist]
	ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	//设置循环频率
	ros::Rate loop_rate(100);
	while (ros::ok())
	{
		//定义发布的数据
		geometry_msgs::Twist msg;
		//定义linear数据
		geometry_msgs::Vector3 linear;
		linear.x=1;
		linear.y=0;
		linear.z=0;
		//定义angular数据
		geometry_msgs::Vector3 angular;
		angular.x=0;
		angular.y=0;
		angular.z=1;
		msg.linear=linear;
		msg.angular=angular;
		//发布msg数据
		chatter_pub.publish(msg);
		//循环等待回调函数
		ros::spinOnce();
		//按照循环频率延时
		loop_rate.sleep();
	}
	return 0;
}
