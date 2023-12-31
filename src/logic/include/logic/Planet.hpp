//
// Purpur Tentakel
// 07.11.2022
//

#pragma once

#include "SpaceObject.hpp"
#include <alias/AliasUtils.hpp>

namespace lgk {
    class Planet final : public SpaceObject {
    private:
        using vec2pos = utl::vec2pos_ty;
        bool m_isHomePlanet{};
        bool m_isDestroyed{ false };
        int m_planetNumber;
        utl::usize m_maxShips;
        utl::usize m_production;

    public:
        Planet(unsigned int ID, utl::vec2pos_ty_ref_c position, Player_ty player, bool isHomePlanet, int m_planetNumber
        );

        Planet(unsigned int ID,
               utl::vec2pos_ty_ref_c position,
               Player_ty player,
               bool isHomePlanet,
               int m_planetNumber,
               utl::usize ships);

        [[nodiscard]] bool IsHomePlanet() const;

        [[nodiscard]] bool IsPlanet() const override;

        [[nodiscard]] utl::usize GetProduction() const;

        [[nodiscard]] int GetPlanetNumber() const;

        void SetDestroyed(bool isDestroyed);

        [[nodiscard]] bool IsDestroyed() const;

        void Update(Galaxy_ty_raw galaxy) override;
    };
} // namespace lgk
