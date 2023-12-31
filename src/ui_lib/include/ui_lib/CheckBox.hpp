//
// Purpur Tentakel
// 23.10.2022
//

#pragma once

#include "Focusable.hpp"
#include "UIElement.hpp"
#include <functional>


namespace uil {
    class CheckBox final : public UIElement, public Focusable {
    private:
        bool m_isEnabled{ true };
        bool m_isChecked{ false };
        bool m_isHovered{ false };

        utl::usize m_ID;

        Texture* m_texture;
        Rectangle m_textureRec{};

        std::function<void(utl::usize, bool)> m_onCheck{ [](utl::usize, bool) {} };


        void Check(app::AppContext_ty_c appContext);

    public:
        CheckBox(utl::usize focusID, Vector2 pos, float height, Alignment alignment, utl::usize checkBoxID);

        void SetOnCheck(std::function<void(utl::usize, bool)> onCheck);

        [[nodiscard]] utl::usize GetID() const;

        void SetChecked(bool isChecked);

        [[nodiscard]] bool IsChecked() const;

        void SetEnabled(bool isEnabled);

        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
