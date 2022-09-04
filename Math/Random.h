#pragma once
#include <random>
#include <vector>
#include <list>

namespace Math
{
	class Random {
	private:
		std::random_device seed_gen;
		std::mt19937_64 engine;
		std::vector<std::uniform_real_distribution<float>> randoms;
		std::list<std::uniform_real_distribution<float>> randoms2;
	public:
		void Initialize();
		int SetSeedRand(const float min, const float max);
		float GetSeedRand(const size_t index);
		void Erase(const size_t index);
		size_t GetSize() { return randoms.size(); }

		int GetRand(const int start, const int end);
		float GetRandF(const float start, const float end);
	public:
		static Random* GetInstance();
	private:
		Random();
		~Random() = default;
		Random(const Random&) = delete;
		const Random& operator=(const Random&) = delete;
	};
}