//
// Purpur Tentakel
// 05.02.2024
//

#pragma once

#include <alias/AliasUtils.hpp>
#include <unordered_map>
#include <event/EventListener.hpp>

namespace app {
    class AliasManager final {
    private:
        using alias_ty = std::unordered_map<utl::usize, std::unordered_map<utl::usize, std::string>>;
        alias_ty m_alias{};

        [[nodiscard]] bool ContainsSpaceObject(utl::usize spaceObjectID) const;

        [[nodiscard]] bool ContainsAlias(utl::usize spaceObjectID, utl::usize playerID) const;

    public:
        void SetAlias(utl::usize spaceObjectID, utl::usize playerID, std::string alias);

        [[nodiscard]] std::string Alias(utl::usize spaceObjectID, utl::usize playerID) const;

        void DeleteAlias(utl::usize spaceObjectID, utl::usize playerID);

        void DeleteSpaceObjectAlias(utl::usize spaceObjectID);

        void Clear();
    };
} // namespace app
