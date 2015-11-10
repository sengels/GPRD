// GraphicPulseRateDetector.cpp : Defines the entry point for the console application.
//
#pragma once
//#include "stdafx.h"

#include "GetPulse.h"
#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
#include "highgui.hpp"
#include <string>
//#include <list>
#include <iostream>


//using namespace cv;
//#include "Functions.h"

const cv::String windowName = "Welcome to GPRD - A Graphic Pulse Rate Detector";
const cv::String outCutWindowName = "Rectangular Outcut";
const cv::String greenFilterWindowName = "Grün gefiltert";


int main(int argc, char** argv) // funktionierende Version
{
	cv::VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	namedWindow(windowName, 1);
	namedWindow(outCutWindowName, 1);
	namedWindow(greenFilterWindowName, 1);

	
	//CvSize size = cvSize((int cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
	
	/*double frameRate = cap.get(CV_CAP_PROP_FPS);		//refreshrate!?
	double refreshrate;
	double timestamp1=0;
	double timestamp2=0;

	timestamp1= cap.get(CV_CAP_)
	timestamp2 = timestamp1;

	refreshrate = timestamp2 - timestamp1;

	int length = 10 * frameRate;	//10 für "Über 10 Sekunden messen"*/
	double frameRate = 60;

	int x1 = 300;
	int y1 = 220;
	int x2 = 340;
	int y2 = 260;

	int H_MIN = 53;
	int H_MAX = 90;
	int S_MIN = 74;
	int S_MAX = 147;
	int V_MIN = 160;
	int V_MAX = 256;
	
	cv::Mat frame;
	cv::Mat frameOutcut;

	int i;
	/*
	for (i = 1, i = 600, i++);
	{

	}*/

	while (1)
	{	
		cap >> frame; // get a new frame from camera

		frameOutcut = frame(cv::Rect(x1, y1, x2-x1, y2-y1)).clone();
		imshow(outCutWindowName, frameOutcut);

		rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 255));
		cv::putText(frame, "Stirn hier platzieren!", cv::Point(250, 200), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0), 1, 1, 0);
		
		//std::cout <<"Framerate:" << frameRate <<std::endl;

		cv::putText(frame, std::to_string(frameRate),cv::Point(0,50),cv::FONT_HERSHEY_COMPLEX,1,cv::Scalar(255,0,0),1,1,0);

		imshow(windowName, frame);
		
	
		cv::Mat greenFiltered;
		//green and ranges should be h:53-90 s:74-147 v: 160-255

		//cv::subtract()
		
		//cv::mixChannels(frameOutcut, greenFiltered);
		//cv::cvtColor(frameOutcut, greenFiltered, CV_RGB2HSV);
		//cv::filter2D(frameOutcut, greenFiltered, -1,  );
		
		cv::inRange(frameOutcut, cv::Scalar(H_MIN, S_MIN, V_MIN), cv::Scalar(H_MAX, S_MAX, V_MAX), greenFiltered);
		

		imshow(greenFilterWindowName, greenFiltered);

		//Timevektor anlegen
		//Pixelwert auslesen, in Timevektor speichern
		//Framerate auslesen

		//statt 600 Matrix mit 0-Werten initialisiert

		//Liste für den Fall, dass komplette Matrix übergeben wird
		std::list<cv::Mat> timeVector(600); //60 frames/sec * 10 sec


		
		imshow(greenFilterWindowName, frameOutcut);

		timeVector.push_front(frameOutcut);
		
		GetPulse(timeVector);


		//timeVector[] = ;

		if (cv::waitKey(30) >= 0) break;
	}
	return 0;
}