//
// Purpur Tentakel
// 09.06.2023
//

#pragma once
#include "HLogicAlias.hpp"

struct HMergeResult final {
private:
	Player_ty m_player;
	SpaceObject_ty m_origin;
	SpaceObject_ty m_destination;
	size_t m_count;

public:
	HMergeResult(Player_ty player, SpaceObject_ty origin, SpaceObject_ty destination, size_t count);

	[[nodiscard]] Player_ty GetPlayer() const;
	[[nodiscard]] SpaceObject_ty GetOrigin() const;
	[[nodiscard]] SpaceObject_ty GetDestination() const;
	[[nodiscard]] size_t GetCount() const;
};
