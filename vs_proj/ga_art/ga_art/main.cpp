#include <cstdint>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Polygon.h"
#include "constants.h"
#include "draw_polygons.h"

int main(void) 
{

	//DNA dna(constants::N_POLYGONS, 
	//	    constants::N_VERTICES,
	//	    constants::DNA_MODE);

	//char window[] = "Polygons";

	///// Create black empty images
	//cv::Mat img = cv::Mat::zeros(constants::IMG_H,
	//						     constants::IMG_W, 
	//);

	//std::vector< std::shared_ptr<Polygon>> polygons = dna.polygons();
	//draw_polygons(polygons, img);
	//
	//cv::imshow(window, img);
	//cv::moveWindow(window, 10, 10);
	//cv::waitKey(0);

	cv::Mat img1 = cv::Mat::zeros(1, 1, CV_8UC3);
	cv::Mat img2 = cv::Mat::zeros(1, 1, CV_8UC3);
	img1.at<cv::Vec3b>(0, 0)[0] = 1;
	img1.at<cv::Vec3b>(0, 0)[1] = 2;
	img1.at<cv::Vec3b>(0, 0)[2] = 3;

	img2.at<cv::Vec3b>(0, 0)[0] = 3;
	img2.at<cv::Vec3b>(0, 0)[1] = 2;
	img2.at<cv::Vec3b>(0, 0)[2] = 1;

	cv::Mat diff;
	cv::absdiff(img1, img2, diff);
	std::cout << diff << std::endl;
	diff = diff.mul(diff);
	cv::Scalar bgr = cv::mean(diff);


	std::cout << img1 << std::endl;
	std::cout << img2 << std::endl;

	std::cout << diff << std::endl;
	std::cout << bgr << std::endl;



	//std::cout << cv::getBuildInformation().c_str() << std::endl;
	std::cin >> std::string();
	return(0);
}

