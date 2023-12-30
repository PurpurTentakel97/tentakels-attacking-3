//
// PurpurTentakel
// 04.06.23
//

#include "FightResult.hpp"


namespace utl {
    FightResult::FightResult(player_ty player, spaceObject_ty objects, rounds_ty rounds, bool const valid)
        : m_players{ player },
          m_objects{ objects },
          m_rounds{ std::move(rounds) },
          m_valid{ valid } { }

    FightResult::player_ty FightResult::GetPlayer() const {
        return m_players;
    }
    FightResult::spaceObject_ty FightResult::GetSpaceObjects() const {
        return m_objects;
    }

    FightResult::rounds_ty FightResult::GetRounds() const {
        return m_rounds;
    }

    bool FightResult::IsValid() const {
        return m_valid;
    }
} // namespace utl
