#include "hill_climbing.h"
#include "constants.h"
#include "Random.h"

using namespace constants;

HillClimbing::HillClimbing(const cv::Mat & ref_img)
	:
	_ref_img(ref_img),
	_current_dna(DNA(N_POLYGONS, N_VERTICES, DNA_MODE))

{
	
}

void HillClimbing::next_generation()
{
	this->n_generation++;
	DNA next_dna(this->_current_dna);
	next_dna.mutate();
	double f1 = next_dna.fitness(_ref_img);
	double f2 = this->_current_dna.fitness(_ref_img);
	if (f1 < f2)
	{
		this->_current_dna = next_dna;
		this->n_selected++;
	}

}

double HillClimbing::fitness()
{
	return this->_current_dna.fitness(_ref_img);
}

const cv::Mat & HillClimbing::raster() 
{
	return this->_current_dna.raster();
}
