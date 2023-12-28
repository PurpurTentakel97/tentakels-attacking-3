//
// Purpur Tentakel
// 31.08.2022
//

#pragma once
#include "Button.hpp"

class SliderButton final : public Button {
public:
    using Button::Button;
    using Button::operator=;

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
};
