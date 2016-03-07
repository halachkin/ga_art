#include "Population.h"

#include <algorithm>
#include <limits>
#include "constants.h"
#include "fitness.h"
#include "draw_polygons.h"
#include "Random.h"

using namespace constants;

Population::Population(std::size_t n_chromosomes) 
{
	for (std::size_t i = 0; i < n_chromosomes; i++)
		_chromosomes.push_back(DNA(N_POLYGONS, N_VERTICES, DNA_MODE));
}

Population::Population(std::vector<DNA>& chromosomes):
   _chromosomes(chromosomes)
{

}

std::size_t Population::size() const
{
	return  _chromosomes.size();
}

const std::vector<DNA>& Population::chromosomes() const
{
	return _chromosomes;
}

double Population::fitness(const cv::Mat& ref_img) 
{
	if (!_elite_found)
	{
		double best_fitness = std::numeric_limits<double>::max();
		std::size_t elite_idx = 0;
		for (std::size_t i = 0; i < _chromosomes.size(); i++)
		{
			double cur_fitness = _chromosomes[i].cmp_fitness(ref_img);
			if (cur_fitness < best_fitness)
			{
				elite_idx = i;
				best_fitness = cur_fitness;
			}
		}
		_elite_idx = elite_idx;
		_elite_found = true;
	}
	return _chromosomes[_elite_idx].fitness();
}


double Population::mean_fitness()
{
	if(_elite_found)
	{
		double mean = 0.0;
		for (std::size_t i = 0; i < _chromosomes.size(); i++)
			mean += _chromosomes[i].fitness();
		return mean / _chromosomes.size();
	}
	else
		std::exception("COMPUTE FITNESS FIRST!");
	return -1.0;
}

const DNA & Population::elite() const
{
	return _chromosomes[_elite_idx];
}

 const Population& Population::selection()
{
	//TODO
	std::sort(this->_chromosomes.begin(), this->_chromosomes.end(),
		[](DNA& a, DNA& b) {return a.fitness() < b.fitness();});
	std::vector<DNA> chromosomes(
		            this->_chromosomes.begin(),
					this->_chromosomes.begin() + this->size() / 2);
	_elite_found = true;
	_elite_idx = 0;
	this->_chromosomes = chromosomes;
	return *this;
}

const Population & Population::crossover()
{
	std::shuffle(_chromosomes.begin(), _chromosomes.end(),
		         Random().generator());
	std::size_t n = _chromosomes.size();
	for (std::size_t i = 1; i < (n + 3) / 2 ; i++)
	{
		DNA child1 = DNA::crossover(_chromosomes[i], _chromosomes[i - 1]);
		DNA child2 = DNA::crossover(_chromosomes[i - 1], _chromosomes[i]);
		_chromosomes.push_back(child1);
		_chromosomes.push_back(child2);
	}
	this->_elite_found = false;
	return *this;
}

const Population & Population::mutation()
{
	for (std::size_t i = 0; i < constants::POPULATION_SIZE/3; i++)
	{
		int idx = Random().gen_int(0, this->size() - 1);
		this->_chromosomes[idx].mutate();
	}
	this->_elite_found = false;
	return *this;
}
