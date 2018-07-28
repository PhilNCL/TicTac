#include "RandomNumberGenerator.h"

#include <ctime>
#include <random>

int getRandomIntInRange(int min, int max)
{
	static std::mt19937_64 _randomEngine(time(0));
	std::uniform_int_distribution<int> emptySlotIndices(min, max);
	return emptySlotIndices(_randomEngine);
}