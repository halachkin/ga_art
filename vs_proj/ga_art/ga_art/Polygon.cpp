
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

Polygon & CartesianPolygon::crossover(Polygon & parent2)
{
	//TODO
	return *this;
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


Polygon & PolarPolygon::crossover(Polygon & parent2)
{
	return *this;
}

void PolarPolygon::mutate()
{
	//TODO
}


