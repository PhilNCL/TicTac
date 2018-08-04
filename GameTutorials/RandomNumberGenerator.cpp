#include "RandomNumberGenerator.h"

#include <ctime>
#include <random>

int getRandomIntInRange(int min, int max)
{
	static std::mt19937_64 _randomEngine(time(0));
	std::uniform_int_distribution<int> emptySlotIndices(min, max);
	return emptySlotIndices(_randomEngine);
}

float getProbability()
{
	static std::mt19937_64 _randomEngine(time(0));
	static std::uniform_real_distribution<> prob_distribution(0.0f, 1.0f); 
	return prob_distribution(_randomEngine);
}