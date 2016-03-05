#ifndef FITNESS_H
#define FITNESS_H


#include <opencv2/core/core.hpp>

namespace fitness 
{
	double mean_square_err(const cv::Mat &img1, const cv::Mat &img2);
}


#endif