#ifndef CONFIGS_H
#define CONFIGS_H

#include <cstdint>
#include <algorithm>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;


enum class DnaMode { Polar = 0, Cartesian = 1 };
enum class FitnessMode { MSE = 0, PSNR = 1, SSIM = 2 };
enum class SelectionMode { RouletteWheel = 0};
enum class ImageMode { Grayscale, BGR };


const  std::string DNA_MODE_STR[2] = { "Polar", "Cartesian" };
const  std::string FITNESS_MODE_STR[3] = { "MSE", "PSNR", "SSIM" };
const  std::string SELECTEION_MODE_STR[1] = { "RouletteWheel" };

namespace Configs
{
	
	extern json configs;
	//general params
	extern bool LOGGING;
	extern std::size_t LOG_TO_CSV_EVERY_N_GEN;
	extern std::size_t LOG_IMG_EVERY_N_GEN;
	extern int DISPLAY_IMG_W;
	extern int DISPLAY_IMG_H;
	extern std::size_t DISPLAY_EVERY_N_GEN;
	extern int IMG_W;
	extern int IMG_H;
	extern uint8_t     N_VERTICES;
	extern std::size_t N_GENERATIONS;
	extern FitnessMode FITNESS_MODE;
	extern DnaMode DNA_MODE;

	//params for generating polygons in polar cords
	extern double SCALE;
	extern double OFFSET;

	//Fitness SSIM - GaussianBlur parameter
	extern double GAUSSIAN_SIGMA_X;

	//Hill climbing params
	extern std::size_t MAX_N_POLYGONS;
	extern bool   ANNEALING_SIMULATION;
	extern double ANNEALING_SIMULATION_RATE;
	extern bool   REMOVING_POLYGON;
	extern double REMOVING_POLYGON_TOLERANCE;
	//Mutation probabilties, sum should be 1
	extern double ADD_PROB;
	extern double REMOVE_PROB;
	extern double MUTATE_POS;
	extern double MUTATE_POINT;
	extern double MUTATE_COLOR;;
	extern double MUTATE_ALPHA;
	extern double SWAP_PROB;
	void load_configs(std::string config_path);

}




#endif