// Designed with inspiration from the following examples:
// https://docs.opencv.org/2.4/doc/tutorials/imgproc/imgtrans/canny_detector/canny_detector.html#canny-detector 
// http://wiki.ros.org/image_transport
// http://wiki.ros.org/cv_bridge/Tutorials
//---------------------------------------------------

#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <image_transport/image_transport.h>

using namespace std;
using namespace cv;
    
image_transport::Subscriber img_sub; 
image_transport::Publisher img_pub;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
  cv_bridge::CvImagePtr cv_ptr;
  try
  {
    cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& ex)
  {
    ROS_ERROR("CV_bridge exception: %s", ex.what());
  }

  int low_threshold = 40;
  int ratio = 3; 
  int kernel_size = 3;

  Mat img;
  cvtColor(cv_ptr->image, img, CV_BGR2GRAY); // Convert to gray-scale image
  blur( img, img, Size(3,3));// Reduce noise with a kernel of 3x3
  Canny(img, img, low_threshold, low_threshold*ratio, kernel_size);
  cvtColor(img, img, CV_GRAY2BGR);

  cv_bridge::CvImage imgBridge = cv_bridge::CvImage(std_msgs::Header(), sensor_msgs::image_encodings::RGB8, img);
  sensor_msgs::Image canny_image;
  imgBridge.toImageMsg(canny_image);
  img_pub.publish(canny_image);

}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "canny_edge_my_face");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);   
  img_sub = it.subscribe("/cv_camera/image_raw", 1, imageCallback);; 
  img_pub = it.advertise("/ryb_camera/canny_edge",1);

  ros::spin();
}