
#include <stdexcept>

#include "Random.h"
#include "constants.h"
#include "Polygon.h"

using namespace constants;

//Polygon class

Polygon::Polygon(uint8_t n_vertices, cv::Scalar& color) :
	_n_vertices(n_vertices), _color(color) {}

const uint8_t& Polygon::n_vertices() const
{ 
	return _n_vertices;
}

const cv::Scalar& Polygon::color() const
{
	return _color;
}

const cv::Point * Polygon::get_raw_points() const
{
	return &_xy[0];
}

const std::vector<cv::Point>& Polygon::xy() const
{
	return _xy;
}

//CartesianPolygon class
CartesianPolygon::CartesianPolygon(
	uint8_t n_vertices,
	cv::Scalar& color,
	std::vector<cv::Point>& xy) : Polygon(n_vertices, color)
{
	_xy = xy;
}


std::ostream& CartesianPolygon::operator<<(std::ostream& os) const
{
	//TODO
	os << "n_vertices: " << _n_vertices << std::endl;
	os << _xy << std::endl;
	return os;
}

std::vector<double> CartesianPolygon::genes() const
{
	//TODO
	//init the vector with number of coord (x,y) and color (4 values)
	std::vector<double> gen( 2 * this->_n_vertices + 4);
	std::size_t i = 0;
	for (auto it = this->_xy.begin(); it != this->_xy.end(); it++)
	{
		gen[i] = (it->x);
		gen[i + 1] = (it->y);
		i += 2;
	}
	gen.push_back(this->_color[0]);
	gen.push_back(this->_color[1]);
	gen.push_back(this->_color[2]);
	gen.push_back(this->_color[3]);

	return gen;
}

void CartesianPolygon::mutate()
{
	Random rand;
	std::size_t point_idx = rand.gen_int(0, this->n_vertices() - 1);
	this->_xy[point_idx].x = rand.gen_int(0, IMG_W);
	this->_xy[point_idx].y = rand.gen_int(0, IMG_H);
}

//PolarPoygon 
PolarPolygon::PolarPolygon(uint8_t n_vertices,
	cv::Scalar& color,
	std::vector<double>& r,
	std::vector<double>& angles,
	double offset_x,
	double offset_y) :
	Polygon(n_vertices, color), _r(r), _angles(angles), _offset_x(offset_x),
	_offset_y(offset_y)
{
	//compute cartesian cords
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = _r[i] * std::cos(_angles[i]) + offset_x;
		double y = _r[i] * std::sin(_angles[i]) + offset_y;
		_xy.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}
}

const std::vector<double>& PolarPolygon::r() const
{ 
	return _r;
}

const std::vector<double>& PolarPolygon::angles() const
{
	return _angles;
}

const double& PolarPolygon::offset_x() const
{ 
	return _offset_x;
}

const double& PolarPolygon::offset_y() const
{ 
	return _offset_y;
}

std::vector<double> PolarPolygon::genes() const
{
	//TODO
	return std::vector<double>();
}

std::ostream & PolarPolygon::operator<<(std::ostream & os) const
{
	//TODO
	os << "n_vertices: " << _n_vertices << std::endl;
	return os;
}

void PolarPolygon::mutate()
{
	//TODO
}


//DNA

const std::vector< std::shared_ptr<Polygon>>& DNA::polygons() const
{
	return _polygons;
}

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

DNA::DNA(
	std::size_t n_polygons,
	uint8_t n_vertices,
	DnaMode dna_mode) :
	_n_polygons(n_polygons), _n_vertices(n_vertices), _dna_mode(dna_mode)
{
	for (std::size_t i = 0; i < n_polygons; i++)
	{
		if (dna_mode == DnaMode::Cartesian)
			_polygons.push_back(gen_random_cartesian_polygon(n_vertices));
		else if (dna_mode == DnaMode::Polar)
			_polygons.push_back(gen_random_polar_polygon(n_vertices));
	}
}