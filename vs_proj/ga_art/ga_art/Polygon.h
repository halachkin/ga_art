#ifndef POLYGON_H
#define POLYGON_H

#include <cstdint>
#include <vector>
#include <opencv2/core/core.hpp>


class Polygon
{

private:
	uint8_t _n_vertices;
	//cartesian polygon cords
	std::vector<cv::Point> _xy;
	//polar polygon cords
	std::vector<double> _r;
	std::vector<double> _angles;
	double _offset_r;
	double _offset_angle;

	//polygon color BGRA
	cv::Scalar _color;

public:

	//getters
	const uint8_t& n_vertices() const { return _n_vertices; }
	const std::vector<cv::Point>& xy() const { return _xy; }
	const std::vector<double>& r() const { return _r; }
	const std::vector<double>& angles() const { return _angles; }
	const cv::Scalar& color() const { return _color; }
	const double& offset_r() const { return _offset_r; }
	const double& offset_angle() const { return _offset_angle; }


	const cv::Point* get_raw_points() { return &_xy[0]; }
	const double alpha() { return _color[3]; }
	Polygon(bool gen_in_polar = false);

};

class DNAPolygon : public Polygon
{
private:
	std::vector<int> _dna;
};

#endif