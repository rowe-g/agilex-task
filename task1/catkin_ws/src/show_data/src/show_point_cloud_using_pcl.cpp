#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/point_cloud.h>                 //pcl点云类型head file
#include <pcl_conversions/pcl_conversions.h> //pcl与ros之间转换head file
#include <pcl/visualization/cloud_viewer.h>

static pcl::visualization::CloudViewer viewer("point cloud"); //set up a pcl window for once (globally)

//receive msg from Lidar ; 用pcl显示出点云图
void laserCallback(sensor_msgs::PointCloud2ConstPtr msg)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr lasercloud(new pcl::PointCloud<pcl::PointXYZ>); //创建pcl类型的点云指针，用于存放ros Lidar msg转换的结果
    pcl::fromROSMsg(*msg, *lasercloud);                                                 //将ros msg转换成pcl点云
    viewer.showCloud(lasercloud);
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "show_point_cloud_using_pcl");
    ros::NodeHandle n;
    // ros::Subscriber pcl_sub = n.subscribe<sensor_msgs::PointCloud2>("/rslidar_points", 10, laserCallback);
    ros::Subscriber pcl_sub = n.subscribe("/rslidar_points", 10, laserCallback);

    ros::spin();
    return 0;
}

/* Refs:
 * https://blog.csdn.net/weixin_43807148/article/details/113850803
 * https://github.com/MRwangmaomao/VSLAM/blob/master/ROS/readme.md
 */