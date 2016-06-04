#ifndef POLYGON_H
#define POLYGON_H

#include <cstdint>
#include <iostream>
#include <vector>


#include <opencv2/core/core.hpp>

#include "Configs.h"


#define MIN_BOUNDARY_CHECK(VAL, MIN) ((VAL) > (MIN) ? VAL : MIN)
#define MAX_BOUNDARY_CHECK(VAL, MAX) ((VAL) < (MAX) ? VAL : MAX)

template<class T>
void check_boundaries(T& val, const T& min,const T& max);

//CartesianPolygon class
class CartesianPolygon
{
protected:
	//number of vertices
	uint8_t _n_vertices;
	//CartesianPolygon color BGRA
	cv::Scalar _color;
	//CartesianPolygon vertices in Cartesian coordinates
	std::vector<cv::Point> _points;
	
public:
	//ctor
	CartesianPolygon(uint8_t n_vertices, cv::Scalar const& color);
	CartesianPolygon(
		uint8_t n_vertices,
		cv::Scalar const& color,
		std::vector<cv::Point> const& points);

	virtual ~CartesianPolygon() {}
	//need for deep copy of DNAs
	virtual CartesianPolygon* clone() const {
		return new CartesianPolygon(*this);
	}

	//getters
	const uint8_t& n_vertices() const;
	const cv::Scalar& color() const;
	const std::vector<cv::Point>& points() const;
	const cv::Point* get_raw_points() const;

	//setters
	CartesianPolygon& set_point(std::size_t point_idx, cv::Point point);
	CartesianPolygon& set_color(int channel, double value);
	CartesianPolygon& set_alpha(double alpha);

	virtual void mutate_point();
	virtual void mutation_position();
	virtual void mutate_color();
	virtual void mutate_alpha();


};



//Polygon with vertices in Polar coordinates
class PolarPolygon : public CartesianPolygon
{
private:
	//polygon vertices in polar cords 
	std::vector<double> _r;
	std::vector<double> _angles;
	//Polygon center is located at (_offset_x, _offset_y)
	double _offset_x;
	double _offset_y;

	void update_cords();
public:

	//ctor
	PolarPolygon(   uint8_t n_vertices,
					cv::Scalar const& color,
					std::vector<double> const& r,
					std::vector<double> const& angles,
					double offset_x,
					double offset_y);

	virtual PolarPolygon* clone() const {
		return new PolarPolygon(*this);
	}

	//getters
	const std::vector<double>& r() const;
	const std::vector<double>& angles() const;
	const double& offset_x() const;
	const double& offset_y() const;

	PolarPolygon& set_r(std::size_t point_idx, double r);
	PolarPolygon& set_angle(std::size_t point_idx, double angle);
	PolarPolygon& set_offset_x(double x);
	PolarPolygon& set_offset_y(double y);

	virtual void mutate_point();
	virtual void mutation_position();
	virtual void mutate_color();
	virtual void mutate_alpha();

};

template<class T>
void check_boundaries(T & val, const T & min, const T & max)
{
	val = MIN_BOUNDARY_CHECK(val, min);
	val = MAX_BOUNDARY_CHECK(val, max);
}


#endif


