#ifndef GEN_RANDOM_H
#define GEN_RANDOM_H


#include <random>


class Random {

private:
	std::mt19937 gen{ std::random_device{}() };
public:
	std::mt19937 generator() const
	{
		return gen;
	}

	int gen_int(int min, int max)
	{
		return std::uniform_int_distribution<int>{min, max}(gen);
	}

	double gen_double(double min, double max)
	{
		return std::uniform_real_distribution<double>{min, max}(gen);
	}
};




#endif