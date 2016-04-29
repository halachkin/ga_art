#include "Population.h"

#include <algorithm>
#include <limits>
#include "Configs.h"
#include "fitness.h"
#include "draw_polygons.h"
#include "Random.h"

using namespace Configs;


void Population::_find_elite()
{
	_chromosomes.insert(_chromosomes.begin(), _elite.begin(), _elite.end());
	_elite.clear();
	for (std::size_t i = 0; i < this->_n_elite; i++)
	{
		std::size_t cur_idx = 0;
		double temp_min = std::numeric_limits<double>::max();
		for (std::size_t j = 0; j < _chromosomes.size(); j++)
		{
			if (temp_min > _chromosomes[j].fitness(_ref_img))
			{
				temp_min = _chromosomes[j].fitness(_ref_img);
				cur_idx = j;
			}
		}
		_elite.push_back(_chromosomes[cur_idx]);
		_chromosomes.erase(_chromosomes.begin() + cur_idx);
	}
}
/*
Population::Population(std::size_t n_chromosomes, const cv::Mat & ref_img) :
	_ref_img(ref_img)
{
	_n_elite = ELITE_SIZE;
	for (std::size_t i = 0; i < n_chromosomes; i++)
		_chromosomes.push_back(DNA(N_POLYGONS, N_VERTICES, DNA_MODE));//MAX_N_POLYGONS
}

Population::Population(std::vector<DNA>& chromosomes, const cv::Mat & ref_img) :
	_chromosomes(chromosomes),
	_ref_img(ref_img)
{
	_n_elite = ELITE_SIZE;
}*/

const std::size_t Population::size() const
{
	return  _chromosomes.size() + _elite.size();
}

const std::vector<DNA>& Population::chromosomes() const
{
	return _chromosomes;
}

double Population::fitness()
{
	if (this->_elite.size() == 0)
		this->_find_elite();
	return this->_elite[this->_elite.size() - 1].fitness(_ref_img);
}


double Population::mean_fitness()
{
	double mean = 0.0;

	for (std::size_t i = 0; i < _chromosomes.size(); i++)
		mean += _chromosomes[i].fitness(_ref_img);
	for (std::size_t i = 0; i < _elite.size(); i++)
		mean += _elite[i].fitness(_ref_img);

	return mean / this->size();

}

const std::vector<DNA>  & Population::elite() const
{
	if (_elite.size() == 0)
		throw std::exception("Elite not found yet!");
	return this->_elite;
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

	//init fitness array
	std::vector<double> fitness_arr(this->_chromosomes.size());
	for (std::size_t i = 0; i < this->_chromosomes.size(); i++)
		fitness_arr[i] = _chromosomes[i].fitness(this->_ref_img);

	//select chromosomes
	std::vector<std::size_t> alived;
	for (std::size_t i = 0; i < this->_chromosomes.size() / 2; i++)
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

	this->_chromosomes = t_chromosomes;
}

const Population & Population::crossover()
{
	//TODO
	//There is just some naive version to make code work
	std::shuffle(_chromosomes.begin(), _chromosomes.end(),
		Random().generator());
	std::size_t n = _chromosomes.size();
	for (std::size_t i = 1; i < n / 2 + 1; i++)
	{
		DNA child1 = DNA::crossover(_chromosomes[i], _chromosomes[i - 1]);
		DNA child2 = DNA::crossover(_chromosomes[i - 1], _chromosomes[i]);
		_chromosomes.push_back(child1);
		_chromosomes.push_back(child2);
	}
	return *this;
}
/*
const Population & Population::mutation()
{
	//TODO 
	//There is just some naive version to make code work

	for (std::size_t i = 0; i < POPULATION_SIZE / 3; i++)
	{
		int idx = Random().gen_int(0, static_cast<int>(this->_chromosomes.size() - 1));
		this->_chromosomes[idx].mutate();
	}

	_chromosomes.insert(_chromosomes.begin(), _elite.begin(), _elite.end());
	_elite.clear();
	return *this;
}
*/