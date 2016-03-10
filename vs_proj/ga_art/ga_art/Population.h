#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <opencv2/core/core.hpp>
#include "DNA.h"
#include "constants.h"

//Population class
//Contain the DNAs (chromosomes - images)
class Population
{
private:
	std::vector<DNA> _chromosomes;
	//Best Chromosome (DNA with the lowest fitness) index
	//TODO:
	//change to vector
	std::size_t _elite_idx;
	bool _elite_found;

public:
	//Init the population with random chromosomes
	Population(std::size_t n_chromosomes);
	//Create the population from chromosomes
	Population(std::vector<DNA>& chromosomes);

	//getters
	const std::size_t size() const;
	const std::vector<DNA>& chromosomes() const;

	
	//fitness of the best DNA
	//If DNAs do not have fitness will compute it
	double fitness(const cv::Mat& ref_img);

	//mean fitness of all chromosomes
	double mean_fitness();

	//elite getter
	const DNA & elite() const;

	//TODO
	//Genetic operators
	//Selection
	//will erase half of the chromosomes
	const Population& 
	selection(SelectionMode selection_mode = SelectionMode::RouletteWheel);
	//help function to the roulette wheel
	static std::size_t 
	roulette_wheel_select(const std::vector<double>& fitness_arr);
	//Roulette Wheel selection algorithm
	void roulette_wheel();

	//will crossover alived chromosomes
	//population will grow twice
	const Population& crossover();
	
	const Population& mutation();

};


#endif

