//
// Purpur Tentakel
// 09.06.2023
//

#include "HMergeResult.h"

HMergeResult::HMergeResult(Player_ty player, SpaceObject_ty origin, SpaceObject_ty destination, size_t count)
    : m_player{ player }, m_origin{ origin }, m_destination{ destination }, m_count{ count } { }

Player_ty HMergeResult::GetPlayer() const {
    return m_player;
}
SpaceObject_ty HMergeResult::GetOrigin() const {
    return m_origin;
}
SpaceObject_ty HMergeResult::GetDestination() const {
    return m_destination;
}
size_t HMergeResult::GetCount() const {
    return m_count;
}
