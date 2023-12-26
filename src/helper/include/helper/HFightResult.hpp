//
// PurpurTentakel
// 04.06.23
//

#include "HLogicAlias.hpp"
#include <vector>
#include <utility>
#pragma once

struct HFightResult final {
public:
	using rounds_ty = std::vector<std::pair<size_t, size_t>>;
	using player_ty = std::pair<Player_ty, Player_ty>;
	using spaceObject_ty = std::pair<SpaceObject_ty, SpaceObject_ty>;

private:
	player_ty m_players;
	spaceObject_ty m_objects;
	rounds_ty m_rounds;
	bool m_valid;


public:
	HFightResult(player_ty player, spaceObject_ty objects,
		rounds_ty rounds, bool valid);


	[[nodiscard]] player_ty GetPlayer() const;
	[[nodiscard]] spaceObject_ty GetSpaceObjects() const;
	[[nodiscard]] rounds_ty GetRounds() const;
	[[nodiscard]] bool IsValid() const;
};