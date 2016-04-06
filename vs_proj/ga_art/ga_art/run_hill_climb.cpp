#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "run_hill_climb.h"
#include "draw_polygons.h"


using namespace constants;
extern ImageMode IMAGE_MODE;


std::string get_time_date_as_str()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y-%I-%M-%S", timeinfo);
	return std::string(buffer);
}

void log_params(std::string log_dir)
{
	//store parameters
	std::string paramsname = log_dir + "\\" + "params.csv";
	std::ofstream paramsfile;
	paramsfile.open(paramsname, std::ios::out | std::ios::trunc);
	if (!paramsfile.is_open())
		return;
	//use std::map to store constants?
	//general params
	paramsfile << "LOG_TO_CSV_EVERY_N_GEN: " << LOG_TO_CSV_EVERY_N_GEN << std::endl;
	paramsfile << "LOG_IMG_EVERY_N_GEN: " << LOG_IMG_EVERY_N_GEN << std::endl;
	paramsfile << "DISPLAY_IMG_W: " << DISPLAY_IMG_W << std::endl;
	paramsfile << "DISPLAY_IMG_H: " << DISPLAY_IMG_H << std::endl;
	paramsfile << "IMG_W: " << IMG_W << std::endl;
	paramsfile << "IMG_H: " << IMG_H << std::endl;
	paramsfile << "N_VERTICES: " << int(N_VERTICES) << std::endl;
	paramsfile << "N_GENERATIONS: " << N_GENERATIONS << std::endl;
	paramsfile << "FITNESS_MODE: " << FITNESS_MODE_STR[int(FITNESS_MODE)] << std::endl;
	paramsfile << "DNA_MODE: " << DNA_MODE_STR[int(DNA_MODE)] << std::endl;

	//params for generating polygons in polar cords
	paramsfile << "SCALE: " << SCALE << std::endl;
	paramsfile << "OFFSET: " << OFFSET << std::endl;

	//Hill climbing params
	paramsfile << "ANNEALING_SIMULATION: " << ANNEALING_SIMULATION << std::endl;
	paramsfile << "ANNEALING_SIMULATION_RATE: " << ANNEALING_SIMULATION_RATE << std::endl;
	paramsfile << "REMOVING_POLYGON: " << REMOVING_POLYGON << std::endl;
	paramsfile << "REMOVING_POLYGON_TOLERANCE: " << REMOVING_POLYGON_TOLERANCE << std::endl;
	paramsfile.close();
}


void run_hill_climb(const cv::Mat & image)
{
	//date and time will be the name of the log directory
	std::string timedate = get_time_date_as_str();
	std::string log_dir= "logs\\" + timedate;
	CreateDirectory(log_dir.c_str(), NULL);

	if (LOGGING)
	{
		log_params(log_dir);
	}

	//stats.csv stores fitness, number selected models and other parameters 
	//for every n generations
	std::string logname =  log_dir + "\\" + "stats.csv";
	std::ofstream logfile;
	if (LOGGING)
	{
		logfile.open(logname, std::ios::out | std::ios::trunc);
		if (!logfile.is_open())
			return;
		//header
		logfile << "GENERATION;FITNESS;SELECTED;MUTATION ADD;MUTATION REMOVE;NUMBER OF POLYGONS\n";
	}
	

	char window[] = "Genetic Art";

	cv::namedWindow(window);
	cv::moveWindow(window, 10, 500);

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

	for (int i = 0; (N_GENERATIONS ==0 || i < N_GENERATIONS); i++)
	{
		if (LOGGING && (i % LOG_TO_CSV_EVERY_N_GEN == 0))
		{
			logfile << i << ";";
			logfile << hill_climbing.fitness() << ";";
			logfile << hill_climbing.n_selected << ";";
			logfile << hill_climbing.mutation_selected[0] << ";";
			logfile << hill_climbing.mutation_selected[1] << ";";
			logfile << hill_climbing.n_polygons << ";";
			logfile << "\n";
		}
		if (i % 500 == 0)
		{
			std::cout << "fitness: " << hill_climbing.fitness() << " i:  ";
			std::cout << i << " selected:  " << hill_climbing.n_selected;
			std::cout << "  mutation: " << hill_climbing.mutation_selected[0];
			std::cout << ", " << hill_climbing.mutation_selected[1];
			std::cout << "  n poly: " << hill_climbing.n_polygons <<std::endl;

			cv::Mat output;
			cv::Mat generated_raster = cv::Mat::zeros(DISPLAY_IMG_H, 
				                                      DISPLAY_IMG_H,
				                                      CV_8UC4);
			
			double scale = DISPLAY_IMG_H / double(IMG_H);
			draw_polygons(hill_climbing.dna().polygons(), 
				          generated_raster, &scale);

			cv::hconcat(ref_img_disp, generated_raster, output);
			cv::imshow(window, output);
			cv::cvtColor(generated_raster, generated_raster, CV_BGRA2BGR);
			cv::imwrite(log_dir + "\\" + 
				       "img_" + std::to_string(i) + ".png", generated_raster);
			cv::waitKey(10);
		}
		hill_climbing.next_generation();

	}
	if(LOGGING)
		logfile.close();
	std::cout << "finished" << std::endl;

}

