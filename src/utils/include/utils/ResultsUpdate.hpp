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
    struct ResultBlackHole final {
    private:
        RepresentationPlayer m_player;
        RepresentationSpaceObject m_objectDestroyed;
        RepresentationBlackHole m_blackHole;
        usize m_shipsDestroyed;

    public:
        ResultBlackHole(RepresentationPlayer player,
                        RepresentationSpaceObject objectDestroyed,
                        RepresentationBlackHole blackHole,
                        usize shipsDestroyed)
            : m_player{ player },
              m_objectDestroyed{ objectDestroyed },
              m_blackHole{ blackHole },
              m_shipsDestroyed{ shipsDestroyed } { }

        [[nodiscard]] RepresentationPlayer Player() const {
            return m_player;
        }

        [[nodiscard]] RepresentationSpaceObject ObjectDestroyed() const {
            return m_objectDestroyed;
        }

        [[nodiscard]] RepresentationBlackHole BlackHole() const {
            return m_blackHole;
        }

        [[nodiscard]] usize ShipsDestroyed() const {
            return m_shipsDestroyed;
        }
    };

    struct ResultMerge final {
    private:
        RepresentationPlayer m_player;
        RepresentationSpaceObject m_origin;
        RepresentationSpaceObject m_destination;
        usize m_count;

    public:
        ResultMerge(RepresentationPlayer player,
                    RepresentationSpaceObject origin,
                    RepresentationSpaceObject destination,
                    usize count)
            : m_player{ player },
              m_origin{ origin },
              m_destination{ destination },
              m_count{ count } { }

        [[nodiscard]] RepresentationPlayer GetPlayer() const {
            return m_player;
        }

        [[nodiscard]] RepresentationSpaceObject GetOrigin() const {
            return m_origin;
        }

        [[nodiscard]] RepresentationSpaceObject GetDestination() const {
            return m_destination;
        }

        [[nodiscard]] usize GetCount() const {
            return m_count;
        }
    };

    struct ResultFight final {
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
        ResultFight() = default;
        ResultFight(player_ty players, spaceObject_ty objects, rounds_ty rounds, bool valid)
            : m_players{ players },
              m_objects{ objects },
              m_rounds{ std::move(rounds) },
              m_valid{ valid } { }


        [[nodiscard]] player_ty GetPlayers() const {
            return m_players;
        }

        [[nodiscard]] spaceObject_ty GetSpaceObjects() const {
            return m_objects;
        }

        [[nodiscard]] rounds_ty GetRounds() const {
            return m_rounds;
        }

        [[nodiscard]] bool IsValid() const {
            return m_valid;
        }
    };
} // namespace utl
