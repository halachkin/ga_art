#pragma once


#include <cstdint>
#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "constants.h"
#include "DNA.h"
#include "HillClimbing.h"


void run_hill_climb(const cv::Mat & ref_img);