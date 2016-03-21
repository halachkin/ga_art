#ifndef HILL_CLIMBING_H
#define HILL_ClIMBING_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "DNA.h"
#include "constants.h"

class HillClimbing
{
private:

	DNA _current_dna;
	const cv::Mat & _ref_img;

public:
	unsigned int n_generation;
	unsigned int n_selected;
	unsigned int mutation_selected[3] = { 0 };

	HillClimbing(const cv::Mat & ref_img);

	void next_generation();
	double fitness();
	const cv::Mat & raster();



};



#endif