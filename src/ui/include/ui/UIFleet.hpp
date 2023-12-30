//
// Purpur Tentakel
// 16.06.2023
//

#pragma once

#include <alias/AliasLogic.hpp>
#include <app/PlayerCollection.hpp>
#include <ui_lib/Hover.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/UIElement.hpp>

class UIFleet final : public uil::UIElement {
private:
    unsigned int m_ID;
    app::PlayerData m_player;
    Vector2 m_relativeStart;
    Vector2 m_relativeEnd;
    lgk::Fleet_ty_raw_c m_fleet;
    std::function<bool(Vector2 const&)> m_isInGalaxyCollider;
    uil::Line m_line;
    uil::Hover m_hover;
    bool m_isDisplayAsPoint{ false };
    uil::CountRing_ty m_ring{ nullptr };

public:
    UIFleet(unsigned int ID,
            app::PlayerData const& player,
            Vector2 start,
            Vector2 end,
            Vector2 relativeStart,
            Vector2 relativeEnd,
            lgk::Fleet_ty_raw_c fleet,
            std::function<bool(Vector2 const&)> isInGalaxyCollider);

    [[nodiscard]] unsigned int GetID() const;

    [[nodiscard]] bool IsColliding(Vector2 const& mousePosition) const;

    [[nodiscard]] bool IsRingOverlappingWithRectangle(Rectangle const& rect) const;

    [[nodiscard]] app::PlayerData GetPlayer() const;

    void UpdateHoverText();

    void UpdatePositions(Rectangle newCollider);

    void SetDisplayedAsPoint(bool isDisplayedAsPoint);

    [[nodiscard]] bool IsDisplayAsPoint() const;

    void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void RenderRing(app::AppContext_ty_c appContext);

    void Resize(app::AppContext_ty_c appContext) override;
};
