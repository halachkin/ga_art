
#include <stdexcept>

#include "Random.h"
#include "Configs.h"
#include "Polygon.h"

using namespace Configs;
extern ImageMode IMAGE_MODE;


//Polygon class

CartesianPolygon::CartesianPolygon(uint8_t n_vertices, cv::Scalar& color) :
	_n_vertices(n_vertices), _color(color) {}

const uint8_t& CartesianPolygon::n_vertices() const
{ 
	return _n_vertices;
}

const cv::Scalar& CartesianPolygon::color() const
{
	return _color;
}

const cv::Point * CartesianPolygon::get_raw_points() const
{
	return &_points[0];
}


const std::vector<cv::Point>& CartesianPolygon::points() const
{
	return _points;
}


CartesianPolygon & CartesianPolygon::set_point(std::size_t point_idx, cv::Point point)
{
	if (point_idx > _n_vertices)
		point_idx = _n_vertices - 1;
	check_boundaries(point.x, 0, static_cast<int>(IMG_W));
	check_boundaries(point.y, 0, static_cast<int>(IMG_H));

	this->_points[point_idx] = point;
	return *this;
}

CartesianPolygon & CartesianPolygon::set_color(int channel, double value)
{
	check_boundaries(value, 0.0, 255.0);
	this->_color[channel] = value;
	return *this;
}

CartesianPolygon & CartesianPolygon::set_alpha(double alpha)
{
	check_boundaries(alpha, 0.1, 1.0);
	this->_color[3] = alpha;
	return *this;
}


//CartesianPolygon class
CartesianPolygon::CartesianPolygon(
	uint8_t n_vertices,
	cv::Scalar& color,
	std::vector<cv::Point>& points):
	_n_vertices(n_vertices), _color(color), _points(points)

{
	
}

CartesianPolygon & CartesianPolygon::crossover(CartesianPolygon & parent2)
{
	//TODO
	return *this;
}

void CartesianPolygon::mutate_point()
{
	cv::Point point;
	int k = IMG_H / 5;
	std::size_t point_idx = Random().gen_int(0, this->n_vertices() - 1);
	point.x = this->points()[point_idx].x;
	point.y = this->points()[point_idx].y;
	int dx = Random().gen_int(-k, k);
	int dy = Random().gen_int(-k, k);
	point.x += dx;
	point.y += dy;
	this->set_point(point_idx, point);
}

void CartesianPolygon::mutation_position()
{
	cv::Point point;
	int k = IMG_H / 10;
	int dx = Random().gen_int(-k, k);
	int dy = Random().gen_int(-k, k);
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

void CartesianPolygon::mutate_color()
{
	if (IMAGE_MODE == ImageMode::BGR)
	{
		int channel = Random().gen_int(0, 2);
		this->set_color(channel, this->color()[channel] + Random().gen_int(-30, 30));
	}
	else if (IMAGE_MODE == ImageMode::Grayscale)
	{
		int color_mutation = Random().gen_int(-30, 30);
		for (int i = 0; i < 3; i++)
			this->set_color(i, this->color()[i] + color_mutation);
	}
}

void CartesianPolygon::mutate_alpha()
{
	this->set_alpha(this->color()[3] + Random().gen_double(-0.1, 0.1));
}



/////////////////////////////////////////////////////////////////////////////////////
///////////////////////// P O L A R  P O L Y G O N //////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////


void PolarPolygon::update_cords()
{
	_points.clear();
	for (uint8_t i = 0; i < _n_vertices; i++)
	{
		double x = this->_r[i] * std::cos(_angles[i]) + this->_offset_x;
		double y = this->_r[i] * std::sin(_angles[i]) + this->_offset_y;
		_points.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
	}
}


PolarPolygon::PolarPolygon(uint8_t n_vertices,
	cv::Scalar& color,
	std::vector<double>& r,
	std::vector<double>& angles,
	double offset_x,
	double offset_y) :
	CartesianPolygon(n_vertices, color), _r(r), _angles(angles), _offset_x(offset_x),
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
	check_boundaries(r, 0.0, OFFSET);
	this->_r[point_idx] = r;

	this->update_cords();
	return *this;
}

PolarPolygon & PolarPolygon::set_angle(std::size_t point_idx, double angle)
{
	// TODO: insert return statement here
	check_boundaries(angle, 0.0, static_cast<double>(2 * std::_Pi));
	this->_angles[point_idx] = angle;
	this->update_cords();
	return *this;
}

PolarPolygon & PolarPolygon::set_offset_x(double x)
{
	// TODO: insert return statement here
	check_boundaries(x, OFFSET, IMG_W - OFFSET);
	this->_offset_x = x;
	this->update_cords();
	return *this;
}

PolarPolygon & PolarPolygon::set_offset_y(double y)
{
	check_boundaries(y, OFFSET, IMG_H - OFFSET);
	this->_offset_y = y;
	_points.clear();
	this->update_cords();
	return *this;
}


CartesianPolygon & PolarPolygon::crossover(CartesianPolygon & parent2)
{
	//TODO
	return *this;
}

void PolarPolygon::mutate_point()
{
	int idx = Random().gen_int(0, this->n_vertices() - 1);
	double k = SCALE * 20;
	this->set_r(idx, this->_r[idx] + Random().gen_double(-k, k));
	this->set_angle(idx, this->_angles[idx] + Random().gen_double(-k, k));
}

void PolarPolygon::mutation_position()
{
	this->set_offset_x(_offset_x + Random().gen_double(-10, 10));
	this->set_offset_y(_offset_y + Random().gen_double(-10, 10));
}

void PolarPolygon::mutate_color()
{
	if (IMAGE_MODE == ImageMode::BGR)
	{
		int channel = Random().gen_int(0, 2);
		this->set_color(channel, this->color()[channel] + Random().gen_int(-30, 30));
	}
	else if (IMAGE_MODE == ImageMode::Grayscale)
	{
		int color_mutation = Random().gen_int(-30, 30);
		for (int i = 0; i < 3; i++)
			this->set_color(i, this->color()[i] + color_mutation);
	}
}

void PolarPolygon::mutate_alpha()
{
	this->set_alpha(this->color()[3] + Random().gen_double(-0.1, 0.1));
}









		

                  



