//
// Purpur Tentakel
// original by coder2k (https://gist.github.com/mgerhold/353e39da27ae9b22c614bc264c8a3d18)
// 08.08.2022
//

#pragma once

#include <random>


namespace hlp {
    class Random final {
    public:
        static Random& GetInstance();

        [[nodiscard]] auto random(std::mt19937_64::result_type upperBoundExclusive) -> std::mt19937_64::result_type;
        [[nodiscard]] auto random() -> float;
        auto setRandomSeed(std::mt19937_64::result_type seed) -> void;
        [[nodiscard]] auto getRandomSeed() const -> std::mt19937_64::result_type;
        auto setState(std::string state) -> void;
        [[nodiscard]] auto getState() -> std::string;
        auto randomize() -> void;

        Random(Random const& old) = delete;

    private:
        Random();
        std::mt19937_64 mGenerator;
        std::mt19937_64::result_type mSeed;
        std::uniform_real_distribution<float> mUniformRealDistribution;
        std::uniform_int_distribution<std::mt19937_64::result_type> mUniformIntDistribution;
    };

    template<typename T>
    [[nodiscard]] T& RandomElementFromList(std::vector<T>& list) {
        auto& random     = Random::GetInstance();
        auto const index = random.random(list.size());
        return list[index];
    }
} // namespace hlp
