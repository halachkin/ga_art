#ifndef POLYGON_H
#define POLYGON_H

#include <cstdint>
#include <iostream>
#include <vector>


#include <opencv2/core/core.hpp>

#include "constants.h"

//Abstract Polygon class
class Polygon
{
protected:
	//number of vertices
	uint8_t _n_vertices;
	//polygon color BGRA
	cv::Scalar _color;
	//polygon vertices in Cartesian coordinates
	std::vector<cv::Point> _points;
	
public:
	//ctor
	Polygon(uint8_t n_vertices, cv::Scalar& color);

	//getters
	const uint8_t& n_vertices() const;
	const cv::Scalar& color() const;
	const std::vector<cv::Point>& points() const;
	const cv::Point* get_raw_points() const;

	//setters
	Polygon& set_point(std::size_t point_idx, cv::Point point);
	Polygon& scale_points(double scale_factor);
	Polygon& set_color(int channel, double value);
	Polygon& set_alpha(double alpha);

	//will crossover this with parent and save child into this	
	virtual Polygon& crossover(Polygon& parent2) = 0;
	virtual int mutate() = 0;
};


//Polygon with vertices in Cartesian coordinates
class CartesianPolygon : public Polygon
{
public:
	CartesianPolygon(uint8_t n_vertices,
					 cv::Scalar& color,
					 std::vector<cv::Point>& points);

	Polygon& crossover(Polygon& parent2);
	int mutate();

};


//Polygon with vertices in Polar coordinates
class PolarPolygon : public Polygon
{
private:
	//polygon vertices in polar cords 
	std::vector<double> _r;
	std::vector<double> _angles;
	//Polygon center is located at (_offset_x, _offset_y)
	double _offset_x;
	double _offset_y;

public:

	//ctor
	PolarPolygon(   uint8_t n_vertices,
					cv::Scalar& color,
					std::vector<double>& r,
					std::vector<double>& angles,
					double offset_x,
					double offset_y);

	//getters
	const std::vector<double>& r() const;
	const std::vector<double>& angles() const;
	const double& offset_x() const;
	const double& offset_y() const;

	PolarPolygon& set_r(std::size_t point_idx, double r);
	PolarPolygon& set_angle(std::size_t point_idx, double angle);
	PolarPolygon& set_offset_x(double x);
	PolarPolygon& set_offset_y(double y);


	Polygon& crossover(Polygon& parent2);
	int mutate();

};


#endif