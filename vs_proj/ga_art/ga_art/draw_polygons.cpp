#include "draw_polygons.h"
#include "constants.h"


cv::Mat draw_polygons(std::vector<Polygon> polygons, cv::Mat &img)
{
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		cv::Mat imgt = cv::Mat::zeros(constants::IMG_H,
									  constants::IMG_W, CV_8UC4);
		//imgt = cv::Scalar(255, 255, 255, 0);
		img.copyTo(imgt);
		const cv::Point* ppt[1] = { polygons[i].get_raw_points() };
		int npt[] = { static_cast<int>(polygons[i].xy().size()) };
		cv::fillPoly(
			imgt,// img,
			ppt,
			npt,
			1,
			polygons[i].color(),
			0);

		addWeighted(imgt, 
					polygons[i].alpha(),
			        img,
			        1.0 - polygons[i].alpha(), 
			        0.0,
			        img);
	}
	return img;
}

// // skopirovany algoritmus ... nefungoval
//for (int y = 0; y < img.rows; ++y)
//{				
//	for (int x = 0; x < img.cols; ++x)
//	{
//		double opacity =
//			((double)imgt.data[y * imgt.step + x * 4 + 3])/ 255.;
//		for (int c = 0; opacity > 0 && c < 4; ++c)
//		{
//			unsigned char imgtPx =
//				imgt.data[y * imgt.step + x * 4 + c];
//			unsigned char imgPx =
//				img.data[y * img.step + x * 4 + c];
//			img.data[y*img.step + 4*x + c] =
//				imgPx * (1. - opacity) + imgtPx * opacity;
//		}
//	}
//}