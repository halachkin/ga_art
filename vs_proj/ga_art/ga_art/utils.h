#ifndef UTILS_H
#define UTILS_H


void polygons_to_svg(const std::vector< std::shared_ptr<CartesianPolygon>>& polygons, std::string file);
std::string get_time_date_as_str();
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);
std::string pretty_print(std::string log_row);


#endif