#include "HillClimbing.h"
#include "constants.h"
#include "Random.h"

using namespace constants;

HillClimbing::HillClimbing(const cv::Mat & ref_img)
	:
	_ref_img(ref_img),
	_current_dna(DNA(DNA_MODE))

{
	_current_dna.add_random_polygon();
}

void HillClimbing::next_generation()
{
	this->n_generation++;
	DNA next_dna(this->_current_dna);
	this->n_polygons = next_dna.n_polygons();
	int mutation = next_dna.mutate();
	double f1 = next_dna.fitness(_ref_img);
	double f2 = this->_current_dna.fitness(_ref_img);

	if (f1 < f2 
		//|| Random().gen_double(0.0, 1.0) < 0.001 /this->n_selected
		|| (std::abs(f1 - f2) < f2/10000.0 && mutation == 1)
	    )
	{
		this->_current_dna = next_dna;
		//log evolution info
		this->n_selected++;
		//0 - add, 1 - remove
		this->mutation_selected[mutation]++;
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

const DNA& HillClimbing::dna() const
{
	return this->_current_dna;
}
