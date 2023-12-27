//
// Purpur Tentakel
// 04.09.2022
//

#pragma once
#include "Button.hpp"
#include "Focusable.hpp"


class ClassicButton final : public Button, public Focusable {
public:
    ClassicButton(
            unsigned int focusID,
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            std::string const& text,
            SoundType releaseSound
    );

    [[nodiscard]] bool IsEnabled() const override;

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;

    [[nodiscard]] Rectangle GetCollider() const override;
};
