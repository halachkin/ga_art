#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include <fstream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#endif
#include "run_hill_climb.h"
#include "draw_polygons.h"


using namespace Configs;
extern ImageMode IMAGE_MODE;


void polygons_to_svg(const std::vector< std::shared_ptr<CartesianPolygon>>& polygons,
	std::string file)
{
	std::ofstream svgfile;
	svgfile.open(file, std::ios::out | std::ios::trunc);
	if (!svgfile.is_open())
		return;
	svgfile << "<svg>\n";
	svgfile << "	<rect width=\"" << IMG_W << "\" height=\"" << IMG_H << "\" fill=\"rgb(0, 0, 0)\" />\n";
	//example polygon
	//svgfile << "	<polygon points=\"50, 5 100, 5 125, 30 125, 80 100, 105 50, 105 25, 80 25, 30\" fill=\"rgb(205,133,255)\" fill-opacity=\"0.4\"/>\n";
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		svgfile << "	<polygon points=\"";
		std::vector<cv::Point> points(polygons[i]->points());
		for (int j = 0; j < polygons[i]->points().size(); j++)
		{
			svgfile << points[j].x << "," << points[j].y <<" ";
		}
		cv::Scalar color = polygons[i]->color();
		svgfile << "\" fill=\"rgb(" << color[2] << "," << color[1] << "," << color[0];
		svgfile << ")\" fill-opacity=\"" << color[3] << "\"/>\n";
	}
	svgfile << "</svg>";
	svgfile.close();
	return;
}

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

//copy paste from stackoverflow :D
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::string pretty_print(std::string log_row)
{
	std::stringstream output;
	std::vector<std::string> params = split(log_row, ';');
	output << " gen: ";
	output << std::setw(5) << std::stoi(params[0]);
	output << " f: ";
	output << std::setw(5) << std::stoi(params[1]);
	output << " selected: ";
	output << std::setw(5) << std::stoi(params[2]);
	output << " n poly: ";
	output << std::setw(5) << std::stoi(params[3]);
	output << " add: ";
	output << std::setw(5) << std::stoi(params[4]);
	output << " remove: ";
	output << std::setw(5) << std::stoi(params[5]);
	output << " position: ";
	output << std::setw(5) << std::stoi(params[6]);
	output << " point: ";
	output << std::setw(5) << std::stoi(params[7]);
	output << " color: ";
	output << std::setw(5) << std::stoi(params[8]);
	output << " alpha: ";
	output << std::setw(5) << std::stoi(params[9]);
	output << " swap: ";
	output << std::setw(5) << std::stoi(params[10]);
	return output.str();;
}

void run_hill_climb(const cv::Mat & image)
{
	//date and time will be the name of the log directory
	std::string timedate = get_time_date_as_str();
	std::string log_dir= "logs\\" + timedate;

	//stats.csv stores fitness, number selected models and other parameters 
	//for every n generations
	std::string logname =  log_dir + "\\" + "stats.csv";
	std::ofstream logfile;
	std::string configname = log_dir + "\\" + "config.json";
	std::ofstream config_file;
	if (LOGGING)
	{
		#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
		CreateDirectory(log_dir.c_str(), NULL);
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
			cv::imwrite(log_dir + "\\" +
				"img_" + std::to_string(i) + ".png", generated_raster);
			polygons_to_svg(hill_climbing.dna().polygons(), log_dir + "\\" +
				"svg_" + std::to_string(i) + ".svg");
		}

		hill_climbing.next_generation();

	}

	if(LOGGING)
		logfile.close();
	std::cout << "finished" << std::endl;

}

