#include "run_hill_climb.h"


void run_hill_climb(const cv::Mat & ref_img)
{
	char window[] = "Genetic Art";

	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);


	HillClimbing hill_climbing(ref_img);
	for (int i = 0; (constants::N_GENERATIONS ==0 || i < constants::N_GENERATIONS); i++)
	{
		if (i % 1000 == 0)
		{
			std::cout << "fitness: " << hill_climbing.fitness() << " i:  ";
			std::cout << i << " selected:  " << hill_climbing.n_selected;
			std::cout << "  mutation: " << hill_climbing.mutation_selected[0];
			std::cout << ", " << hill_climbing.mutation_selected[1];
			std::cout << "  n poly: " << hill_climbing.n_polygons <<std::endl;
		}
		if (i % 100 == 0)
		{
			cv::Mat output;
			cv::Mat generated_raster = hill_climbing.raster();
			cv::Mat ref_img_copy(ref_img);
			cv::Size dsize;
			dsize.width = 250;
			dsize.height = 250;
			cv::resize(generated_raster, generated_raster, dsize);
			cv::resize(ref_img_copy, ref_img_copy, dsize);
			cv::hconcat(ref_img_copy, generated_raster, output);
			cv::imshow(window, output);
			cv::waitKey(10);
		}
		hill_climbing.next_generation();
		i++;
	}

}

