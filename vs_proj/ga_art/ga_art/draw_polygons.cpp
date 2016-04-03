#include "draw_polygons.h"
#include "constants.h"



cv::Mat draw_polygons(const std::vector< std::shared_ptr<Polygon>>& polygons, cv::Mat &img)
{
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		cv::Mat imgt = cv::Mat::zeros(img.size().height,
									  img.size().width, CV_8UC4);
		img.copyTo(imgt);
		const cv::Point* ppt[1] = { polygons[i]->get_raw_points() };
		int npt[] = { static_cast<int>(polygons[i]->points().size()) };
		//cv::fillPoly(
		//	imgt, //img
		//	ppt,
		//	npt,
		//	1,
		//	polygons[i]->color(),
		//	0);
		fillConvexPoly(img,
			polygons[i]->get_raw_points(),
			static_cast<int>(polygons[i]->points().size()),
			polygons[i]->color(),
			0);
		addWeighted(imgt,
			polygons[i]->color()[3], //alpha
			img,
			1.0 - polygons[i]->color()[3],
			0.0,
			img);

	}
	return img;
}