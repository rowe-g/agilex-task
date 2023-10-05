#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
//#include <math.h>
using namespace std;

double t_recent; double s;

void distanceCallback(const nav_msgs::Odometry::ConstPtr &msg)
{
    double dt; double ds; double v;
    //receive "/odom", obtain the velocity and stamping time
    dt = msg->header.stamp.toSec() - t_recent;
    t_recent = msg->header.stamp.toSec();

    v = msg->twist.twist.linear.x;
    if (dt > 1 || dt < 0)
    { //discard the far-responding msg
        dt = 0;
    }
    ds = v * dt * 1.0504; //ds=v*dt
    s += ds;
    ROS_INFO("v=%0.6fm/s,s=%0.6fm", v, s);
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "speed_subscriber");
    ros::NodeHandle n;

    s = 0;
    t_recent = ros::Time::now().toSec();
    ROS_INFO("init s=%f,t_recent=%0.6fs", s, t_recent);
    ros::Subscriber speed_sub = n.subscribe("/odom", 10, distanceCallback);
    ros::spin();
    return 0;
}
/*
usage:
```bash
roslaunch scout_bringup open_rslidar.launch
```
init the Lidar to receive msg
*/