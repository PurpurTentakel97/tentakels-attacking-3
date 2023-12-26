//
// Purpur Tentakel
// 15.06.2023
//

#pragma once
#include "helper/HPlayerData.hpp"
#include "ui_lib/Focusable.h"
#include "ui_lib/Hover.h"
#include "ui_lib/UIElement.hpp"

class UIGalaxyElement : public UIElement, public Focusable {
public:
    static constexpr int s_maxShipCount{ 300 };   ///< containts the maximum ship count the Count ring is refering to
    static constexpr int s_ringColorAlpha{ 100 }; ///< contains the alpha of the ring color

protected:
    unsigned int m_ID;          ///< contains the unique SpaceObject ID witch is also the SpaceObject "name"
    PlayerData m_currentPlayer; ///< contains the current player data that own the SpaceObject
    Vector2 m_colliderPos;      ///< the position of the collider
    Color m_color;              ///< contains the current color.
    std::string m_stringID;     ///< contains the ID as string
    Hover m_hover;              ///< contains the hover element
    bool m_isEnabled{ true };   ///< contains if the element is enabled
    std::function<void(UIGalaxyElement*)> m_onClick{ [](UIGalaxyElement*) {
    } };                            ///< contains on click that gets called when the planet is clicked
    bool m_renderHover{ false };    ///< contains if the hover text should be rendered
    CountRing_ty m_ring{ nullptr }; ///< contains the ring that indicates the ship count.

public:
    /**
	 * ctor.
	 * converts the id to a string.
	 */
    UIGalaxyElement(
            unsigned int focusID,
            unsigned int ID,
            Vector2 size,
            PlayerData player,
            Vector2 pos,
            Vector2 colliderPos
    );

    /**
	 * Updates the position with the collider position.
	 */
    void UpdatePosition(Rectangle newColider);

    /**
	 * updates the hover text
	 */
    virtual void UpdateHoverText() = 0;

    /**
	 * sets the onClick lambda that �gets called when the planet is clicked.
	 * provides this.
	 */
    void SetOnClick(std::function<void(UIGalaxyElement*)> onClick);

    /**
	 * sets a player the planet ist currently owning.
	 */
    void SetPlayer(PlayerData player);

    /**
	 * returns the current player of the UIPlanet.
	 */
    [[nodiscard]] PlayerData GetPlayer() const;

    /**
	 * sets a new color.
 	 */
    void SetColor(Color color);
    /**
	 * returns the current color.
	 */

    [[nodiscard]] Color GetColor() const;
    /**
	 * returns the unique id.
	 */
    [[nodiscard]] unsigned int GetID() const;

    /**
	 * returns if the mouse is currently over the planet.
	 */
    [[nodiscard]] bool IsHover() const;

    /**
	 * sets if the planets is enabled.
	 */
    void SetEnabled(bool isEnabled);
    /**
	 * returns if the planet is enabled.
	 */
    [[nodiscard]] bool IsEnabled() const override;

    /**
	 * return the current collider.
	 */
    [[nodiscard]] Rectangle GetCollider() const override;

    /**
	 * planet logic.
	 */
    virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override = 0;
    /**
	 * Renders the ring of the Element.
	 */
    virtual void RenderRing(AppContext_ty_c appContext) = 0;
    /**
	 * renders the planet.
	 */
    virtual void Render(AppContext_ty_c appContext) override = 0;
    /**
	 * resizes the planet.
	 * calls the hover text to resize.
	 */
    void Resize(AppContext_ty_c appContext) override;
};
