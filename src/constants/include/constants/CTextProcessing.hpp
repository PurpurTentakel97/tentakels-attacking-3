//
// Purpur Tentakel
// 07.10.2022
//

#pragma once
#include <string>

namespace cst {
    struct CTextProcessing final {
        static constexpr char cursor{ '_' };
        static inline std::string const prefix{ "..." };
        static constexpr int cursorOffset{ 5 };
    };
} // namespace cst
