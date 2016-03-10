#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

enum class DnaMode { Polar, Cartesian };
enum class SelectionMode { RouletteWheel };


namespace constants
{
	//general params
	const std::size_t IMG_W = 100;
	const std::size_t IMG_H = 100;
	const std::size_t N_POLYGONS = 50;
	const uint8_t     N_VERTICES = 5;

	//params for generating polygons in polar cords
	const double SCALE = 0.9; // [0; 1.0]
	const double OFFSET = SCALE * 0.5 * std::min(IMG_H, IMG_W);

	const DnaMode DNA_MODE = DnaMode::Cartesian;

	//Evolution params
	const std::size_t POPULATION_SIZE = 20;
	const std::size_t ELITE_SIZE = 3;
	const SelectionMode SELECTION_MODE = SelectionMode::RouletteWheel;


}
#endif