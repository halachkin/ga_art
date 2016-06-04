#include <cstdint>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "run_hill_climb.h"


ImageMode IMAGE_MODE = ImageMode::Grayscale;

int main(int argc, char *argv[])
{
	if (argc != 3)
		return -1;

	try
	{
		Configs::load_configs(argv[1]);
	}
	catch (...) // catch-all handler
	{
		std::cout << "Could not read config file" << std::endl;
	}
	cv::Mat image = cv::imread(argv[2], CV_LOAD_IMAGE_UNCHANGED);
	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
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


	run_hill_climb(image);
	//hill_climb_time_meas();

	return 0;
}

