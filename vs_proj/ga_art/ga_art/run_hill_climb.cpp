#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <fstream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <windows.h>
#else
	#include <sys/types.h>
	#include <sys/stat.h>
#endif

#include "run_hill_climb.h"
#include "draw_polygons.h"
#include "utils.h"


using namespace Configs;
extern ImageMode IMAGE_MODE;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash = "\\";
#else
static const std::string slash = "/";
#endif



void run_hill_climb(const cv::Mat & image)
{
	//date and time will be the name of the log directory
	std::string timedate = get_time_date_as_str();
	std::string log_dir= "logs" + slash + timedate;

	//stats.csv stores fitness, number selected models and other parameters 
	//for every n generations
	std::string logname =  log_dir + slash + "stats.csv";
	std::ofstream logfile;
	std::string configname = log_dir + slash + "config.json";
	std::ofstream config_file;
	if (LOGGING)
	{
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		CreateDirectory(log_dir.c_str(), NULL);
		#else
		mkdir(log_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		#endif
		logfile.open(logname, std::ios::out | std::ios::trunc);
		if (!logfile.is_open())
			return;
		//header
		logfile << "GENERATION;FITNESS;SELECTED;NUMBER OF POLYGONS;";
		//muatation count columns
		logfile << "ADD;REMOVE;MUTATE_POS;MUTATE_POINT;MUTATE_COLOR;MUTATE_ALPHA;SWAP";
		//end of header
		logfile << std::endl;

		//save configs
		config_file.open(configname, std::ios::out | std::ios::trunc);
		if (!config_file.is_open())
			return;
		config_file << configs.dump(4);
		config_file.close();

	}
	
	char window[] = "Genetic Art";
	cv::namedWindow(window);
	// cv::moveWindow(window, 10, 500);


	cv::Mat ref_img = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC4);
	cv::Mat ref_img_disp = cv::Mat::zeros(DISPLAY_IMG_H, DISPLAY_IMG_W, CV_8UC4);
	//convert input image to the approriate format
	if (IMAGE_MODE == ImageMode::BGR)
		cv::cvtColor(image, ref_img, CV_BGR2BGRA);
	else if (IMAGE_MODE == ImageMode::Grayscale)
		cv::cvtColor(image, ref_img, CV_GRAY2BGRA);
	ref_img.copyTo(ref_img_disp);
	//resample input image for displaying
	cv::resize(ref_img_disp, ref_img_disp, cv::Size(DISPLAY_IMG_H, DISPLAY_IMG_W));
	//resample input image for the internal computing
	cv::resize(ref_img, ref_img, cv::Size(IMG_W, IMG_H));
	HillClimbing hill_climbing(ref_img);

	for (int i = 0; (N_GENERATIONS == 0 || i < N_GENERATIONS); i++)
	{
		std::stringstream log_row;
		//write row
		log_row << i << ";"; //number of generation
		log_row << hill_climbing.fitness() << ";";
		log_row << hill_climbing.n_selected << ";";
		log_row << hill_climbing.n_polygons << ";";
		for (int i = 0; i < 7; i++)
			log_row << hill_climbing.mutation_selected[i] << ";";
		//end of row
		log_row << std::endl;
		if (LOGGING && (i % LOG_TO_CSV_EVERY_N_GEN == 0))
		{
			logfile << log_row.str();
		}
		cv::Mat generated_raster;
		//display img and log info every 100 generations
		if (i % DISPLAY_EVERY_N_GEN == 0)
		{
			std::cout << pretty_print(log_row.str()) << std::endl;
			cv::Mat output;
			generated_raster = cv::Mat::zeros(DISPLAY_IMG_H, 
				                                      DISPLAY_IMG_H,
				                                      CV_8UC4);
			
			double scale = DISPLAY_IMG_H / double(IMG_H);
			draw_polygons(hill_climbing.dna().polygons(), 
				          generated_raster, &scale);
			
			cv::hconcat(ref_img_disp, generated_raster, output);
			cv::imshow(window, output);
			cv::waitKey(10);
		}
		if (LOGGING && i % LOG_IMG_EVERY_N_GEN == 0)
		{
			generated_raster = cv::Mat::zeros(DISPLAY_IMG_H,
													  DISPLAY_IMG_H,
													  CV_8UC4);
			double scale = DISPLAY_IMG_H / double(IMG_H);
			draw_polygons(hill_climbing.dna().polygons(),
				generated_raster, &scale);
			cv::cvtColor(generated_raster, generated_raster, CV_BGRA2BGR);
			cv::imwrite(log_dir + slash +
				"img_" + std::to_string(i) + ".png", generated_raster);
			polygons_to_svg(hill_climbing.dna().polygons(), log_dir + slash +
				"svg_" + std::to_string(i) + ".svg");
		}

		hill_climbing.next_generation();

	}

	if(LOGGING)
		logfile.close();
	std::cout << "finished" << std::endl;

}

