#include "Random.h"
#include <stdlib.h>
#include <time.h>

using Math::Random;

Random::Random() {
	engine.seed(seed_gen());
}

void Random::Initialize() { srand(time(NULL)); }

int Random::GetRand(const int start, const int end) {
	return ((rand() % (end + 1)) + start);
}

float Random::GetRandF(const float start, const float end) {
	return (fmodf(rand(), (end + 1.0f)) + start);
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

