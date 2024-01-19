//
// Purpur Tentakel
// 09.06.2023
//

#include "MergeResult.hpp"

namespace utl {
    MergeResult::MergeResult(RepresentationPlayer player,
                             RepresentationSpaceObject origin,
                             RepresentationSpaceObject destination,
                             usize count)
        : m_player{ std::move(player) },
          m_origin{ std::move(origin) },
          m_destination{ std::move(destination) },
          m_count{ count } { }

    RepresentationPlayer MergeResult::GetPlayer() const {
        return m_player;
    }
    RepresentationSpaceObject MergeResult::GetOrigin() const {
        return m_origin;
    }
    RepresentationSpaceObject MergeResult::GetDestination() const {
        return m_destination;
    }
    usize MergeResult::GetCount() const {
        return m_count;
    }
} // namespace utl
