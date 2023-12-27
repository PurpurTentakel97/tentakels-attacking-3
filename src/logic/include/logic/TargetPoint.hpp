//
// Purpur Tentakel
// 16.02.2022
//

#pragma once
#include "SpaceObject.hpp"

class TargetPoint : public SpaceObject {
public:
    using SpaceObject::SpaceObject;

    [[nodiscard]] bool IsTargetPoint() const override;

    void Update(Galaxy_ty_raw galaxy) override;
};
