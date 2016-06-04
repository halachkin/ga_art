#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <memory>
#include "Polygon.h"
#include "utils.h"

using namespace Configs;


void polygons_to_svg(const std::vector< std::shared_ptr<CartesianPolygon>>& polygons,
	std::string file)
{
	std::ofstream svgfile;
	svgfile.open(file, std::ios::out | std::ios::trunc);
	if (!svgfile.is_open())
		return;
	svgfile << "<svg>\n";
	svgfile << "	<rect width=\"" << IMG_W << "\" height=\"" << IMG_H << "\" fill=\"rgb(0, 0, 0)\" />\n";
	//example polygon
	//svgfile << "	<polygon points=\"50, 5 100, 5 125, 30 125, 80 100, 105 50, 105 25, 80 25, 30\" fill=\"rgb(205,133,255)\" fill-opacity=\"0.4\"/>\n";
	for (std::size_t i = 0; i < polygons.size(); i++)
	{
		svgfile << "	<polygon points=\"";
		std::vector<cv::Point> points(polygons[i]->points());
		for (int j = 0; j < polygons[i]->points().size(); j++)
		{
			svgfile << points[j].x << "," << points[j].y << " ";
		}
		cv::Scalar color = polygons[i]->color();
		svgfile << "\" fill=\"rgb(" << color[2] << "," << color[1] << "," << color[0];
		svgfile << ")\" fill-opacity=\"" << color[3] << "\"/>\n";
	}
	svgfile << "</svg>";
	svgfile.close();
	return;
}

std::string get_time_date_as_str()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y-%I-%M-%S", timeinfo);
	return std::string(buffer);
}

//copy paste from stackoverflow :D
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

std::string pretty_print(std::string log_row)
{
	std::stringstream output;
	std::vector<std::string> params = split(log_row, ';');
	output << " gen: ";
	output << std::setw(5) << std::stoi(params[0]);
	output << " f: ";
	output << std::setw(5) << std::stoi(params[1]);
	output << " selected: ";
	output << std::setw(5) << std::stoi(params[2]);
	output << " n poly: ";
	output << std::setw(5) << std::stoi(params[3]);
	output << " add: ";
	output << std::setw(5) << std::stoi(params[4]);
	output << " remove: ";
	output << std::setw(5) << std::stoi(params[5]);
	output << " position: ";
	output << std::setw(5) << std::stoi(params[6]);
	output << " point: ";
	output << std::setw(5) << std::stoi(params[7]);
	output << " color: ";
	output << std::setw(5) << std::stoi(params[8]);
	output << " alpha: ";
	output << std::setw(5) << std::stoi(params[9]);
	output << " swap: ";
	output << std::setw(5) << std::stoi(params[10]);
	return output.str();;
}