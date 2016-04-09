#include "DNA.h"


#include "constants.h"
#include "Random.h"
#include "draw_polygons.h"
#include "fitness.h"


using namespace constants;
extern ImageMode IMAGE_MODE;


DNA DNA::deep_copy()
{
	std::vector< std::shared_ptr<CartesianPolygon>> polygons;
	//polygons deep copy
	for (int i = 0; i < this->_polygons.size(); i++)
	{
		polygons.push_back(std::shared_ptr<CartesianPolygon>(
			this->_polygons[i]->clone()));
	}
	return DNA(polygons);
}

cv::Scalar DNA::gen_random_color()
{
	Random rand;
	cv::Scalar color;
	if (IMAGE_MODE == ImageMode::BGR)
	{
		color[0] = rand.gen_double(0, 255);
		color[1] = rand.gen_double(0, 255);
		color[2] = rand.gen_double(0, 255);
	}
	else if (IMAGE_MODE == ImageMode::Grayscale)
	{
		double random_color = rand.gen_double(0, 255);
		for (int i = 0; i < 3; i++)
			color[i] = random_color;
	}

	color[3] = rand.gen_double(0.1, 1.0);
	return color;
}

std::shared_ptr<CartesianPolygon>
DNA::gen_random_cartesian_polygon(uint8_t n_vertices)
{
	Random rand;
	std::vector<cv::Point> points;
	for (uint8_t i = 0; i < n_vertices; i++)
	{
		int x = rand.gen_int(0, IMG_W);
		int y = rand.gen_int(0, IMG_H);
		points.push_back(cv::Point(x, y));
	}
	return std::shared_ptr<CartesianPolygon>(
		new CartesianPolygon(n_vertices, gen_random_color(), points));
}

std::shared_ptr<CartesianPolygon>
DNA::gen_random_polar_polygon(uint8_t n_vertices)
{
	Random rand;
	std::vector<double> r;
	std::vector<double> angles;
	for (uint8_t i = 0; i < n_vertices; i++)
	{
		r.push_back(rand.gen_double(0.0, OFFSET));
		angles.push_back(rand.gen_double(0.0, 2 * std::_Pi));
	}
	std::sort(angles.begin(), angles.end());
	double offset_x = rand.gen_double(OFFSET, IMG_W - OFFSET);
	double offset_y = rand.gen_double(OFFSET, IMG_H - OFFSET);

	return std::shared_ptr<CartesianPolygon>(
		new PolarPolygon(n_vertices, gen_random_color(),
			r, angles, offset_x, offset_y));
}

DNA::DNA(DnaMode dna_mode) :
_dna_mode(dna_mode)
{
	
}

DNA::DNA(std::size_t n_polygons,
	     uint8_t n_vertices,
	     DnaMode dna_mode) :
	_dna_mode(dna_mode)
{
	_fitness_computed = false;
	//generate random n polygons
	for (std::size_t i = 0; i < n_polygons; i++)
	{
		if (dna_mode == DnaMode::Cartesian)
			_polygons.push_back(gen_random_cartesian_polygon(n_vertices));
		else if (dna_mode == DnaMode::Polar)
			_polygons.push_back(gen_random_polar_polygon(n_vertices));
	}

}


DNA::DNA(const std::vector< std::shared_ptr<CartesianPolygon>>& polygons) :
	_polygons(polygons)
{
	//if (typeid(*polygons[0].get()) == typeid(CartesianPolygon))
	//	_dna_mode = DnaMode::Cartesian;
	//else if (typeid(*polygons[0].get()) == typeid(PolarPolygon))
	//	_dna_mode = DnaMode::Polar;
	//else
	//	throw std::exception("Unknown polygon DNA");
	_dna_mode = DNA_MODE;
	_fitness_computed = false;

}

void DNA::add_random_polygon()
{
	if (this->_dna_mode == DnaMode::Cartesian)
		_polygons.push_back(gen_random_cartesian_polygon(constants::N_VERTICES));
	else if (this->_dna_mode == DnaMode::Polar)
		_polygons.push_back(gen_random_polar_polygon(constants::N_VERTICES));
}

void DNA::remove_random_polygon()
{
	int idx = Random().gen_int(0, static_cast<int>(this->_polygons.size() - 1));
	this->_polygons.erase(this->_polygons.begin() + idx);
}


std::size_t DNA::n_polygons() const
{
	return _polygons.size();
}

const DnaMode & DNA::dna_mode() const
{
	return _dna_mode;
}


const std::vector< std::shared_ptr<CartesianPolygon>>& DNA::polygons() const
{
	return _polygons;
}

double DNA::fitness(const cv::Mat & ref_img)
{
	if (!_fitness_computed)
	{
		this->_fitness_computed = true;
		this->_fitness = fitness::fitness(ref_img, this->raster(), FITNESS_MODE);
	}
	return _fitness;
}

const cv::Mat & DNA::raster()
{
	if (_raster.empty())
	{
		_raster = cv::Mat::zeros(constants::IMG_H,
			                     constants::IMG_W, CV_8UC4);
		draw_polygons(this->_polygons, this->_raster);
	}
	return _raster;
}

DNA DNA::crossover(const DNA & parent1, const DNA & parent2)
{
	//TODO 
	//There is just some naive version to make code work
	std::vector< std::shared_ptr<CartesianPolygon>> polygons(
		parent1.polygons().begin(),
		parent1.polygons().begin() + parent1.n_polygons() / 2);
	polygons.insert(polygons.end(), parent2.polygons().begin(),
		parent2.polygons().begin() + parent2.n_polygons() / 2);
	//std::shuffle(polygons.begin(), polygons.end(), Random().generator());

	return DNA(polygons);
}

int DNA::mutate()
{
	double roll = Random().gen_double(0.0, 1.0);
	int n = static_cast<int>(this->n_polygons() - 1);
	int mutation_type = 0;
	if (roll < ADD_PROB  && this->n_polygons() < MAX_N_POLYGONS)
	{
		this->add_random_polygon();
		mutation_type = 0;
	}
	else if (!this->_polygons.empty())
	{
		if (roll < ADD_PROB + REMOVE_PROB)
		{
			this->remove_random_polygon();
			mutation_type = 1;
		}
		else if (roll < ADD_PROB + REMOVE_PROB + MUTATE_POS)
		{
			this->_polygons[Random().gen_int(0, n)]->mutation_position();
			mutation_type = 2;
		}
		else if (roll < ADD_PROB + REMOVE_PROB + MUTATE_POS + MUTATE_POINT)
		{
			this->_polygons[Random().gen_int(0, n)]->mutate_point();
			mutation_type = 3;
		}
		else if (roll < ADD_PROB + REMOVE_PROB + MUTATE_POS + MUTATE_COLOR)
		{
			this->_polygons[Random().gen_int(0, n)]->mutate_color();
			mutation_type = 4;
		}
		else if (roll < ADD_PROB + REMOVE_PROB + MUTATE_POS + MUTATE_COLOR + MUTATE_ALPHA)
		{
			this->_polygons[Random().gen_int(0, n)]->mutate_alpha();
			mutation_type = 5;
		}
		else if (roll < ADD_PROB + REMOVE_PROB + MUTATE_POS + MUTATE_COLOR + MUTATE_ALPHA + SWAP_PROB)
			//it seems like not very good mutation
		{
			int idx1 = Random().gen_int(0, n);
			int idx2 = Random().gen_int(0, n);
			std::iter_swap(this->_polygons[idx1], this->_polygons[idx2]);
			mutation_type = 6;
		}

	}

	_fitness_computed = false;
	_raster.release();
	return mutation_type;
}
