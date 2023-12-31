//
// Purpur Tentakel
// 09.06.2023
//

#include "MergeResult.hpp"

namespace utl {
    MergeResult::MergeResult(
            lgk::Player_ty player,
            lgk::SpaceObject_ty origin,
            lgk::SpaceObject_ty destination,
            utl::usize count
    )
        : m_player{ std::move(player) },
          m_origin{ std::move(origin) },
          m_destination{ std::move(destination) },
          m_count{ count } { }

    lgk::Player_ty MergeResult::GetPlayer() const {
        return m_player;
    }
    lgk::SpaceObject_ty MergeResult::GetOrigin() const {
        return m_origin;
    }
    lgk::SpaceObject_ty MergeResult::GetDestination() const {
        return m_destination;
    }
    utl::usize MergeResult::GetCount() const {
        return m_count;
    }
} // namespace utl
