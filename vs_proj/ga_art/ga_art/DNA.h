#ifndef DNA_H
#define DNA_H


#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>
#include "Polygon.h"


class DNA
{
private:
	DnaMode _dna_mode;
	std::vector< std::shared_ptr<Polygon>> _polygons;
	cv::Mat _raster;
	double _fitness;
	bool _fitness_computed;
	
public:


	static cv::Scalar gen_random_color();
	
	static std::shared_ptr<CartesianPolygon>
	gen_random_cartesian_polygon(uint8_t n_vertices);

	static std::shared_ptr<PolarPolygon>
	gen_random_polar_polygon(uint8_t n_vertices);

	//ctors
	//Will generate random DNA
	DNA(std::size_t n_polygons,
		uint8_t n_vertices,
		DnaMode dna_mode = DnaMode::Cartesian);

	//Will create the DNA from the polygons
	DNA(const std::vector< std::shared_ptr<Polygon>>& polygons);
	
	//getters
	std::size_t n_polygons() const;
	const DnaMode& dna_mode() const;
	const std::vector< std::shared_ptr<Polygon>>& polygons() const;
	const double& fitness() const;

	//setter
	DNA& fitness(const double& fitness);


	double cmp_fitness(const cv::Mat & ref_img);
	const cv::Mat & raster() const;

	//TODO
	static DNA crossover(const DNA& parent1, const DNA& parent2);

	DNA& mutate();

};

#endif