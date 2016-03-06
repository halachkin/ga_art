#include <cstdint>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Polygon.h"
#include "constants.h"
#include "draw_polygons.h"
#include "DNA.h"
#include "Evolution.h"
#include "Population.h"

int main(void) 
{

	DNA dna(constants::N_POLYGONS, 
		    constants::N_VERTICES,
		    constants::DNA_MODE);

	char window[] = "img";

	/// Create black empty images
	cv::Mat ref_img = cv::Mat::zeros(constants::IMG_H,
							        constants::IMG_W, CV_8UC3);

	draw_polygons(dna.polygons(), ref_img);
	
	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);
	Evolution evolution(constants::POPULATION_SIZE, ref_img);
	for (std::size_t i = 0; i < 20; i++)
	{

		std::cout << "computing generation: " << i << std::endl;
		std::cout << evolution.fitness() << "   ";
		std::cout << evolution.population().size() << std::endl;
		cv::Mat output;
		cv::hconcat(ref_img, evolution.elite().raster(), output);
		cv::imshow(window, output);
		
		cv::waitKey(25);
		evolution.next_generation();
		
	}

	std::cout << "finish" << std::endl;

	
	return(0);
}

