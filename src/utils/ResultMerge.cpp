//
// Purpur Tentakel
// 09.06.2023
//

#include "ResultMerge.hpp"

namespace utl {
    ResultMerge::ResultMerge(RepresentationPlayer player,
                             RepresentationSpaceObject origin,
                             RepresentationSpaceObject destination,
                             usize count)
        : m_player{ std::move(player) },
          m_origin{ std::move(origin) },
          m_destination{ std::move(destination) },
          m_count{ count } { }

    RepresentationPlayer ResultMerge::GetPlayer() const {
        return m_player;
    }
    RepresentationSpaceObject ResultMerge::GetOrigin() const {
        return m_origin;
    }
    RepresentationSpaceObject ResultMerge::GetDestination() const {
        return m_destination;
    }
    usize ResultMerge::GetCount() const {
        return m_count;
    }
} // namespace utl
