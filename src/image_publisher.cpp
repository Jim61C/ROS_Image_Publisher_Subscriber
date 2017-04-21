#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include "helper/FrameLoader.h"

using namespace std;

int main(int argc, char** argv)
{
  if (argc < 3) {
    printf("Usage: %s input_dir data_source_name \n", argv[0]);
    exit(-1);
  }
  string input_dir = argv[1];
  string data_source_name = argv[2];
  int start_frame = 1;
  int end_frame = 2500;
  int step = 1;
  FrameLoader loader(input_dir, data_source_name, start_frame, end_frame, step);
  vector<Mat> frames;
  cout << "loading input_dir: " << input_dir << "from dataset: " << data_source_name << " ..." <<endl;
  loader.load(frames);
  cout << "finished loading, start publishing..." << endl;

  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/camera/image_raw", end_frame-start_frame);


  ros::Rate loop_rate(10);
  int i = 0;
  while (nh.ok() && i < frames.size()) {
    cout << "publish new frame" << endl;
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frames[i]).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    i++;
  }
}