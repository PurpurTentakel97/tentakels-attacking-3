//
// Purpur Tentakel
// 16.06.2023
//

#pragma once
#include "helper/HLogicAlias.hpp"
#include "helper/HPlayerCollection.hpp"
#include "ui_lib/Hover.h"
#include "ui_lib/Line.h"
#include "ui_lib/UIElement.hpp"

class UIFleet final : public UIElement {
private:
    unsigned int m_ID;       ///< contains the logic ID
    PlayerData m_player;     ///< contains the current player data
    Vector2 m_relativeStart; ///< contains teh relative start of the line according to the galaxy
    Vector2 m_relativeEnd;   ///< contains teh relative end of the line according to the galaxy
    Fleet_ty_raw_c m_fleet;  ///< contains the logic Planet to this Planet
    std::function<bool(Vector2 const&)> m_isInGalaxyCollider; ///< returns if a point is in the galaxy collider
    Line m_line;                                              ///< contains the line for displaying
    Hover m_hover;                                            ///< contains the hover Element
    bool m_isDisplayAsPoint{ false }; ///< contains if the fleet gets displayed as point insted of a line
    CountRing_ty m_ring{ nullptr };   ///< contains the ring that indicates how many ships are on the planet

public:
    UIFleet(unsigned int ID,
            PlayerData player,
            Vector2 start,
            Vector2 end,
            Vector2 relativeStart,
            Vector2 relativeEnd,
            Fleet_ty_raw_c fleet,
            std::function<bool(Vector2 const&)> isInGalaxyCollider);

    /**
	 * return the logic ID
	 */
    [[nodiscard]] unsigned int GetID() const;
    /**
	 * checks if a point is colliding with the line.
	 */
    [[nodiscard]] bool IsColliding(Vector2 const& mousePosition) const;
    /**
	 * checks if the ring is colliding with a rectangle.
	 */
    [[nodiscard]] bool IsRingOverlappingWithRectangle(Rectangle const& rect) const;
    /**
	 * returns the player of the uifleet.
	 */
    [[nodiscard]] PlayerData GetPlayer() const;

    /**
	 * updates the hover text.
	 */
    void UpdateHoverText();

    /**
	 * updates the start and end positions
	 */
    void UpdatePositions(Rectangle newCollider);

    /**
	 * sets if the fleet gets displayed as point.
	 */
    void SetDisplayedAsPoint(bool isDisplayedAsPoint);
    /**
	 * returns if the fleet gets displayed as point.
	 */
    [[nodiscard]] bool IsDisplayAsPoint() const;

    /**
	 * calls the UIElement to Update.
	 * checks collision with line.
	 */
    virtual void CheckAndUpdate(Vector2 const&, AppContext_ty_c appContext);
    /**
	 * renders the line.
	 */
    void Render(AppContext_ty_c appContext) override;
    /**
	 * Renders the ring of the Element.
	 */
    void RenderRing(AppContext_ty_c appContext);
    /**
	 * calls UIElement to Resize.
	 * Resizes the line.
	 */
    void Resize(AppContext_ty_c appContext) override;
};
