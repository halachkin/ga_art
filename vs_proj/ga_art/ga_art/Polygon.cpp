#include <random>

#include "Random.h"
#include "constants.h"
#include "Polygon.h"

using namespace constants;

Polygon::Polygon(bool gen_in_polar)
{
	Random rand;
	
	_n_vertices = rand.gen_int(MIN_VERTICES, MAX_VERTICES);
	_color[0] = rand.gen_double(0, 255);
	_color[1] = rand.gen_double(0, 255);
	_color[2] = rand.gen_double(0, 255);
	_color[3] = rand.gen_double(0.0, 1.0);

	if (gen_in_polar)
	{
		//generate random polygon in polar cords
		for (uint8_t i = 0; i < _n_vertices; i++)
		{
			_r.push_back(rand.gen_double(0.0, OFFSET));
			_angles.push_back(rand.gen_double(0.0, 2 * std::_Pi));
		}

		std::sort(_angles.begin(), _angles.end());

		double offset_x = rand.gen_double(OFFSET, IMG_W - OFFSET);
		double offset_y = rand.gen_double(OFFSET, IMG_H - OFFSET);

		double _offset_r = sqrt(std::pow(offset_x, 2) + std::pow(offset_x, 2));
		double _offset_angle = std::atan(offset_y / offset_x);

		//compute cartesian cords
		for (uint8_t i = 0; i < _n_vertices; i++)
		{
			double x = _r[i] * std::cos(_angles[i]) + offset_x;
			double y = _r[i] * std::sin(_angles[i]) + offset_y;
			_xy.push_back(cv::Point(static_cast<int>(x), static_cast<int>(y)));
		}
	}
	else
	{
		//generate random polygon in cartesian cords
		for (uint8_t i = 0; i < _n_vertices; i++)
		{
			int x = rand.gen_int(0, IMG_W);
			int y = rand.gen_int(0, IMG_H);
			_xy.push_back(cv::Point(x, y));
		}
	}


}