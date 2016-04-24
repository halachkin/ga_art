#include "hill_climb_time_meas.h"

void hill_climb_time_meas()
{
	cv::Mat image = cv::imread("test_samples\\example1.png", CV_LOAD_IMAGE_UNCHANGED);

	if (!image.data)    // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return;
	}

	cv::Mat ref_img = cv::Mat::zeros(Configs::IMG_H,
		Configs::IMG_W, CV_8UC4);

	cv::cvtColor(image, ref_img, CV_BGR2BGRA);
	cv::Size dsize;
	dsize.width = Configs::IMG_W;
	dsize.height = Configs::IMG_H;
	cv::resize(ref_img, ref_img, dsize);

	clock_t begin = clock();

	run_hill_climb(ref_img);

	clock_t end = clock();
	std::cout << "Time elapsed: " << double(end - begin) / CLOCKS_PER_SEC;
	std::cout << " s" << std::endl;
	std::cin >> string();
}
