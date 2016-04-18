#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

enum class DnaMode { Polar = 0, Cartesian = 1 };
enum class FitnessMode { MSE = 0, PSNR = 1, SSIM = 2 };
enum class SelectionMode { RouletteWheel = 0};
enum class ImageMode { Grayscale, BGR };


namespace constants
{
	//general params
	const bool LOGGING = false;
	const std::size_t LOG_TO_CSV_EVERY_N_GEN = 10;
	const std::size_t LOG_IMG_EVERY_N_GEN = 2000;
	const std::size_t DISPLAY_IMG_W = 200;
	const std::size_t DISPLAY_IMG_H = 200;
	const std::size_t IMG_W = 120;
	const std::size_t IMG_H = 120;
	const uint8_t     N_VERTICES = 3;
	const std::size_t N_GENERATIONS = 10000; // 0 for inf
	const FitnessMode FITNESS_MODE = FitnessMode::MSE;
	const DnaMode DNA_MODE = DnaMode::Cartesian;

	//params for generating polygons in polar cords
	const double SCALE = 0.3; // [0; 1.0]
	const double OFFSET =  SCALE * 0.5 * std::min(IMG_H, IMG_W);



	//Hill climbing params

	const std::size_t MAX_N_POLYGONS = 100;
	const bool   ANNEALING_SIMULATION = true;
	const double ANNEALING_SIMULATION_RATE = 0.001;
	const bool   REMOVING_POLYGON = true;
	const double REMOVING_POLYGON_TOLERANCE = 0.01; // in %
	//Mutation probabilties, sum should be 1
	const double ADD_PROB         = 10  / 100.0;
	const double REMOVE_PROB      = 10  / 100.0;
	const double MUTATE_POS		  = 10  / 100.0;
	const double MUTATE_POINT     = 20  / 100.0;
	const double MUTATE_COLOR     = 20  / 100.0;
	const double MUTATE_ALPHA     = 20  / 100.0;
	const double SWAP_PROB		  = 10  /  100.0;


	//Classic genetic algorithm params
	const std::size_t N_POLYGONS = 100;
	const std::size_t POPULATION_SIZE = 20;
	const std::size_t ELITE_SIZE = 3;
	const SelectionMode SELECTION_MODE = SelectionMode::RouletteWheel;

	//to log params
	const std::string DNA_MODE_STR[2] = { "Polar", "Cartesian" };
	const std::string FITNESS_MODE_STR[3] = { "MSE", "PSNR", "SSIM" };
	const std::string SELECTEION_MODE_STR[1] = { "RouletteWheel" };

}
#endif