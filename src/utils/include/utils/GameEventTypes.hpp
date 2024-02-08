//
// Purpur Tentakel
// 24.10.2022
//

#pragma once

#include <cstdint>
#include <type_traits>

namespace utl {
    enum class GameEventType : uint8_t {
        // clang-format off
    PIRATES        = 0b00000001, // 1
    REVOLTS        = 0b00000010, // 2
    RENEGADE_SHIPS = 0b00000100, // 4
    BLACK_HOLE     = 0b00001000, // 8
    SUPERNOVA      = 0b00010000, // 16
    ENGINE_PROBLEM = 0b00100000, // 32
    GLOBAL         = 0b11111111,
        // clang-format on
    };

    inline GameEventType operator|(GameEventType lhs, GameEventType rhs) {
        return static_cast<GameEventType>(
                static_cast<std::underlying_type_t<GameEventType>>(lhs)
                | static_cast<std::underlying_type_t<GameEventType>>(rhs)
        );
    }

    inline GameEventType& operator|=(GameEventType& lhs, GameEventType rhs) {
        return lhs = { lhs | rhs };
    }

    inline GameEventType operator&(GameEventType lhs, GameEventType rhs) {
        return static_cast<GameEventType>(
                static_cast<std::underlying_type_t<GameEventType>>(lhs)
                & static_cast<std::underlying_type_t<GameEventType>>(rhs)
        );
    }

    inline GameEventType& operator&=(GameEventType& lhs, GameEventType rhs) {
        return lhs = { lhs & rhs };
    }

    inline GameEventType operator~(GameEventType value) {
        return static_cast<GameEventType>(~(static_cast<std::underlying_type_t<GameEventType>>(value)));
    }
} // namespace cst
