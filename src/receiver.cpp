#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
//#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class ImageReceiver {
private:
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    std::string OPENCV_WINDOW;
public:
    ImageReceiver(const std::string &topic_name)
            : it_(nh_) {
        OPENCV_WINDOW = topic_name;
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe(OPENCV_WINDOW, 1,
                                   &ImageReceiver::imageCb, this);
        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageReceiver() {
        cv::destroyWindow(OPENCV_WINDOW);
    }

    void imageCb(const sensor_msgs::ImageConstPtr &msg) {
        cv_bridge::CvImagePtr cv_ptr;
        try {
            cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        }
        catch (cv_bridge::Exception &e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        cv::waitKey(1);
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "rgb_receiver");
    ImageReceiver color("D435/color");
    ros::spin();
    return 0;
}