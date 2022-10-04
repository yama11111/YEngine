#include "Random.h"
#include <stdlib.h>
#include <time.h>

using Math::Random;

Random::Random() {
	engine.seed(seed_gen());
}

void Random::Initialize() { srand(time(NULL)); }

int Random::GetRand(const int start, const int end) {
	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;
	if (div == 0) return end;

	return ((rand() % div) + start);
}

float Random::GetRandF(const float start, const float end) {
	float div = end - start;
	if (div > 0.0f) div += 1.0f;
	if (div < 0.0f) div -= 1.0f;
	if (div == 0.0f) return end;

	return (fmodf((float)rand(), div) + start);
}

int Random::SetSeedRand(const float min, const float max) {
	std::uniform_real_distribution<float> random(min, max);
	randoms.push_back(random);
	return randoms.size() - 1;
}

float Random::GetSeedRand(const size_t index) {
	if (index < 0 || index >= randoms.size()) return 0.0f;
	return randoms[index](engine);
}

void Random::Erase(const size_t index) {
	randoms.erase(randoms.begin() + index);
}

Random* Random::GetInstance() {
	static Random instance;
	return &instance;
}

