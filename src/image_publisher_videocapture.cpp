#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include "helper/FrameLoader.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
   VideoCapture cap(0); // open the default camera
  //  cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  //  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
   
   if(!cap.isOpened()) {
    return -1;
   } // check if we succeeded

  ros::init(argc, argv, "image_publisher_videocapture");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/camera/image_raw", 10000);


  ros::Rate loop_rate(20); // fps
  
  while (nh.ok()) {
    Mat frame;
    cap >> frame;
    cout << "web cam frame size:" << frame.size().width << ", " << frame.size().height << endl;
    cout << "publish new frame" << endl;
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
    pub.publish(msg);
    // imshow("web cam", frame);
    // waitKey(100);
    ros::spinOnce();
    loop_rate.sleep(); // to maintain te fps needed
  }
}