#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "DNA.h"

class Population
{
private:
	std::vector<DNA> _chromosomes;
	std::size_t _elite_idx;
	
	//the DNA with the lowest fitness value (best DNA)
	bool _elite_found;

public:
	//Init the population with random chromosomes
	Population(std::size_t n_chromosomes);
	//Create the population from chromosomes
	Population(std::vector<DNA>& chromosomes);

	std::size_t size() const;
	const std::vector<DNA>& chromosomes() const;

	
	//fitness of the best DNA
	double fitness(const cv::Mat& ref_img);

	//mean fitness of all chromosomes
	double mean_fitness();

	const DNA & elite() const;
	const Population& selection();
	const Population& crossover();
	const Population& mutation();

};


#endif

