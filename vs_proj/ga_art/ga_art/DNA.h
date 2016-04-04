#ifndef DNA_H
#define DNA_H


#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>
#include "Polygon.h"

//DNA class
//Contain the polygons
//DNA (chromosome) represents the image
class DNA
{
private:
	//Polygons representation: Polar/Cartesian:
	DnaMode _dna_mode;
	//using smart pointers to avoid problems with memory
	std::vector< std::shared_ptr<Polygon>> _polygons;
	//generated image
	cv::Mat _raster;
	double _fitness;
	bool _fitness_computed;
	
public:
	//will generate random color (BGRA)
	static cv::Scalar gen_random_color();
	
	//will generate polygon with n vertices in Cartesian coords 
	//and random color
	static std::shared_ptr<CartesianPolygon>
	gen_random_cartesian_polygon(uint8_t n_vertices);

	//will generate polygon with n vertices in Polar coords 
	//and random color
	static std::shared_ptr<PolarPolygon>
	gen_random_polar_polygon(uint8_t n_vertices);

	//ctor
	//will init empty DNA
	DNA(DnaMode dna_mode = DnaMode::Cartesian);

	//Will generate n random polygons 
	DNA(std::size_t n_polygons,
		uint8_t n_vertices,
		DnaMode dna_mode = DnaMode::Cartesian);

	//Will create the DNA from the polygons
	DNA(const std::vector< std::shared_ptr<Polygon>>& polygons);
	

	void add_random_polygon();
	void remove_random_polygon();


	//getters
	std::size_t n_polygons() const;
	const DnaMode& dna_mode() const;
	const std::vector< std::shared_ptr<Polygon>>& polygons() const;

	

	//will compute fitness and return it
	//computing fitness only first time! 
	//TODO:
	//add some check for different input images?
	double fitness(const cv::Mat & ref_img);
	//Will generate raster image
	const cv::Mat & raster() ;
	//Will generate raster image of specific size
	//const cv::Mat & raster(cv::Size dsize);

	//TODO
	//Will crossover two DNAs and return offspring
	//Offspring should have the same number of polygons with same
	//number of vertices as parents
	static DNA crossover(const DNA& parent1, const DNA& parent2);
	//TODO
	int mutate();

};

#endif