//
// Purpur Tentakel
// 16.07.2023
//

#pragma once

#include "Button.hpp"
#include "Focusable.hpp"


namespace uil {
    class ToggleButton : public Button, public Focusable {
    private:
        bool m_isToggled{ false };

        std::function<void(bool, bool)> m_onToggle{ [](bool, bool) {} };

        void UpdateState();

    public:
        ToggleButton(
                utl::usize focusID,
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                std::string const& text,
                app::SoundType releaseSound
        );

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        [[nodiscard]] Rectangle GetCollider() const override;

        void SetEnabled(bool enabled) override;

        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] bool IsToggled() const;

        void SetToggleButton(bool isToggled);

        void SetOnToggle(std::function<void(bool, bool)> onToggle);
    };
} // namespace uil
