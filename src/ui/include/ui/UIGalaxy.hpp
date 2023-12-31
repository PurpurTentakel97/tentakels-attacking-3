//
// Purpur Tentakel
// 12.11.2022
//

#pragma once

#include "app/PlayerData.hpp"
#include <alias/AliasEvent.hpp>
#include <alias/AliasUi.hpp>
#include <event/EventListener.hpp>
#include <functional>
#include <memory>
#include <ui_lib/Focusable.hpp>
#include <ui_lib/UIElement.hpp>
#include <vector>


namespace ui {
    class UIGalaxy final : public uil::UIElement, public eve::EventListener, public uil::Focusable {
    private:
        enum class Direction {
            UP,
            DOWN,
            LEFT,
            RIGHT,
        };
        bool m_isEnabled{ true };
        bool m_isScaling{ true };
        bool m_isScrollingByMouse{ false };
        bool m_isShowGalaxy{ false };
        bool m_isAcceptingInput{ false };

        float m_scaleFactor{ 1.0f };
        Vector2 m_lastMousePosition{ 0.0f, 0.0f };
        Rectangle m_absoluteSize{};
        lgk::Galaxy_ty_raw m_currentGalaxy{ nullptr };

        std::vector<UIGalaxyElement_ty> m_uiGalaxyElements;
        std::vector<UIPlanet_ty> m_uiPlanets;
        std::vector<UITargetPoint_ty> m_uiTargetPoints;
        std::vector<UIFleet_ty> m_uiFleets;

        std::function<void(float, Vector2)> m_onZoom{ [](float, Vector2) {} };
        std::function<void(float, bool)> m_onSlide{ [](float, bool) {} };
        std::function<void(utl::usize)> m_onUIGalaxyElementClick{ [](utl::usize) {} };

        bool m_updateLineDrag{ false };
        uil::LineDrag_ty m_lineDrag;

        void Initialize(eve::SendGalaxyPointerEvent const* event);

        [[nodiscard]] Vector2 GetAbsolutePosition(Vector2 pos, app::AppContext_ty_c appContext) const;

        [[nodiscard]] Vector2 GetRelativePosition(Vector2 pos, app::AppContext_ty_c appContext) const;

        [[nodiscard]] bool IsUIGalaxyElementInCollider(UIGalaxyElement_ty const& element) const;

        void UpdateUIGalaxyElementPosition();

        void SelectUIGalaxyElement(UIGalaxyElement* planet);

        void ClampsPositionAndSize();

        void PrepForOnSlide();

        void MoveByKey(Direction direction, float speed);

        void MoveByMouse(Vector2 mousePosition);

        [[nodiscard]] Vector2 GetCurrentScaleReference() const;

        [[nodiscard]] bool IsCollidingObjectPoint(Vector2 point) const;

        [[nodiscard]] utl::usize GetIDFromPoint(Vector2 point) const;

        [[nodiscard]] utl::vec2pos_ty GetCoordinatesFromPoint(Vector2 point) const;

        void HandleDragLineResult(Vector2 start, Vector2 end);

    public:
        UIGalaxy(
                utl::usize ID,
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                bool isShowGalaxy,
                bool isAcceptInput
        );

        ~UIGalaxy() override;

        void SetIsScaling(bool isScaling);

        [[nodiscard]] bool IsScaling() const;

        [[nodiscard]] float GetScaleFactor() const;

        void Zoom(bool zoomIn, int factor = 2);

        void Slide(float position, bool isHorizontal);

        void SetOnZoom(std::function<void(float, Vector2)> onZoom);

        void SetOnSlide(std::function<void(float, bool)> onSlide);

        void SetOnUIGalaxyElementClick(std::function<void(utl::usize)> onPlanetClick);

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;

        void FilterByCurrentPlayer(app::PlayerData const& player);

        void SetEnabled(bool isEnabled);

        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        [[nodiscard]] lgk::Galaxy_ty_raw GetGalaxy() const;

        void OnEvent(eve::Event const& event) override;
    };
} // namespace ui
