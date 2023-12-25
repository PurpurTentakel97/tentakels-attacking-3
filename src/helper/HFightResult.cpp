//
// PurpurTentakel
// 04.06.23
//

#include "HFightResult.h"

HFightResult::HFightResult(player_ty player, spaceObject_ty objects,
	rounds_ty rounds, bool valid)
	: m_players{ player }, m_objects{ objects }, m_rounds{ rounds }, m_valid{ valid } { }

HFightResult::player_ty HFightResult::GetPlayer() const
{
	return m_players;
}
HFightResult::spaceObject_ty HFightResult::GetSpaceObjects() const
{
	return m_objects;
}

HFightResult::rounds_ty HFightResult::GetRounds() const {
	return m_rounds;
}

bool HFightResult::IsValid() const {
	return m_valid;
}
