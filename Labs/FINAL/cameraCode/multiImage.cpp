#include "opencv2/opencv.hpp"
#include "string.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>


#define BAUDRATE B9600
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1


#define EPSILON .001
using namespace cv;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
Mat black;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
bool quit = false;
VideoCapture cap(0);
int fd, res;
termios oldtio,newtio;
char buf[255];


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

double max4(double a, double b , double c, double d)
{
	double m1 = max2(a,b);
    	double m2 = max2(c,d);
	return max2(m1,m2);
}

void * fetchImLoop(void *) {

	Mat gray;
	Mat frame;
	namedWindow("black", 1);
	for(;;)
	{
		
		cap >> frame;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		pthread_mutex_lock(&mutex1);
		threshold(gray, black, 70, 255, THRESH_BINARY);
		pthread_mutex_unlock(&mutex1);

		imshow("black", black);
		if(waitKey(30) >= 0)
		{
			//send message to kill thread
			pthread_mutex_lock(&mutex2);
			quit = true;
			pthread_mutex_unlock(&mutex2);
			break;
		}

	}
}


void * computeMatchLoop(void *) {
	std::string templateSource1 = "temp1L.png";
	std::string templateSource2 = "temp2L.png";
	std::string templateSource3 = "temp3L.png";
	std::string templateSource4 = "temp4L.png";
	Mat temp1 = imread(templateSource1.c_str(), IMREAD_GRAYSCALE );
	Mat temp2 = imread(templateSource2.c_str(), IMREAD_GRAYSCALE );
	Mat temp3 = imread(templateSource3.c_str(), IMREAD_GRAYSCALE );
	Mat temp4 = imread(templateSource4.c_str(), IMREAD_GRAYSCALE );
	unsigned char orientation = 0;
	Mat match1,match2,match3,match4;
        double e1, e2, e3, e4;
        Mat blackWhite; //copy of black
	for(;;)
	{
		//Sync
		//read(fd, buf, 1); //block until char received
		
		//update to current frame
		pthread_mutex_lock(&mutex1);
		blackWhite = black.clone();
		pthread_mutex_unlock(&mutex1);

		matchTemplate(blackWhite,temp1, match1,TM_CCOEFF);
                minMaxLoc(match1, NULL, &e1, NULL, NULL);                

		matchTemplate(blackWhite,temp2, match2,TM_CCOEFF);
       	        minMaxLoc(match2, NULL, &e2, NULL, NULL);                

		matchTemplate(blackWhite,temp3, match3,TM_CCOEFF);
       	        minMaxLoc(match3, NULL, &e3, NULL, NULL);                

		matchTemplate(blackWhite,temp4, match4,TM_CCOEFF);
       	        minMaxLoc(match4, NULL, &e4, NULL, NULL);                

		double best = max4(e1,e2,e3,e4);
		
		if(best < 100000000)
			orientation = '0';
		else if(compareDoubles2(best,e1))
			orientation = '1';
		else if(compareDoubles2(best,e2))
			orientation = '2';
		else if(compareDoubles2(best,e3))
			orientation = '3';
		else if(compareDoubles2(best,e4))
			orientation = '4';

		std::cout << "Orientation " << orientation << std::endl;
		write(fd, &orientation, 1);
		pthread_mutex_lock(&mutex2);
		if(quit)
		{
			break;
		}
		pthread_mutex_unlock(&mutex2);

	}
	
	

}

int main(int argv, char ** argc)
{
	//initialize temporary variable
	char c = '0';

	//initialize serial
        fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );  
        if (fd <0) {perror(MODEMDEVICE); exit(-1); }

	//backup setting and clear
        tcgetattr(fd,&oldtio); /* save current serial port settings */
        bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	newtio.c_iflag = IGNPAR | ICRNL;
	newtio.c_oflag = 0;
	newtio.c_lflag = ICANON;

	newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
        newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
        newtio.c_cc[VERASE]   = 0;     /* del */
        newtio.c_cc[VKILL]    = 0;     /* @ */
        newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
        newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
        newtio.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
        newtio.c_cc[VSWTC]    = 0;     /* '\0' */
        newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
        newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
        newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
        newtio.c_cc[VEOL]     = 0;     /* '\0' */
        newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
        newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
        newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
        newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
        newtio.c_cc[VEOL2]    = 0;     /* '\0' */

	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);

	//Sync
	//sleep(2);
	//write(fd, &c, 1);
	





	if(!cap.isOpened())
		return -1;
	//initiate black variable to as a workaround
	Mat gray;
	Mat frame;
	cap >> frame;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	threshold(gray, black, 50, 255, THRESH_BINARY);
	

	//run each pthread
	pthread_t thread1, thread2;
	int iret1, iret2;
	iret1 = pthread_create( &thread1, NULL, fetchImLoop, NULL);
	if(iret1)
	{
		std::cout << "Image reader failed to initialize\n";
		exit(EXIT_FAILURE);
	}
	iret2 = pthread_create( &thread2, NULL, computeMatchLoop, NULL);
	if(iret2)
	{
		std::cout << "Image proccessing failed to initialize\n";
		exit(EXIT_FAILURE);
	}
	
	//wait for all threads to finish
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	/* restore the old port settings */
        tcsetattr(fd,TCSANOW,&oldtio);

	std::cout << "We did it :)\n";
	
	
	return 0;

}
