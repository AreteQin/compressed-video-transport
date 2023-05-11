#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pub_cam_node");
    ros::NodeHandle nh;

    cv::VideoCapture capture(0); //read the video from camera
    if (!capture.isOpened()) {
        ROS_ERROR_STREAM("Failed to open video device\n");
        ros::shutdown();
    }

    //image_transport will publish the video that can be compressed
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub_color = it.advertise("D435/color", 1);
//    ros::Publisher pub_color = nh.advertise<sensor_msgs::Image>("/dji_osdk_ros/fpv_camera_images", 1);
    cv::Mat image, depth;

    while (ros::ok()) {
        capture >> image; //load
        if (image.empty()) {
            ROS_ERROR_STREAM("Failed to capture image!");
            ros::shutdown();
        }
//        cv::imshow("pub", image);
//        cv::waitKey(1);
        pub_color.publish(cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg());
    }

    ros::spin();
}
