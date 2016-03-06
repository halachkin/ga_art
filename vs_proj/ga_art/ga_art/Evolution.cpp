#include "Evolution.h"




Evolution::Evolution(std::size_t population_size, cv::Mat& ref_img):
	_reference_img(ref_img), _population(population_size)
{
	_population.fitness(ref_img);
}

const Population & Evolution::population() const
{
	return _population;
}

double Evolution::fitness()
{
	return _population.fitness(_reference_img);
}

const DNA & Evolution::elite() const
{
	return _population.elite();
}

const Population& Evolution::next_generation()
{
	_population.selection();
	_population.crossover();
	_population.mutation();
	return _population;
}