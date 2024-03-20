//
// Purpur Tentakel
// 20.03.2024
//

#include "SaveState.hpp"

namespace utl {
    utl::usize SaveState::GetSaveValueCount() {
        return G_Save_Version::s_load_save_entry_count;
    }
} // namespace app
