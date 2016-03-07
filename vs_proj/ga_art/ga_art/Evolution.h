#ifndef EVOLUTION_H
#define EVOLUTION_H


#include <opencv2/core/core.hpp>
#include "Population.h"

//Evolution class
class Evolution
{
private:
	cv::Mat _reference_img;
	Population _population;

public:
	Evolution(std::size_t population_size, cv::Mat& ref_img);

	const Population& population() const;
	double fitness();
	double mean_fitness();
	const DNA& elite() const;

	const Population& next_generation();

};



#endif