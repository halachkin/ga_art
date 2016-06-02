cmake_minimum_required (VERSION 2.8)

project (ga_art)

set(CMAKE_CXX_COMPILER "clang-3.8")
set(CMAKE_CXX_FLAGS "-Wall -std=c++14")

find_package(OpenCV REQUIRED)

set(HEADER_FILES
        Configs.h
        DNA.h
        HillClimbing.h
        Polygon.h
	Random.h
	draw_polygons.h
        fitness.h
	json.hpp
	run_hill_climb.h
       )

set(SOURCE_FILES
   	 Configs.cpp
   	 DNA.cpp
	 HillClimbing.cpp
	 Polygon.cpp
	 draw_polygons.cpp
	 fitness.cpp
	 run_hill_climb.cpp
       )


add_executable(ga_art main.cpp ${SOURCE_FILES} ${HEADER_FILES})


target_link_libraries(ga_art ${OpenCV_LIBS} )
