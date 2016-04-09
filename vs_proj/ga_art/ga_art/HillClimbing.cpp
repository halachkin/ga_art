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
	DNA next_dna  = this->_current_dna.deep_copy();
	this->n_polygons = next_dna.n_polygons();
	int mutation = next_dna.mutate();
	double f1 = next_dna.fitness(_ref_img);
	double f2 = this->_current_dna.fitness(_ref_img);

	if (f1 < f2 
		|| 
		(ANNEALING_SIMULATION && 
		 Random().gen_double(0.0, 1.0) < ANNEALING_SIMULATION_RATE / this->n_selected)
		|| 
		(REMOVING_POLYGON &&
	     std::abs(f1 - f2) < REMOVING_POLYGON_TOLERANCE * f2 / 100.0
	     && mutation == 1)
	    )
	{
		this->_current_dna = next_dna;
		//log evolution info
		this->n_selected++;
		//log mutation info, 0 - add, 1 - remove, ...
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
