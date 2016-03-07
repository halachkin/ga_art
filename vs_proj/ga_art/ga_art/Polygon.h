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
	std::vector<cv::Point> _xy;
	
public:
	//ctor
	Polygon(uint8_t n_vertices, cv::Scalar& color);

	//getters
	const uint8_t& n_vertices() const;
	const cv::Scalar& color() const;
	const std::vector<cv::Point>& xy() const;
	const cv::Point* get_raw_points() const;

	//will crossover this with parent and save child into this	
	virtual Polygon& crossover(Polygon& parent2) = 0;
	virtual void mutate() = 0;
};

//Polygon with vertices in Cartesian coordinates
class CartesianPolygon : public Polygon
{
public:
	CartesianPolygon(uint8_t n_vertices,
					 cv::Scalar& color,
					 std::vector<cv::Point>& xy);

	Polygon& crossover(Polygon& parent2);
	void mutate();

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

	Polygon& crossover(Polygon& parent2);
	void mutate();

};


#endif