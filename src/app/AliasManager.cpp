//
// Purpur Tentakel
// 05.02.2024
//

#include "AliasManager.hpp"
#include <helper/HPrint.hpp>

namespace app {
    bool AliasManager::ContainsSpaceObject(utl::usize spaceObjectID) const {
        return m_alias.contains(spaceObjectID);
    }

    bool AliasManager::ContainsAlias(utl::usize spaceObjectID, utl::usize playerID) const {
        if (not ContainsSpaceObject(spaceObjectID)) {
            return false;
        }

        return m_alias.at(spaceObjectID).contains(playerID);
    }

    void AliasManager::SetAlias(utl::usize spaceObjectID, utl::usize playerID, std::string alias) {
        m_alias[spaceObjectID][playerID] = std::move(alias);
    }

    std::string AliasManager::Alias(utl::usize spaceObjectID, utl::usize playerID) const {
        if (not ContainsAlias(spaceObjectID, playerID)) {
            hlp::Print(hlp::PrintType::ERROR,
                       "no alias for Space Object {} and player {}. returning empty string",
                       spaceObjectID,
                       playerID);
            return "";
        }

        return m_alias.at(spaceObjectID).at(playerID);
    }

    void AliasManager::DeleteAlias(utl::usize spaceObjectID, utl::usize playerID) {
        if (not ContainsAlias(spaceObjectID, playerID)) {
            return;
        }

        m_alias[spaceObjectID].erase(playerID);

        if (m_alias[spaceObjectID].empty()) {
            m_alias.erase(spaceObjectID);
        }
    }

    void AliasManager::DeleteSpaceObjectAlias(utl::usize spaceObjectID) {
        if (not ContainsSpaceObject(spaceObjectID)) {
            return;
        }

        m_alias.erase(spaceObjectID);
    }
} // namespace app
