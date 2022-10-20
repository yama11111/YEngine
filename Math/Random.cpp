#include "Random.h"
#include <stdlib.h>
#include <time.h> 

using Math::Random;

Random::Random() 
{
	engine.seed(seed_gen());
}

void Random::Initialize() { srand(time(NULL)); }

int Random::GetRand(const int start, const int end) 
{
	int adjust = 1;
	if (start > end) { adjust = -1; }
	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;
	if (div == 0) return end;

	return adjust * ((rand() % div) + start);
}

float Random::GetRandF(const float start, const float end, const float place)
{
	const int p = static_cast<int>(powf(10, place));
	const int s = static_cast<int>(start * p);
	const int e = static_cast<int>(end * p);
	float result = static_cast<float>(GetRand(s, e)) / p;
	return result;
}

int Random::SetSeedRand(const float min, const float max) 
{
	std::uniform_real_distribution<float> random(min, max);
	randoms.push_back(random);
	return randoms.size() - 1;
}

float Random::GetSeedRand(const size_t index) 
{
	if (index < 0 || index >= randoms.size()) return 0.0f;
	return randoms[index](engine);
}

void Random::Erase(const size_t index) 
{
	randoms.erase(randoms.begin() + index);
}

Random* Random::GetInstance() 
{
	static Random instance;
	return &instance;
}

