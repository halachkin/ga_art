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

	std::vector<Polygon> polygons;
	for (std::size_t i = 0; i < constants::N_POLYGONS; i++)
		polygons.push_back(Polygon());

	char window_cartesian[] = "Random Polygons in Cartesian";
	char window_polar[] = "Random Polygons in Polar";

	/// Create black empty images
	cv::Mat img_cartesian = cv::Mat::zeros(constants::IMG_H,
							     constants::IMG_W, CV_8UC4);

	cv::Mat img_polar = cv::Mat::zeros(constants::IMG_H,
		constants::IMG_W, CV_8UC4);


	draw_polygons(polygons, img_cartesian);

	polygons.clear();
	for (std::size_t i = 0; i < constants::N_POLYGONS; i++)
		polygons.push_back(Polygon(true));
	
	draw_polygons(polygons, img_polar);

	cv::imshow(window_cartesian, img_cartesian);
	cv::imshow(window_polar, img_polar);
	cv::moveWindow(window_polar, 10, 10);
	cv::moveWindow(window_polar, 500, 10);
	cv::waitKey(0);

	
	return(0);
}

