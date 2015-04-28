#include <wiringPi.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv.h"
#define LATA 100
#define BOTELLA 200

using namespace cv;
using namespace std;

int detector(int x, int y, int width, int height, int thresholdValue);

int main(int argc, char const *argv[])
{

  CvCapture* capture = cvCaptureFromCAM(0);
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,640);
  cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,480);

  wiringPiSetup();
  pinMode(21,OUTPUT);
  pinMode(20,OUTPUT);
  //digitalWrite(20,LOW); //digitalWrite(21,LOW);
  int DELAY_FOR_PIC = atoi(argv[1]);
  int DELAY_FOR_ROBOT = atoi(argv[2]);
  int x = atoi(argv[3]);
  int y = atoi(argv[4]);
  int width = atoi(argv[5]);
  int height = atoi(argv [6]);
  int thresholdValue = atoi(argv[7]);

  int nonstop = 1;

  do {
    //digitalWrite(20,LOW);
    //digitalWrite(21,HIGH);
    delay(DELAY_FOR_PIC);

    //int resultado = detector(100, 80, 150, 150,140);
    //digitalWrite(20,LOW); //digitalWrite(21,LOW);
    int resultado = detector(x,y,width,height,thresholdValue,capture);
    printf("%d\n", resultado);

    if (resultado == LATA) {
      //digitalWrite(20,HIGH);
      //digitalWrite(21,LOW);
    }

    else {
      //digitalWrite(20,HIGH);
      //digitalWrite(21,HIGH);
    }

    delay(DELAY_FOR_ROBOT);
    //digitalWrite(20,LOW);
    //digitalWrite(21,LOW);
  }
  while(nonstop);

  return 0;
}

int detector(int x, int y, int width, int height, int thresholdValue,capture) {

  Mat img;
  Rect r;
  vector<Mat> channels;
  r = Rect(x,y,width,height);

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
