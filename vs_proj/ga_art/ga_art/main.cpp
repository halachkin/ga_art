#include <cstdint>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "run_hill_climb.h"

int main(void) 
{

	DNA dna(constants::N_POLYGONS, 
		    constants::N_VERTICES,
		    constants::DNA_MODE);

	char window[] = "img";

	/// Create black empty images
	cv::Mat image = cv::imread("test_samples\\example3.png", CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::Mat ref_img = cv::Mat::zeros(constants::IMG_H,
								     constants::IMG_W, CV_8UC4);

	cv::cvtColor(image, ref_img, CV_BGR2BGRA);
	run_hill_climb(ref_img);


	
	return(0);
}

