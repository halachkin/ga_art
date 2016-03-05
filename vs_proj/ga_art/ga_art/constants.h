#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

enum class DnaMode { Polar, Cartesian };

namespace constants 
{
	//general params
	const std::size_t IMG_W = 500;
	const std::size_t IMG_H = 500;
	const std::size_t N_POLYGONS = 30000;
	const uint8_t     N_VERTICES = 255;

	//params for generating polygons in polar cords
	const double SCALE = 0.5; // [0; 1.0]
	const double OFFSET = SCALE * 0.5 * std::min(IMG_H, IMG_W);

	const DnaMode DNA_MODE = DnaMode::Polar;
}


#endif