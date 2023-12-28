//
// Purpur Tentakel
// 16.06.2023
//

#pragma once
#include <helper/HLogicAlias.hpp>
#include <helper/HPlayerCollection.hpp>
#include <ui_lib/Hover.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/UIElement.hpp>

class UIFleet final : public UIElement {
private:
    unsigned int m_ID;
    PlayerData m_player;
    Vector2 m_relativeStart;
    Vector2 m_relativeEnd;
    Fleet_ty_raw_c m_fleet;
    std::function<bool(Vector2 const&)> m_isInGalaxyCollider;
    Line m_line;
    Hover m_hover;
    bool m_isDisplayAsPoint{ false };
    CountRing_ty m_ring{ nullptr };

public:
    UIFleet(unsigned int ID,
            PlayerData const& player,
            Vector2 start,
            Vector2 end,
            Vector2 relativeStart,
            Vector2 relativeEnd,
            Fleet_ty_raw_c fleet,
            std::function<bool(Vector2 const&)> isInGalaxyCollider);

    [[nodiscard]] unsigned int GetID() const;

    [[nodiscard]] bool IsColliding(Vector2 const& mousePosition) const;

    [[nodiscard]] bool IsRingOverlappingWithRectangle(Rectangle const& rect) const;

    [[nodiscard]] PlayerData GetPlayer() const;

    void UpdateHoverText();

    void UpdatePositions(Rectangle newCollider);

    void SetDisplayedAsPoint(bool isDisplayedAsPoint);

    [[nodiscard]] bool IsDisplayAsPoint() const;

    void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void RenderRing(app::AppContext_ty_c appContext);

    void Resize(app::AppContext_ty_c appContext) override;
};
