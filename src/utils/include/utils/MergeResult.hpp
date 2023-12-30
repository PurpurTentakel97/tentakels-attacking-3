//
// Purpur Tentakel
// 09.06.2023
//

#pragma once

#include <alias/AliasLogic.hpp>

namespace utl {
    struct MergeResult final {
    private:
        lgk::Player_ty m_player;
        lgk::SpaceObject_ty m_origin;
        lgk::SpaceObject_ty m_destination;
        size_t m_count;

    public:
        MergeResult(lgk::Player_ty player, lgk::SpaceObject_ty origin, lgk::SpaceObject_ty destination, size_t count);

        [[nodiscard]] lgk::Player_ty GetPlayer() const;
        [[nodiscard]] lgk::SpaceObject_ty GetOrigin() const;
        [[nodiscard]] lgk::SpaceObject_ty GetDestination() const;
        [[nodiscard]] size_t GetCount() const;
    };
} // namespace utl
