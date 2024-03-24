//
// Purpur Tentakel
// 20.03.2024
//

#pragma once

#include <alias/AliasUtils.hpp>
#include "G_Save_Version.hpp"

namespace utl {
    struct SaveState final {
        G_Save_Version g_save_version;

        [[nodiscard]] utl::usize GetSaveValueCount();
    };
} // namespace app
