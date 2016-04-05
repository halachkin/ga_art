#ifndef DRAW_POLYGONS_H
#define DRAW_POLYGONS_H

#include <memory>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "Polygon.h"


cv::Mat draw_polygons(const std::vector< std::shared_ptr<GeneticPolygon>>& polygons, 
	                  cv::Mat &img,
	                  double* scale = nullptr);

#endif