#ifndef POLYGON_H
#define POLYGON_H

#include <cstdint>
#include <iostream>
#include <vector>


#include <opencv2/core/core.hpp>

#include "constants.h"

//Abstract GeneticPolygon class
class GeneticPolygon
{
protected:
	//number of vertices
	uint8_t _n_vertices;
	//GeneticPolygon color BGRA
	cv::Scalar _color;
	//GeneticPolygon vertices in Cartesian coordinates
	std::vector<cv::Point> _points;
	
public:
	//ctor
	GeneticPolygon(uint8_t n_vertices, cv::Scalar& color);

	//getters
	const uint8_t& n_vertices() const;
	const cv::Scalar& color() const;
	const std::vector<cv::Point>& points() const;
	const cv::Point* get_raw_points() const;

	//setters
	GeneticPolygon& set_point(std::size_t point_idx, cv::Point point);
	GeneticPolygon& set_color(int channel, double value);
	GeneticPolygon& set_alpha(double alpha);

	//will crossover this with parent and save child into this	
	virtual GeneticPolygon& crossover(GeneticPolygon& parent2) = 0;
	virtual int mutate() = 0;
};


//Polygon with vertices in Cartesian coordinates
class CartesianPolygon : public GeneticPolygon
{
public:
	CartesianPolygon(uint8_t n_vertices,
					 cv::Scalar& color,
					 std::vector<cv::Point>& points);

	GeneticPolygon& crossover(GeneticPolygon& parent2);
	int mutate();

};


//Polygon with vertices in Polar coordinates
class PolarPolygon : public GeneticPolygon
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


	GeneticPolygon& crossover(GeneticPolygon& parent2);
	int mutate();

};


#endif