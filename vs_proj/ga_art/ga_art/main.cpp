#include <cstdint>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "run_hill_climb.h"
#include "hill_climb_time_meas.h"

int main() 
{

	cv::Mat image = cv::imread("test_samples\\example5.png", CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::Mat ref_img = cv::Mat::zeros(constants::IMG_H,
								     constants::IMG_W, CV_8UC4);

	cv::cvtColor(image, ref_img, CV_BGR2BGRA);
	cv::Size dsize;
	dsize.width = constants::IMG_W;
	dsize.height = constants::IMG_H;
	cv::resize(ref_img, ref_img, dsize);

	run_hill_climb(ref_img);

	//hill_climb_time_meas();
	return 0;
}

