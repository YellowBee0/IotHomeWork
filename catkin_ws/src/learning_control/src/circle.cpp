#include "ros/ros.h"
#include "std_msgs/String.h"
#include<geometry_msgs/Twist.h> //运动速度结构体类型  geometry_msgs::Twist的定义文件
 
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "vel_ctrl");  //对该节点进行初始化操作
    ros::NodeHandle n;         //申明一个NodeHandle对象n，并用n生成一个广播对象vel_pub
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ros::Rate loop_rate(10);
    //vel_pub会在主题"/turtle1/cmd_vel"(机器人速度控制主题)里广播geometry_msgs::Twist类型的数据
    //ros::Rate loopRate(2);
    ROS_INFO("draw_circle start...");//输出显示信息
    while(ros::ok())
    {
        geometry_msgs::Twist vel_cmd; //声明一个geometry_msgs::Twist 类型的对象vel_cmd，并将速度的值赋值到这个对象里面

        vel_cmd.linear.x = 2.0;//前后（+-） m/s
        vel_cmd.linear.y = 0.0;  //左右（+-） m/s
        vel_cmd.linear.z = 0.0;
 
        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 1.8; //机器人的自转速度，+左转，-右转，单位是rad/s

        vel_pub.publish(vel_cmd); //赋值完毕后，发送到主题"/turtle1/cmd_vel"。机器人的核心节点会从这个主题接受发送过去的速度值，并转发到硬件体上去执行
	std_msgs::String msg;
        std::stringstream ss;//定义输出流对象
        ss <<vel_cmd;
        msg.data = ss.str();
    	/**
     	* The publish() function is how you send messages. The parameter
     	* is the message object. The type of this object must agree with the type
     	* given as a template parameter to the advertise<>() call, as was done
     	* in the constructor above.
     	*/
        chatter_pub.publish(msg);
        ros::spinOnce();//调用此函数给其他回调函数得以执行(比例程未使用回调函数)
       //loopRate.sleep();
    }
    return 0;
}


