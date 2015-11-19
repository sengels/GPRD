// GraphicPulseRateDetector.cpp : Defines the entry point for the console application.
//
#pragma once
//#include "stdafx.h"

#include "GetPulse.h"
#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
#include "highgui.hpp"
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <chrono>


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
//     namedWindow(outCutWindowName, 1);
     namedWindow(greenFilterWindowName, 1);

    
    //CvSize size = cvSize((int cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH),(int)cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT));
//     cap.set(CV_CAP_PROP_FPS, 60);       //refreshrate!?
    
//     double frameRate = cap.get(CV_CAP_PROP_FPS);
    /*double refreshrate;
    double timestamp1=0;
    double timestamp2=0;

    timestamp1= cap.get(CV_CAP_)
    timestamp2 = timestamp1;

    refreshrate = timestamp2 - timestamp1;

    int length = 10 * frameRate;    //10 für "Über 10 Sekunden messen"*/

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
    
    const int MAX_FRAMES = 200;

    cv::Mat frame;
    cv::Mat frameOutcut;
    std::list<double> colorVector;
    std::list<double> timeVector;
    std::vector<double> v;
    v.reserve(MAX_FRAMES);

    double intervalLength = 0;


    cv::Rect cutout(x1, y1, x2-x1, y2-y1);

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds;

    PulseAnalyzer pa(MAX_FRAMES);

    while (1)
    {    
        cap.grab();
        cap.retrieve(frame, 0);

        frameOutcut = frame(cutout).clone();
        imshow(outCutWindowName, frameOutcut);

        rectangle(frame, cv::Point(x1 - 1, y1 - 1), cv::Point(x2 + 2, y2 + 2), cv::Scalar(0, 0, 255));
        cv::putText(frame, "Stirn hier platzieren!", cv::Point(250, 200), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 255, 0), 1, 1, 0);
        
        end = std::chrono::system_clock::now();
        elapsed_seconds = end - start;
        const double elapsed = elapsed_seconds.count();
        start = end;
        std::cout << (1.0 / elapsed) << "fps" << std::endl;

        cv::putText(frame, std::to_string(1.0 / elapsed), cv::Point(0, 50), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0), 1, 1, 0);

        colorVector.push_back(pa.getAverage(frame(cutout)));
        timeVector.push_back(elapsed_seconds.count());
        intervalLength += elapsed_seconds.count();

        if(colorVector.size() > MAX_FRAMES) {
            colorVector.pop_front();
            intervalLength -= timeVector.front();
            timeVector.pop_front();
            v.clear();
            std::copy(colorVector.begin(), colorVector.end(), std::back_inserter(v));
            double p = pa.getPulse(v, 10, 60) / intervalLength * 60.0;
            cv::putText(frame, "ready: " + std::to_string(intervalLength) + "s / " + std::to_string(p) + "bps", cv::Point(0, 100), cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 0, 0), 1, 1, 0);
        }
//         else {
//             std::cout << "next frame" << std::endl;
        imshow(windowName, frame);
//         }
        // channel 0==blue, channel 1==green, channel 2==red
//         imshow(greenFilterWindowName, channels[1]);


        if (cv::waitKey(1) >= 0) break;
    }
    return 0;
}
