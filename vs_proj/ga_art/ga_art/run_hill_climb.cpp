#include "run_hill_climb.h"
#include "draw_polygons.h"

using namespace constants;

void run_hill_climb(const cv::Mat & image)
{
	char window[] = "Genetic Art";

	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);


	cv::Mat ref_img = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC4);
	cv::Mat ref_img_disp = cv::Mat::zeros(DISPLAY_IMG_H, DISPLAY_IMG_W, CV_8UC4);
	//convert input image to the approriate format
	cv::cvtColor(image, ref_img, CV_BGR2BGRA);
	ref_img.copyTo(ref_img_disp);
	//resample input image for displaying
	cv::resize(ref_img_disp, ref_img_disp, cv::Size(DISPLAY_IMG_H, DISPLAY_IMG_W));
	//resample input image for the internal computing
	cv::resize(ref_img, ref_img, cv::Size(IMG_W, IMG_H));
	HillClimbing hill_climbing(ref_img);

	for (int i = 0; (N_GENERATIONS ==0 || i < N_GENERATIONS); i++)
	{
		if (i % 500 == 0)
		{
			std::cout << "fitness: " << hill_climbing.fitness() << " i:  ";
			std::cout << i << " selected:  " << hill_climbing.n_selected;
			std::cout << "  mutation: " << hill_climbing.mutation_selected[0];
			std::cout << ", " << hill_climbing.mutation_selected[1];
			std::cout << "  n poly: " << hill_climbing.n_polygons <<std::endl;
		}
		if (i % 500 == 0)
		{
			cv::Mat output;
			cv::Mat generated_raster = cv::Mat::zeros(DISPLAY_IMG_H, 
				                                      DISPLAY_IMG_H,
				                                      CV_8UC4);
			
			double scale = DISPLAY_IMG_H / double(IMG_H);
			draw_polygons(hill_climbing.dna().polygons(), 
				          generated_raster, &scale);

			cv::hconcat(ref_img_disp, generated_raster, output);
			cv::imshow(window, output);
			cv::waitKey(10);
		}
		hill_climbing.next_generation();
		i++;
	}

}

