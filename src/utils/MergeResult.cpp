//
// Purpur Tentakel
// 09.06.2023
//

#include "MergeResult.hpp"

namespace utl {
    MergeResult::MergeResult(Player_ty player, SpaceObject_ty origin, SpaceObject_ty destination, size_t count)
        : m_player{ std::move(player) },
          m_origin{ std::move(origin) },
          m_destination{ std::move(destination) },
          m_count{ count } { }

    Player_ty MergeResult::GetPlayer() const {
        return m_player;
    }
    SpaceObject_ty MergeResult::GetOrigin() const {
        return m_origin;
    }
    SpaceObject_ty MergeResult::GetDestination() const {
        return m_destination;
    }
    size_t MergeResult::GetCount() const {
        return m_count;
    }
} // namespace utl
