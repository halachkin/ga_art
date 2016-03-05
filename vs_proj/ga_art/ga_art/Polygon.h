#ifndef POLYGON_H
#define POLYGON_H

#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>

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
	//polygon vertices Cartesian coordinates
	std::vector<cv::Point> _xy;
	
public:
	//ctor
	Polygon(uint8_t n_vertices, cv::Scalar& color);

	//getters
	const uint8_t& n_vertices() const;
	const cv::Scalar& color() const;
	const std::vector<cv::Point>& xy() const;
	const cv::Point* get_raw_points() const;

	virtual std::ostream& operator<<(std::ostream& os) const = 0;
	//get the polygon genes (part of the dna)
	virtual std::vector<double> genes() const = 0;
	virtual void mutate() = 0;
	
};


class CartesianPolygon : public Polygon
{
public:
	CartesianPolygon(uint8_t n_vertices,
					 cv::Scalar& color,
					 std::vector<cv::Point>& xy);

	std::ostream& operator<<(std::ostream& os) const;
	//get the polygon genes
	std::vector<double> genes() const;
	void mutate();

};


class PolarPolygon : public Polygon
{
private:
	//polygon vertices in polar cords 
	std::vector<double> _r;
	std::vector<double> _angles;
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


	std::vector<double> genes() const;
	std::ostream& operator<<(std::ostream& os) const;
	void mutate();

};

class DNA
{
private:
	std::size_t _n_polygons;
	uint8_t _n_vertices;
	DnaMode _dna_mode;
	std::vector< std::shared_ptr<Polygon>> _polygons;

public:
	const std::vector< std::shared_ptr<Polygon>>& polygons() const;

	static cv::Scalar gen_random_color();

	static std::shared_ptr<CartesianPolygon> 
	gen_random_cartesian_polygon(uint8_t n_vertices);

	static std::shared_ptr<PolarPolygon>
	gen_random_polar_polygon(uint8_t n_vertices);

	DNA(std::size_t n_polygons, 
		uint8_t n_vertices,
		DnaMode dna_mode = DnaMode::Cartesian);

};


#endif