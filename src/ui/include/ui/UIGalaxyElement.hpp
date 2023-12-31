//
// Purpur Tentakel
// 15.06.2023
//

#pragma once

#include "app/PlayerData.hpp"
#include <ui_lib/Focusable.hpp>
#include <ui_lib/Hover.hpp>
#include <ui_lib/UIElement.hpp>


namespace ui {
    class UIGalaxyElement : public uil::UIElement, public uil::Focusable {
    public:
        static constexpr utl::usize s_maxShipCount{ 300 };
        static constexpr utl::usize s_ringColorAlpha{ 100 };

    protected:
        utl::usize m_ID;
        app::PlayerData m_currentPlayer;
        Vector2 m_colliderPos;
        Color m_color;
        std::string m_stringID;
        uil::Hover m_hover;
        bool m_isEnabled{ true };
        std::function<void(UIGalaxyElement*)> m_onClick{ [](UIGalaxyElement*) {} };
        bool m_renderHover{ false };
        uil::CountRing_ty m_ring{ nullptr };

    public:
        UIGalaxyElement(
                utl::usize focusID,
                utl::usize ID,
                Vector2 size,
                app::PlayerData const& player,
                Vector2 pos,
                Vector2 colliderPos
        );

        void UpdatePosition(Rectangle newCollider);

        virtual void UpdateHoverText() = 0;

        void SetOnClick(std::function<void(UIGalaxyElement*)> onClick);

        void SetPlayer(app::PlayerData player);

        [[nodiscard]] app::PlayerData GetPlayer() const;

        void SetColor(Color color);

        [[nodiscard]] Color GetColor() const;

        [[nodiscard]] utl::usize GetID() const;

        [[nodiscard]] bool IsHover() const;

        void SetEnabled(bool isEnabled);

        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        virtual void RenderRing(app::AppContext_ty_c appContext) = 0;

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
