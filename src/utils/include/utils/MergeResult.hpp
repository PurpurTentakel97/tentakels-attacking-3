//
// Purpur Tentakel
// 09.06.2023
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <alias/AliasUtils.hpp>

namespace utl {
    struct MergeResult final {
    private:
        lgk::Player_ty m_player;
        lgk::SpaceObject_ty m_origin;
        lgk::SpaceObject_ty m_destination;
        usize m_count;

    public:
        MergeResult(
                lgk::Player_ty player,
                lgk::SpaceObject_ty origin,
                lgk::SpaceObject_ty destination, usize count);

        [[nodiscard]] lgk::Player_ty GetPlayer() const;
        [[nodiscard]] lgk::SpaceObject_ty GetOrigin() const;
        [[nodiscard]] lgk::SpaceObject_ty GetDestination() const;
        [[nodiscard]] usize GetCount() const;
    };
} // namespace utl
