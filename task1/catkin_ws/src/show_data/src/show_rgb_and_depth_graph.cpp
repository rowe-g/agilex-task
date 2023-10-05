#include <ros/ros.h> //ros dependency
#include <cv_bridge/cv_bridge.h>         //ros->opencv
#include <sensor_msgs/image_encodings.h> //get figure
#include <opencv2/highgui/highgui.hpp> // GUI
#include <string>

static const std::string RGB_WINDOW = "RGB Image";
static const std::string DEPTH_WINDOW = "Depth Image";

void ImageConverte_and_Show(const sensor_msgs::ImageConstPtr &msg, const std::string &title)
{
    cv_bridge::CvImagePtr cv_image_ptr; //用来存放ros image msg转换成的OpenCV格式image msg
    cv_image_ptr = cv_bridge::toCvCopy(msg); //set coding type "auto"
    cv::imshow(title, cv_image_ptr->image);
    if (cv::waitKey(1) == 27) //set awaiting time as 1ms
    {
        ros::shutdown();
        cv::destroyAllWindows();
    } //press "esc" to quit()
    return;
}
void color_show(const sensor_msgs::ImageConstPtr &msg)
{
    ImageConverte_and_Show(msg, RGB_WINDOW);
    return;
}
void depth_show(const sensor_msgs::ImageConstPtr &msg)
{
    ImageConverte_and_Show(msg, DEPTH_WINDOW);
    return;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "show_rgb_and_depth_graph");
    ros::NodeHandle n;

    //set up two windows
    cv::namedWindow(RGB_WINDOW);
    cv::namedWindow(DEPTH_WINDOW);

    ros::Subscriber camera_color_sub = n.subscribe("/camera/color/image_raw", 10, color_show);
    ros::Subscriber camera_depth_sub = n.subscribe("/camera/depth/image_rect_raw", 10, depth_show);

    ros::spin();
    return 0;
}