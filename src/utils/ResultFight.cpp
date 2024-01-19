//
// PurpurTentakel
// 04.06.23
//

#include "ResultFight.hpp"


namespace utl {
    ResultFight::ResultFight(player_ty player, spaceObject_ty objects, rounds_ty rounds, bool const valid)
        : m_players{ player },
          m_objects{ objects },
          m_rounds{ std::move(rounds) },
          m_valid{ valid } { }

    ResultFight::player_ty ResultFight::GetPlayer() const {
        return m_players;
    }
    ResultFight::spaceObject_ty ResultFight::GetSpaceObjects() const {
        return m_objects;
    }

    ResultFight::rounds_ty ResultFight::GetRounds() const {
        return m_rounds;
    }

    bool ResultFight::IsValid() const {
        return m_valid;
    }
} // namespace utl
