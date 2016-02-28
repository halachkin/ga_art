#ifndef CONSTATNS_H
#define CONSTATNS_H

#include <cstdint>
#include <algorithm>

namespace constants 
{
	//general params
	const std::size_t IMG_W = 500;
	const std::size_t IMG_H = 500;
	const std::size_t N_POLYGONS = 10000;
	const uint8_t     MIN_VERTICES = 3;
	const uint8_t     MAX_VERTICES = 3;

	//params for the generating polygons in polar cords
	const double      SCALE        = 0.05; // [0; 1.0]
	const double OFFSET            = SCALE * 0.5 * std::min(IMG_H, IMG_W);
	
}


#endif