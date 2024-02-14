//
// PurpurTentakel
// 16.02.22
//

#pragma once

#include "SpaceObject.hpp"
#include <alias/AliasLogic.hpp>
#include <alias/AliasUtils.hpp>

namespace lgk {
    class Fleet final : public SpaceObject {
    private:
        SpaceObject_ty m_target;
        utl::usize m_engineProblemYears{ 0 };

    public:
        Fleet(utl::usize ID, utl::vec2pos_ty_ref_c position, Player_ty_c player, SpaceObject_ty target);

        Fleet(utl::usize ID,
              utl::vec2pos_ty_ref_c position,
              utl::usize ships,
              Player_ty_c player,
              SpaceObject_ty target);

        [[nodiscard]] bool IsFleet() const override;

        [[nodiscard]] SpaceObject_ty GetTarget() const;

        [[nodiscard]] std::pair<bool, SpaceObject_ty> GetFairTarget() const;

        void SetTarget(SpaceObject_ty target);

        [[nodiscard]] bool IsArrived() const;

        [[nodiscard]] bool IsFarArrived() const;

        [[nodiscard]] bool IsFriendly() const;

        [[nodiscard]] bool IsFarFriendly() const;

        [[nodiscard]] utl::usize GetEngineProblemYears() const;

        void SetEngineProblemYears(utl::usize years);

        void Update(Galaxy_ty_raw galaxy) override;
    };
} // namespace lgk
