
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
	return &_points[0];
}



const std::vector<cv::Point>& Polygon::points() const
{
	return _points;
}


Polygon & Polygon::set_point(std::size_t point_idx, cv::Point point)
{
	if (point_idx > _n_vertices)
		point_idx = _n_vertices - 1;

	point.x = point.x > IMG_W ? IMG_W : point.x;
	point.y = point.y > IMG_H ? IMG_H : point.y;
	point.x = point.x < 0 ? 0 : point.x;
	point.y = point.y < 0 ? 0 : point.y;

	this->_points[point_idx] = point;
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
	std::vector<cv::Point>& points) : Polygon(n_vertices, color)
{
	_points = points;
}

Polygon & CartesianPolygon::crossover(Polygon & parent2)
{
	//TODO
	return *this;
}

int CartesianPolygon::mutate()
{
	Random rand;
	int mutation_type = rand.gen_int(0, 3);
	if (mutation_type == 0)
	{
		cv::Point point;
		int k = 30;
		std::size_t point_idx = rand.gen_int(0, this->n_vertices() - 1);
		point.x = this->points()[point_idx].x;
		point.y = this->points()[point_idx].y;
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
		point.x = this->points()[0].x + dx;
		point.y = this->points()[0].y + dy;
		this->set_point(0, point);
		point.x = this->points()[1].x + dx;
		point.y = this->points()[1].y + dy;
		this->set_point(1, point);
		point.x = this->points()[2].x + dx;
		point.y = this->points()[2].y + dy;
		this->set_point(2, point);
	}
	else if (mutation_type == 2)
	{
		int channel = rand.gen_int(0, 2);
		this->set_color(channel, this->color()[channel] + rand.gen_int(-30, 30));
	}
	else
	{
		this->set_alpha(this->color()[3] + rand.gen_double(-0.1, 0.1));
	}
	return mutation_type;


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
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
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

PolarPolygon & PolarPolygon::set_r(std::size_t point_idx,  double r)
{
	// TODO: insert return statement here
	this->_r[point_idx] = r;
	_points.clear();
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = _r[i] * std::cos(_angles[i]) + _offset_x;
		double y = _r[i] * std::sin(_angles[i]) + _offset_y;
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}
	return *this;
}

PolarPolygon & PolarPolygon::set_angle(std::size_t point_idx, double angle)
{
	// TODO: insert return statement here
	this->_angles[point_idx] = angle;
	_points.clear();
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = _r[i] * std::cos(_angles[i]) + _offset_x;
		double y = _r[i] * std::sin(_angles[i]) + _offset_y;
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}
	return *this;
}

PolarPolygon & PolarPolygon::set_offset_x(double x)
{
	// TODO: insert return statement here
	this->_offset_x = x;
	_points.clear();
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = _r[i] * std::cos(_angles[i]) + _offset_x;
		double y = _r[i] * std::sin(_angles[i]) + _offset_y;
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}
	return *this;
}

PolarPolygon & PolarPolygon::set_offset_y(double y)
{
	// TODO: insert return statement here
	this->_offset_y = y;
	_points.clear();
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = _r[i] * std::cos(_angles[i]) + _offset_x;
		double y = _r[i] * std::sin(_angles[i]) + _offset_y;
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}

	return *this;
}


Polygon & PolarPolygon::crossover(Polygon & parent2)
{
	//TODO
	return *this;
}

int PolarPolygon::mutate()
{
	//TODO
	Random rand;

	int mutation_type = rand.gen_int(0, 3);
	if (mutation_type == 0)
	{
		int idx = rand.gen_int(0, this->n_vertices() - 1);
		double k = SCALE * 20;
		this->set_r(idx, this->_r[idx] + Random().gen_double(-k, k));
	}
	else if (mutation_type == 1)
	{
		int idx = rand.gen_int(0, this->n_vertices() - 1);
		double k = SCALE * 20;
		this->set_angle(idx, this->_angles[idx] + Random().gen_double(-k, k));
	}
	else if (mutation_type == 2)
	{
		int channel = rand.gen_int(0, 2);
		this->set_color(channel, this->color()[channel] + rand.gen_int(-30, 30));
	}
	else
	{
		this->set_alpha(this->color()[3] + rand.gen_double(-0.1, 0.1));

		this->set_offset_x(_offset_x + rand.gen_double(-10, 10));
		this->set_offset_y(_offset_y + rand.gen_double(-10, 10));
	}
	return mutation_type;
	return 0;
}


