//
// Purpur Tentakel
// 16.02.2024
//

#pragma once

#include "SpaceObject.hpp"

namespace lgk {
    class BlackHole final : public SpaceObject {
    private:
        utl::usize m_extraSize{ 0 };

    public:
        using SpaceObject::SpaceObject;

        [[nodiscard]] bool IsBlackHole() const override;

        void AddExtraSize(SpaceObject_ty_c object);

        [[nodiscard]] utl::usize ExtraSize() const;

        [[nodiscard]] utl::usize Size() const;

        void Update(Galaxy_ty_raw galaxy) override;
    };
} // namespace lgk
