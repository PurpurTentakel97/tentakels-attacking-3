//
// Purpur Tentakel
// 07.02.2024
//

#pragma once
#include <alias/AliasUtils.hpp>

namespace utl {
    struct Probability final {
        static constexpr utl::usize maxValue{ 10000 };
        utl::usize value;
        inline utl::usize operator*(Probability const& other) const {
            return value * other.value / maxValue;
        }

        Probability(utl::usize v) : value{ v } { }
    };
} // namespace utl
