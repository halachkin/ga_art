#ifndef HILL_CLIMBING_H
#define HILL_ClIMBING_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "DNA.h"
#include "Configs.h"

class HillClimbing
{
private:

	DNA _current_dna;
	const cv::Mat & _ref_img;

public:
	HillClimbing(const cv::Mat & ref_img);

	unsigned int n_generation;
	unsigned int n_selected;
	unsigned int mutation_selected[7] = { 0 };
	std::size_t n_polygons = 0;

	

	void next_generation();
	double fitness();
	const cv::Mat & raster();

	const DNA& dna() const;



};



#endif