//
// Purpur Tentakel
// original by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)
// 08.08.2022
//

#pragma once
#include <random>

class Random final {
public:
	static Random& GetInstance();

	[[nodiscard]] auto random(std::mt19937_64::result_type upperBoundExclusive)->std::mt19937_64::result_type;
	[[nodiscard]] auto random() -> float;
	auto setRandomSeed(std::mt19937_64::result_type seed) -> void;
	[[nodiscard]] auto getRandomSeed() const->std::mt19937_64::result_type;
	auto randomize() -> void;

private:
	Random();
	Random(const Random& old) = delete;
	std::mt19937_64 mGenerator;
	std::mt19937_64::result_type mSeed;
	std::uniform_real_distribution<float> mUniformRealDistribution;
	std::uniform_int_distribution<std::mt19937_64::result_type> mUniformIntDistribution;
};
