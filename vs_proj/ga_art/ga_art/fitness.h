#ifndef FITNESS_H
#define FITNESS_H


#include <opencv2/core/core.hpp>
#include "constants.h"

namespace fitness
{
	//choosing method
	double fitness(const cv::Mat &img1, const cv::Mat &img2, FitnessMode fitness_mode = FitnessMode::MSE);

	//Mean squared error
	//define as:
	//mean( (IMG1i - IMG2i)^2 )
	//TODO:
	//Deal with rgb and grayscale images, alpha channel
	double mean_square_err(const cv::Mat &img1, const cv::Mat &img2);

	//Peak signal-to-noise ratio RGB
	double psnr(const cv::Mat &img1, const cv::Mat &img2);
	//Structural similarity RGB
	double ssim(const cv::Mat &img1, const cv::Mat &img2);
}


#endif