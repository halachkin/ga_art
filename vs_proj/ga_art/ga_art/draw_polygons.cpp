#include "draw_polygons.h"
#include "constants.h"



cv::Mat draw_polygons(std::vector< std::shared_ptr<Polygon>> polygons, cv::Mat &img)
{
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		const cv::Point* ppt[1] = { polygons[i]->get_raw_points() };
		int npt[] = { static_cast<int>(polygons[i]->xy().size()) };
		cv::fillPoly(
			img,
			ppt,
			npt,
			1,
			polygons[i]->color(),
			0);

	}
	return img;
}