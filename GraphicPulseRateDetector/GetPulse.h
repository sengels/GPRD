//#error
#pragma once
#include <opencv2/imgproc.hpp>
#include <list>
#include <vector>
#include <fftw3.h>

class PulseAnalyzer {
    public:
        PulseAnalyzer(const int& tv);
        ~PulseAnalyzer();
        int getPulse(const std::vector<double>& timeVector, unsigned min = 0, unsigned max = 0);
        double getAverage(cv::Mat m) const;
    private:
        fftw_complex *m_cp;
        fftw_plan m_plan;
        double *m_data;
};
//int computeValue(cv::Mat frame, int x, int y);
//int list2array(int inputArray[], std::list<int>vectorValues);
