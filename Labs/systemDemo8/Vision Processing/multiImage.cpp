#include "opencv2/opencv.hpp"
#include "string.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#define EPSILON .001
using namespace cv;

bool compareDoubles2(double a, double b)
{
  double diff = a-b;
  return (diff < EPSILON && -diff < EPSILON);

}

double max2(double a, double b)
{
	if(a<b)
		return b;
	else
		return a;
}

double max4(double a, double b, double c, double d)
{
	double m1 = max2(a,b);
    	double m2 = max2(c,d);
	return max2(m1,m2);
}


int main(int argv, char ** argc)
{
	VideoCapture cap(0);
	if(!cap.isOpened())
		return -1;
        std::string templateSource = "temp1c.png";
	//std::string templateDest = "temp.png";
	Mat gray;
        Mat black;
	Mat frame;
	cap >> frame;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	threshold(gray, black, 50, 255, THRESH_BINARY);
	pid_t pid = getpid(); //parent

	namedWindow("black", 1);
	if(fork() == 0)
	{
		for(;;)
		{
		
			cap >> frame;
			cvtColor(frame, gray, COLOR_BGR2GRAY);
			threshold(gray, black, 50, 255, THRESH_BINARY);
		

			imshow("black", black);
			if(waitKey(30) >= 0)
			{
				kill(pid, 3);
				break;
			}

		}
		exit(0);;
	}
	else
	{
		Mat temp1 = imread(templateSource.c_str(), IMREAD_GRAYSCALE );
	        Mat temp2,temp3,temp4;
        	flip(temp1,temp2, 0);
		flip(temp1,temp3, 1);
		flip(temp1,temp4, -1);
		int orientation = 0;
		Mat match1,match2,match3,match4;
        	double e1, e2, e3, e4;
		for(;;)
		{
			matchTemplate(black,temp1, match1,TM_CCOEFF);
        	        minMaxLoc(match1, NULL, &e1, NULL, NULL);                

			matchTemplate(black,temp2, match2,TM_CCOEFF);
        	        minMaxLoc(match1, NULL, &e2, NULL, NULL);                

			matchTemplate(black,temp3, match3,TM_CCOEFF);
        	        minMaxLoc(match1, NULL, &e3, NULL, NULL);                

			matchTemplate(black,temp4, match4,TM_CCOEFF);
        	        minMaxLoc(match1, NULL, &e4, NULL, NULL);                

			double best = max4(e1,e2,e3,e4);
		
			if(best < 100000000)
				orientation = 0;
			else if(compareDoubles2(best,e1))
				orientation = 1;
			else if(compareDoubles2(best,e2))
				orientation = 2;
			else if(compareDoubles2(best,e3))
				orientation = 3;
			else if(compareDoubles2(best,e4))
				orientation = 4;
		}
	}
	return 0;

}
