#include "DNA.h"


#include "constants.h"
#include "Random.h"
#include "draw_polygons.h"
#include "fitness.h"


using namespace constants;


cv::Scalar DNA::gen_random_color()
{
	Random rand;
	cv::Scalar color;
	color[0] = rand.gen_double(0, 255);
	color[1] = rand.gen_double(0, 255);
	color[2] = rand.gen_double(0, 255);
	color[3] = rand.gen_double(0.1, 1.0);
	return color;
}

std::shared_ptr<CartesianPolygon>
DNA::gen_random_cartesian_polygon(uint8_t n_vertices)
{
	Random rand;
	std::vector<cv::Point> xy;
	for (uint8_t i = 0; i < n_vertices; i++)
	{
		int x = rand.gen_int(0, IMG_W);
		int y = rand.gen_int(0, IMG_H);
		xy.push_back(cv::Point(x, y));
	}
	return std::shared_ptr<CartesianPolygon>(
		new CartesianPolygon(n_vertices, gen_random_color(), xy));
}

std::shared_ptr<PolarPolygon>
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

	return std::shared_ptr<PolarPolygon>(
		new PolarPolygon(n_vertices, gen_random_color(),
			r, angles, offset_x, offset_y));
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

DNA::DNA(const std::vector< std::shared_ptr<Polygon>>& polygons) :
_polygons(polygons)
{
	if (typeid(*polygons[0].get()) == typeid(CartesianPolygon))
		_dna_mode = DnaMode::Cartesian;
	else if (typeid(*polygons[0].get()) == typeid(PolarPolygon))
		_dna_mode = DnaMode::Polar;
	else
		throw std::exception("Unknown polygon DNA");
	_fitness_computed = false;

}
std::size_t DNA::n_polygons() const
{
	return _polygons.size();
}

const DnaMode & DNA::dna_mode() const
{
	return _dna_mode;
}


const std::vector< std::shared_ptr<Polygon>>& DNA::polygons() const
{
	return _polygons;
}

double DNA::fitness(const cv::Mat & ref_img)
{
	if (!_fitness_computed)
	{
		_fitness_computed = true;
		if (_raster.empty())
		{
			_raster = cv::Mat::zeros(constants::IMG_H,
				                     constants::IMG_W, CV_8UC4);
			draw_polygons(this->_polygons, this->_raster);
		}
		_fitness = fitness::mean_square_err(ref_img, _raster);
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
	std::vector< std::shared_ptr<Polygon>> polygons(
		parent1.polygons().begin(),
		parent1.polygons().begin() + parent1.n_polygons() / 2);
	polygons.insert(polygons.end(), parent2.polygons().begin(),
		parent2.polygons().begin() + parent2.n_polygons() / 2);
	//std::shuffle(polygons.begin(), polygons.end(), Random().generator());

	return DNA(polygons);
}

int DNA::mutate()
{
	//TODO
	int idx = Random().gen_int(0, static_cast<int>(_polygons.size() - 1));
	_fitness_computed = false;
	_raster.release();
	return _polygons[idx]->mutate();
}
