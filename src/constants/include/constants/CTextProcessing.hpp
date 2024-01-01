//
// Purpur Tentakel
// 07.10.2022
//

#pragma once

#include <string>

namespace cst {
    struct TextProcessing final {
        static constexpr char cursor{ '_' };
        static inline std::string const prefix{ "..." };
        static constexpr utl::usize cursorOffset{ 5 };
    };
} // namespace cst
