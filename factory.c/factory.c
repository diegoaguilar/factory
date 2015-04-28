#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "opencv.h"

int main(int argc, char const *argv[])
{

/*  int DELAY_FOR_PIC = atoi(argv[1]);
  int DELAY_FOR_ROBOT = atoi(argv[2]);
  int x = atoi(argv[3]);
  int y = atoi(argv[4]);
  int width = atoi(argv[5]);
  int height = atoi(argv [6]);
  int threshold = atoi(argv[7]);*/

  wiringPiSetup();
  pinMode(21,OUTPUT);
  pinMode(20,OUTPUT);
  pinMode(26,INPUT);

  int resultado = detector(100, 80, 150, 150,140);

  printf("%d\n", resultado);

  return 0;
}
