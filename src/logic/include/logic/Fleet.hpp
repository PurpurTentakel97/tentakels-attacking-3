//
// PurpurTentakel
// 16.02.22
//

#pragma once
#include "SpaceObject.hpp"

class Fleet final : public SpaceObject {
private:
    SpaceObject_ty m_target;

public:
    Fleet(unsigned int ID, utl::vec2pos_ty_ref_c position, Player_ty_c player, SpaceObject_ty target);

    Fleet(unsigned int ID, utl::vec2pos_ty_ref_c position, size_t ships, Player_ty_c player, SpaceObject_ty target);

    [[nodiscard]] bool IsFleet() const override;

    [[nodiscard]] SpaceObject_ty GetTarget() const;

    [[nodiscard]] std::pair<bool, SpaceObject_ty> GetFairTarget() const;

    void SetTarget(SpaceObject_ty target);

    [[nodiscard]] bool IsArrived() const;

    [[nodiscard]] bool IsFarArrived() const;

    [[nodiscard]] bool IsFriendly() const;

    [[nodiscard]] bool IsFarFriendly() const;

    void Update(Galaxy_ty_raw galaxy) override;
};
