#ifndef FITNESS_H
#define FITNESS_H


#include <opencv2/core/core.hpp>

namespace fitness 
{
	//Mean squared error
	//define as:
	//mean( (IMG1i - IMG2i)^2 )
	//TODO:
	//Deal with rgb and grayscale images, alpha channel
	double mean_square_err(const cv::Mat &img1, const cv::Mat &img2);
}


#endif