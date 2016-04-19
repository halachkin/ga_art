#include "Configs.h"

namespace Configs
{
	json configs;
	//general params
	bool LOGGING;
	std::size_t LOG_TO_CSV_EVERY_N_GEN;
	std::size_t LOG_IMG_EVERY_N_GEN;
	std::size_t DISPLAY_IMG_W;
	std::size_t DISPLAY_IMG_H;
	std::size_t IMG_W;
	std::size_t IMG_H;
	uint8_t     N_VERTICES;
	std::size_t N_GENERATIONS;
	FitnessMode FITNESS_MODE;
	DnaMode DNA_MODE;

	//params for generating polygons in polar cords
	double SCALE;
	double OFFSET;

	//Fitness SSIM - GaussianBlur parameter
	double GAUSSIAN_SIGMA_X;

	//Hill climbing params
	std::size_t MAX_N_POLYGONS;
	bool   ANNEALING_SIMULATION;
	double ANNEALING_SIMULATION_RATE;
	bool   REMOVING_POLYGON;
	double REMOVING_POLYGON_TOLERANCE;
	//Mutation probabilties, sum should be 1
	double ADD_PROB;
	double REMOVE_PROB;
	double MUTATE_POS;
	double MUTATE_POINT;
	double MUTATE_COLOR;;
	double MUTATE_ALPHA;
	double SWAP_PROB;

}

void Configs::load_configs(std::string config_path)
{
	std::ifstream configf;
	configf.open(config_path);
	configf >> configs;
	configf.close();
	LOGGING = (bool)configs["LOGGING_P"]["LOGGING"];
	LOG_TO_CSV_EVERY_N_GEN = (std::size_t)configs["LOGGING_P"]["LOG_TO_CSV_EVERY_N_GEN"];
	LOG_IMG_EVERY_N_GEN = (std::size_t)configs["LOGGING_P"]["LOG_IMG_EVERY_N_GEN"];

	DISPLAY_IMG_W = (std::size_t)configs["DISPLAY"]["DISPLAY_IMG_W"];
	DISPLAY_IMG_H = (std::size_t)configs["DISPLAY"]["DISPLAY_IMG_H"];

	IMG_W = (std::size_t)configs["INTERNAL_RESOLUTION"]["IMG_W"];
	IMG_H = (std::size_t)configs["INTERNAL_RESOLUTION"]["IMG_H"];


	if (configs["POLYGON"]["DNA_MODE"] == "Cartesian")
		DNA_MODE = DnaMode::Cartesian;
	else
		DNA_MODE = DnaMode::Polar;

	N_VERTICES = (uint8_t)configs["POLYGON"]["N_VERTICES"];
	SCALE = (double)configs["POLYGON"]["SCALE"];
	OFFSET = SCALE * 0.5 * std::min(IMG_H, IMG_W);

	if (configs["METRIC"]["FITNESS_MODE"] == "MSE")
		FITNESS_MODE = FitnessMode::MSE;
	else
		FITNESS_MODE = FitnessMode::SSIM;

	GAUSSIAN_SIGMA_X = configs["METRIC"]["GAUSSIAN_SIGMA_X"];

	N_GENERATIONS = configs["EVOLUTION"]["N_GENERATIONS"];
	MAX_N_POLYGONS = configs["EVOLUTION"]["MAX_N_POLYGONS"];
	ANNEALING_SIMULATION = configs["EVOLUTION"]["ANNEALING_SIMULATION"];
	ANNEALING_SIMULATION_RATE = configs["EVOLUTION"]["ANNEALING_SIMULATION_RATE"];
	REMOVING_POLYGON = configs["EVOLUTION"]["REMOVING_POLYGON"];
	REMOVING_POLYGON_TOLERANCE = configs["EVOLUTION"]["REMOVING_POLYGON_TOLERANCE"];

	ADD_PROB = configs["MUTATIONS_PROBS"]["ADD"];
	REMOVE_PROB = configs["MUTATIONS_PROBS"]["REMOVE"];
	MUTATE_POS = configs["MUTATIONS_PROBS"]["MUTATE_POS"];
	MUTATE_POINT = configs["MUTATIONS_PROBS"]["MUTATE_POINT"];
	MUTATE_COLOR = configs["MUTATIONS_PROBS"]["MUTATE_COLOR"];
	MUTATE_ALPHA = configs["MUTATIONS_PROBS"]["MUTATE_ALPHA"];
	SWAP_PROB = configs["MUTATIONS_PROBS"]["SWAP"];
}



