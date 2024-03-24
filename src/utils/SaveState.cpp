//
// Purpur Tentakel
// 20.03.2024
//

#include "SaveState.hpp"

namespace utl {
    utl::usize SaveState::GetSaveValueCount() {
        return g_save_version.get_load_save_entry_count();
    }
} // namespace app
