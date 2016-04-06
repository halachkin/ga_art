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

	cv::Mat image = cv::imread("test_samples\\example2.png", CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	run_hill_climb(image);

	//hill_climb_time_meas();
	return 0;
}

