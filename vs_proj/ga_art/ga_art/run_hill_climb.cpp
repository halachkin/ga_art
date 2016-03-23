#include "run_hill_climb.h"


void run_hill_climb(const cv::Mat & ref_img)
{
	char window[] = "Genetic Art";

	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);


	HillClimbing hill_climbing(ref_img);
	int i = 0;
	while (true)
	{
		//std::cout << "fitness: " << hill_climbing.fitness() << std::endl;

		if (i % 100 == 0)
		{
			std::cout << "fitness: " << hill_climbing.fitness() << " i:  ";
			std::cout << i << "   selected:  " << hill_climbing.n_selected;
			std::cout << "  mutation: " << hill_climbing.mutation_selected[0];
			std::cout << ", "<< hill_climbing.mutation_selected[1];
			std::cout << ", " << hill_climbing.mutation_selected[2];
			std::cout << ", " << hill_climbing.mutation_selected[3] << std::endl;
		}
		i++;
		if (i % 100 == 0)
		{
			cv::Mat output;
			cv::hconcat(ref_img, hill_climbing.raster(), output);
			cv::imshow(window, output);
			cv::waitKey(10);
		}
		hill_climbing.next_generation();
	}

}

