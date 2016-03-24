#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

enum class DnaMode { Polar, Cartesian };
enum class SelectionMode { RouletteWheel };
enum class FitnessMode { MSE, PSNR, SSIM };

namespace constants
{
	//general params
	const std::size_t IMG_W = 300;
	const std::size_t IMG_H = 300;
	const std::size_t N_POLYGONS = 100;
	const std::size_t N_GENERATIONS = 100000;
	const uint8_t     N_VERTICES = 3;

	//params for generating polygons in polar cords
	const double SCALE = 0.5; // [0; 1.0]
	const double OFFSET = SCALE * 0.5 * std::min(IMG_H, IMG_W);

	const DnaMode DNA_MODE = DnaMode::Polar;

	const FitnessMode FITNESS_MODE = FitnessMode::MSE;

	//Evolution params
	const std::size_t POPULATION_SIZE = 20;
	const std::size_t ELITE_SIZE = 3;
	const SelectionMode SELECTION_MODE = SelectionMode::RouletteWheel;


}
#endif