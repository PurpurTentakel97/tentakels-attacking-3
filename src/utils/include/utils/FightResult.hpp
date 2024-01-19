//
// PurpurTentakel
// 04.06.23
//

#pragma once

#include "RepresentationPlayer.hpp"
#include "RepresentationSpaceObject.hpp"
#include <alias/AliasUtils.hpp>
#include <utility>
#include <vector>


namespace utl {
    struct FightResult final {
    public:
        using rounds_ty      = std::vector<std::pair<usize, usize>>;
        using player_ty      = std::pair<RepresentationPlayer, RepresentationPlayer>;
        using spaceObject_ty = std::pair<RepresentationSpaceObject, RepresentationSpaceObject>;

    private:
        player_ty m_players{};
        spaceObject_ty m_objects{};
        rounds_ty m_rounds{};
        bool m_valid{ false };


    public:
        FightResult() = default;
        FightResult(player_ty player, spaceObject_ty objects, rounds_ty rounds, bool valid);


        [[nodiscard]] player_ty GetPlayer() const;
        [[nodiscard]] spaceObject_ty GetSpaceObjects() const;
        [[nodiscard]] rounds_ty GetRounds() const;
        [[nodiscard]] bool IsValid() const;
    };
} // namespace utl
