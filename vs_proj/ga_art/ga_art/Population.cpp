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

const std::size_t Population::size() const
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
		throw std::exception("COMPUTE FITNESS FIRST!");
	return -1.0;
}

const DNA & Population::elite() const
{
	if (_elite_found)
		return _chromosomes[_elite_idx];
	else
		throw std::exception("Elite not found yet!");
	return _chromosomes[0];
}

 const Population& Population::selection(SelectionMode selection_mode)
{
	if (selection_mode == SelectionMode::RouletteWheel)
		this->roulette_wheel();

	return *this;
}

 std::size_t 
 Population::roulette_wheel_select(const std::vector<double>& fitness_arr)
 {
	 //compute sum of fitness
	 double fitness_sum = 0.0;
	 for (std::size_t i = 0; i < fitness_arr.size(); i++)
		 fitness_sum += fitness_arr[i];
	 double roll = Random().gen_double(0.0, fitness_sum);
	 for (std::size_t i = 0; i < fitness_arr.size(); i++)
	 {
		 roll -= fitness_arr[i];
		 if (roll <= 0)
			 return i;
	 }
	 return 0;
 }

 void Population::roulette_wheel()
 {
	 //TODL: Need to rewrite this! 

	 DNA elite = this->_chromosomes[this->_elite_idx];
	 this->_chromosomes.erase(this->_chromosomes.begin() + this->_elite_idx);
	 //init fitness array
	 std::vector<double> fitness_arr(this->size());
	 for (std::size_t i = 0; i < this->size(); i++)
		 fitness_arr[i] = _chromosomes[i].fitness();

	 //select chromosomes
	 std::vector<std::size_t> alived;

	 for (std::size_t i = 0; i < this->size() / 2; i++)
	 {
		 std::size_t lucker = Population::roulette_wheel_select(fitness_arr);
		 alived.push_back(lucker);
		 fitness_arr.erase(fitness_arr.begin() + lucker);
	 }
	 //copy luckers to chromosomes
	std::vector<DNA> t_chromosomes;
	std::size_t n = alived.size();
	for (std::size_t i = 0; i < alived.size(); i++)
		t_chromosomes.push_back(this->_chromosomes[i]);


	t_chromosomes.push_back(elite);
	_elite_idx = t_chromosomes.size() - 1;
	_elite_found = true;

	this->_chromosomes = t_chromosomes;
 }

const Population & Population::crossover()
{
	//TODO
	//There is just some naive version to make code work
	std::shuffle(_chromosomes.begin(), _chromosomes.end(),
		         Random().generator());
	std::size_t n = _chromosomes.size();
	for (std::size_t i = 1; i < n /  2 + 1 ; i++)
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
	//TODO 
	//There is just some naive version to make code work

	DNA elite = this->_chromosomes[this->_elite_idx];
	this->_chromosomes.erase(this->_chromosomes.begin() + this->_elite_idx);
	for (std::size_t i = 0; i < constants::POPULATION_SIZE/10; i++)
	{
		int idx = Random().gen_int(0, static_cast<int>(this->size() - 1));
		if (idx == this->_elite_idx)
			continue;
		this->_chromosomes[idx].mutate();
	}
	this->_chromosomes.push_back(elite);
	this->_elite_found = false;
	return *this;
}
