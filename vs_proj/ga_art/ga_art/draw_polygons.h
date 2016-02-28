#ifndef DRAW_POLYGONS_H
#define DRAW_POLYGONS_H

#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include "Polygon.h"

cv::Mat draw_polygons(std::vector<Polygon> polygons, cv::Mat &img);

#endif



