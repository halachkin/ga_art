#include "draw_polygons.h"


cv::Mat draw_polygons(std::vector<Polygon> polygons, cv::Mat &img)
{
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		//cv::Mat imgt = cv::Mat::zeros(constants::IMG_H,
		//							  constants::IMG_W, CV_8UC3);
		const cv::Point* ppt[1] = { polygons[i].get_raw_points() };
		int npt[] = { static_cast<int>(polygons[i].xy().size()) };
		cv::fillPoly(
			img,
			ppt,
			npt,
			1,
			polygons[i].color(),
			0);
		//addWeighted(img, 
		//			//polygons[i].alpha(),
		//	        imgt,
		//	        //1.0 - polygons[i].alpha(), 
		//	        0.0,
		//	        img);
	}
	return img;
}