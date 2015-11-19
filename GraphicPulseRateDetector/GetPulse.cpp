#pragma once
#include "GetPulse.h"
#pragma comment(lib, "libfftw3-3")

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <fftw3.h>
#include "highgui.hpp"
#include "stdafx.h"
#include <list>
#include <iostream>
#include "GetPulse.h"

PulseAnalyzer::PulseAnalyzer(const int& ncount) {
    m_cp = (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * ncount);
    m_data = new double[ncount];
}

PulseAnalyzer::~PulseAnalyzer() {
    fftw_free(m_cp);
    delete[] m_data;
    fftw_destroy_plan(m_plan);
}

double PulseAnalyzer::getAverage(cv::Mat m) const {
    cv::Scalar mean = cv::mean(m);
//     std::cout << mean.val[0] << " " << mean.val[1] << " " << mean.val[2] << std::endl;
    return mean.val[1];
}

int PulseAnalyzer::getPulse(const std::vector<double>& timeVector, unsigned min, unsigned max) //RGB Wert rausholen aus cv Mat in bekanntes Format
{
    double ret = 0;
    const int ncount = timeVector.size();
//     std::cout << "ncount: <" << ncount << ">" << std::endl;
//     memset(m_cp, 0, sizeof(fftw_complex) * ncount);
    static bool initialized = false;
    memcpy(m_data, timeVector.data(), sizeof(double) * ncount);
    if(!initialized) {
        initialized = true;
        m_plan = fftw_plan_dft_r2c_1d(ncount, m_data, m_cp, FFTW_MEASURE);
//         std::cout << "found plan!" << (void*)m_plan << std::endl;
    }

    fftw_execute(m_plan);

    double rmax = 0.0, imax = 0.0;
    int frmax = 0, fimax = 0;

    if(max == 0.0 || max <= min) max = ncount;

    for(int i = min; i < ncount && i < max; i++) {
        if(m_cp[i][0] > rmax) {
            rmax = m_cp[i][0];
            frmax = i;
        }
        if(m_cp[i][1] > imax) {
            imax = m_cp[i][1];
            fimax = i;
        }
    }
    std::cout << "max:" << rmax << "@" << frmax << " / " << imax << "@" << fimax << std::endl;
    return fimax;
}
