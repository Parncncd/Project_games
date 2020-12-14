#include "Random.h"

int Random::generateRandom(int min, int max)
{
	int randomNumber = rand() % (max - min + 1) + min;
	int myRandom = randomNumber;
	return myRandom;
}