#include <cstdint>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "run_hill_climb.h"
#include "hill_climb_time_meas.h"

ImageMode IMAGE_MODE = ImageMode::Grayscale;

int main() 
{
	
	cv::Mat image = cv::imread("test_samples\\example1.png", CV_LOAD_IMAGE_UNCHANGED);
	switch (image.channels()) 
	{
		default:
		case 1:
			IMAGE_MODE = ImageMode::Grayscale;
			break;
		case 3:
			IMAGE_MODE = ImageMode::BGR;
			break;
	}
	

	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	run_hill_climb(image);

	//hill_climb_time_meas();
	return 0;
}

