#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

enum class DnaMode { Polar, Cartesian };
enum class FitnessMode { MSE, PSNR, SSIM };
enum class SelectionMode { RouletteWheel };
enum class ImageMode { Grayscale, BGR };


namespace constants
{
	//general params
	const std::size_t DISPLAY_IMG_W = 200;
	const std::size_t DISPLAY_IMG_H = 200;
	const std::size_t IMG_W = 30;
	const std::size_t IMG_H = 30;
	const uint8_t     N_VERTICES = 3;
	const std::size_t N_GENERATIONS = 0;
	const FitnessMode FITNESS_MODE = FitnessMode::MSE;
	const DnaMode DNA_MODE = DnaMode::Cartesian;

	//params for generating polygons in polar cords
	const double SCALE = 0.3; // [0; 1.0]
	const double OFFSET = SCALE * 0.5 * std::min(IMG_H, IMG_W);



	//Hill climbing params
	const bool   ANNEALING_SIMULATION = false;
	const double ANNEALING_SIMULATION_RATE = 0.001;
	const bool   REMOVING_POLYGON = true;
	const double REMOVING_POLYGON_TOLERANCE = 0.2; // in %

	//Classic genetic algorithm params
	const std::size_t N_POLYGONS = 100;
	const std::size_t POPULATION_SIZE = 20;
	const std::size_t ELITE_SIZE = 3;
	const SelectionMode SELECTION_MODE = SelectionMode::RouletteWheel;


}
#endif