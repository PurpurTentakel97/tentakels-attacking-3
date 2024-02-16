//
// Purpur Tentakel
// 16.02.2024
//

#pragma once

#include "SpaceObject.hpp"

namespace lgk {
    class BlackHole final : public SpaceObject {
    private:
    public:
        using SpaceObject::SpaceObject;

        [[nodiscard]] bool IsBlackHole() const override;

        void Update(Galaxy_ty_raw galaxy) override;
    };
} // namespace lgk
