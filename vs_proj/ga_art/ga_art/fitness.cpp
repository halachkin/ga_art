#include "fitness.h"


double fitness::mean_square_err(const cv::Mat &img1, const cv::Mat &img2)
{
	cv::Mat diff;
	cv::absdiff(img1, img2, diff);
	diff = diff.mul(diff);
	cv::Scalar bgr = cv::mean(diff);
	return (bgr[0]* bgr[0] + bgr[1]*bgr[1] + bgr[2]* bgr[2]) / 3.0 / 255.0 / 255.0;
}