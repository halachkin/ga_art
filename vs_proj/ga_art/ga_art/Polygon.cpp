
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


Polygon & Polygon::set_point(std::size_t point_idx, cv::Point point)
{
	if (point_idx > _n_vertices)
		point_idx = _n_vertices - 1;

	point.x = point.x > IMG_W ? IMG_W : point.x;
	point.y = point.y > IMG_H ? IMG_H : point.y;
	point.x = point.x < 0 ? 0 : point.x;
	point.y = point.y < 0 ? 0 : point.y;

	this->_xy[point_idx] = point;
	return *this;
}



Polygon & Polygon::set_color(int channel, double value)
{
	value = value > 255 ? 255 : value;
	value = value < 0 ? 0 : value;
	this->_color[channel] = value;
	return *this;
}

Polygon & Polygon::set_alpha(double alpha)
{
	alpha = alpha > 1.0 ? 1.0 : alpha;
	alpha = alpha < 0.0 ? 0.0 : alpha;
	this->_color[3] = alpha;
	return *this;
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
	//TODO
	Random rand;
	int mutation_type = rand.gen_int(0, 2);
	if (mutation_type == 0)
	{
		cv::Point point;
		int k = 10;
		std::size_t point_idx = rand.gen_int(0, this->n_vertices() - 1);
		point.x = this->xy()[point_idx].x;
		point.y = this->xy()[point_idx].y;
		int dx = rand.gen_int(-k, k);
		int dy = rand.gen_int(-k, k);
		point.x += dx;
		point.y += dy;
		this->set_point(point_idx, point);
	}
	else if (mutation_type == 1)
	{
		cv::Point point;
		int k = 10;
		int dx = rand.gen_int(-k, k);
		int dy = rand.gen_int(-k, k);
		point.x = this->xy()[0].x + dx;
		point.y = this->xy()[0].y + dy;
		this->set_point(0, point);
		point.x = this->xy()[1].x + dx;
		point.y = this->xy()[1].y + dy;
		this->set_point(1, point);
		point.x = this->xy()[2].x + dx;
		point.y = this->xy()[2].y + dy;
		this->set_point(2, point);
	}
	else
	{
		int channel = rand.gen_int(0, 2);
		this->set_color(channel, this->color()[channel] + rand.gen_int(-10, 10));
		this->set_alpha(this->color()[3] + rand.gen_double(-0.1, 0.1));
	}


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
	//TODO
	return *this;
}

void PolarPolygon::mutate()
{
	//TODO
	Random rand;
	this->_color[0] = rand.gen_int(0, 255);
	this->_color[1] = rand.gen_int(0, 255);
	this->_color[2] = rand.gen_int(0, 255);
	this->_color[3] = rand.gen_double(0.1, 1.0);
}


