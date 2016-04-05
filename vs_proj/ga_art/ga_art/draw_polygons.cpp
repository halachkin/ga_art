#include "draw_polygons.h"
#include "constants.h"


cv::Mat draw_polygons(const std::vector< std::shared_ptr<Polygon>>& polygons,
	                  cv::Mat &img,
	                  double* scale)
{
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		cv::Mat imgt = cv::Mat::zeros(img.size().height,
									  img.size().width, CV_8UC4);
		img.copyTo(imgt);
		//const cv::Point* ppt[1] = { polygons[i]->get_raw_points() };
		//int npt[] = { static_cast<int>(polygons[i]->points().size()) };
		//cv::fillPoly(
		//	imgt, //img
		//	ppt,
		//	npt,
		//	1,
		//	polygons[i]->color(),
		//	0);
		const cv::Point* pointsptr = polygons[i]->get_raw_points();
		if (scale != nullptr)
		{
			//copy scale points
			std::vector<cv::Point> points(polygons[i]->points());
			for (int j = 0; j < polygons[i]->points().size(); j++)
			{
				points[j].x =  static_cast<int> (points[j].x* (*scale));
				points[j].y =  static_cast<int> (points[j].y* (*scale));
			}
			pointsptr = &points[0];
		}
		fillConvexPoly(imgt,
			pointsptr,
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