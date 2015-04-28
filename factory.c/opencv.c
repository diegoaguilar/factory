#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv.h"

using namespace cv;
using namespace std;

int detector(int x, int y, int width, int height, int thresholdValue) {

  Mat img;
  Rect r;
  vector<Mat> channels;
  r = Rect(x,y,width,height);

  CvCapture* capture = cvCaptureFromCAM(0);
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,640);
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,480);

  if ( !capture ) {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
                   }

  img = Mat(cvQueryFrame( capture ));
  cvtColor(img,img,CV_RGB2GRAY);
  threshold(img, img, 127, 255, THRESH_BINARY);
  //80 160 100 100
  // 100 115 120 120
  // 100 80 150 150

  // ROI
  Mat roiImage = img(r);
  split(roiImage,  channels);
  Scalar m = mean(channels[0]);
  float media = m[0];
  printf("Media: %f\n", media);

  if (media < thresholdValue) {
    // LATA
    return LATA;
  }

  else {
    return BOTELLA;
  }
}
