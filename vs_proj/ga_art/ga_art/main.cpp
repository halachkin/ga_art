#include <cstdint>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "constants.h"
#include "DNA.h"
#include "Evolution.h"


int main(void) 
{

	DNA dna(constants::N_POLYGONS, 
		    constants::N_VERTICES,
		    constants::DNA_MODE);

	char window[] = "img";

	/// Create black empty images
	cv::Mat ref_img = cv::Mat::zeros(constants::IMG_H,
							         constants::IMG_W, CV_8UC3);

	ref_img = cv::Scalar( 255, 255, 255 );
	cv::rectangle(ref_img,
			cv::Point(2 * constants::IMG_H / 8,
				      6 * constants::IMG_H / 8),
		cv::Point(6 * constants::IMG_H / 8,
				  2 * constants::IMG_H / 8),
			cv::Scalar(0, 255, 255),
			-1,
			8);
	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);
	Evolution evolution(constants::POPULATION_SIZE, ref_img);
	for (std::size_t i = 0; i < 30; i++)
	{
		std::cout << "computing generation: " << i << "  ..." << std::endl;
		std::cout << "fintess: " << evolution.fitness() << "   ";
		std::cout << "mean fitness: " << evolution.mean_fitness() << "  ";
		std::cout << "population size: " << evolution.population().size();
		std::cout << std::endl;
		cv::Mat output;
		cv::hconcat(ref_img, evolution.elite().raster(), output);
		cv::imshow(window, output);
		
		cv::waitKey(25);
		evolution.next_generation();
		
	}

	std::cout << "finish" << std::endl;
	std::cin >> std::string();
	
	return(0);
}

