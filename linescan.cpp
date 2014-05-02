#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main (int argc, char* argv[])
{
  if (argc < 3) {
    cout << "Something's wrong with the provided parameters..." << endl << endl;
    cout << "Usage: ./lineScan   streamType streamLocation" << endl << endl;
    cout << "streamType - 0 = file, 1 = camera" << endl;
    cout << "streamLocation - path to the video stream" << endl;

    return 0;
  }
 
  int streamType = atoi(argv[1]);
  string videoStreamLocation = argv[2];
    
  VideoCapture vcap;
  Mat image;
 
  if (streamType == 0) {  
    if(!vcap.open(videoStreamLocation)) {
      cout << "Error opening video stream" << endl;

      return 0;
    }
  }
  else {
    if(!vcap.open(atoi(argv[2]))) {
      cout << "Error opening video stream" << endl;

      return 0;
    }    
    
    vcap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    vcap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
  }

  namedWindow ("line", CV_WINDOW_AUTOSIZE);
    
  long frame = 0;

  Mat lineImage = Mat::zeros(Size(640, 480), CV_8UC3);
  Mat combinedImage = Mat::zeros(Size(1280, 480), CV_8UC3);
   
  while(true) {
    if(!vcap.read(image)) {
      cout << "No frame" << std::endl;
      return 0;
    }
    
    if (streamType == 0) {
      Mat imageScaled(Size(640, 480), image.type());
    
      resize(image, image, imageScaled.size());
    }
  
    line(image, Point(image.cols / 2 + 1, 0),
                Point(image.cols / 2 + 1, image.rows - 1),
                Scalar(255, 0, 128));

    if (frame >= lineImage.cols) {
      lineImage.colRange(1, lineImage.cols - 1).copyTo(lineImage.colRange(0, lineImage.cols - 2));
      image.col(image.cols / 2).copyTo(lineImage.col(lineImage.cols - 2));
    }
    else {
      image.col(image.cols / 2).copyTo(lineImage.col(frame));
    }
    
    image.colRange(0, image.cols - 1).copyTo(combinedImage.colRange(0, image.cols - 1));
    lineImage.colRange(0, image.cols - 1).copyTo(combinedImage.colRange(image.cols, combinedImage.cols - 1));
  
    imshow("line", combinedImage);
    
    frame ++;
    
    stringstream ss;

    ss.fill('0');
    ss.width(4);

    ss << frame << ".jpg";
    
    /*imwrite(ss.str().c_str(), combinedImage);*/
        
    if(waitKey(1) >= 0) waitKey(0);
  }   
}
