//
// Purpur Tentakel
// 36.06.2023
//

#include "HPlayerData.hpp"
#include <AppContext.hpp>

namespace hlp {
    PlayerData::PlayerData(unsigned int const id, std::string name, Color const col, std::string key)
        : ID{ id },
          color{ col },
          m_name{ std::move(name) },
          m_nameKey{ std::move(key) } { }

    void PlayerData::SetName(std::string const& name) {
        m_name = name;
    }

    std::string PlayerData::GetName() const {
        if (not m_name.empty()) {
            return m_name;
        }
        return AppContext::GetInstance().languageManager.Text(m_nameKey);
    }
} // namespace hlp
