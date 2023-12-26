//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "UIElement.hpp"
#include <vector>
#include <memory>

class UIManager;

class Scene: public UIElement {
protected:
	std::vector<std::shared_ptr<UIElement>> m_elements; ///< contains all ui elements of this scene with update
	std::vector<std::shared_ptr<UIElement>> m_elementsOutUpdates; ///< contains all ui elements of this scene without update
	bool m_active{ false }; ///< contains if the scene is currently active

	/**
	 * sets all elements in elements and elements out update active or inactive.
	 */
	void SetFocusActive(AppContext_ty_c appContext);

	/**
	 * calculates and returns the relative position in the scene
	 * by the provided relative position in the hole window.
	 */
	Vector2 GetElementPosition(float x, float y);
	/**
	 * calculates and returns the relative size in the scene
	 * by the provided relative size in the hole window.
	 */
	Vector2 GetElementSize(float x, float y);
	/**
	 * returns the focusable instance from the id.
	 * returns a nullptr if no instance with that id exists
	 */
	Focusable_ty_raw GetFocusableByFocusID(unsigned int ID) const;


public:
	/**
	 * ctor.
	 * only initialization.
	 */
	Scene(Vector2 pos, Vector2 size, Alignment alignment);

	/**
	 * returns if the scene is currently active.
	 */
	[[nodiscard]] bool IsActive() const;
	/**
	 * sets if the scene is currently active.
	 * calls set focus active.
	 */
	virtual void SetActive(bool active, AppContext_ty_c appContext);

	/**
	 * sets a new relative position in the scene.
	 * sets a new relative position for all elements in the scene.
	 */
	void SetPosition(Vector2 pos);
	/**
	 * sets a new relative size in the scene.
	 * sets a new relative size for all elements in the scene.
	 */
	void SetSize(Vector2 size);

	/**
	 * updates all elements in elements.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders all elements in elements and elements out update.
 	 */
	virtual void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes all elements in elements and elements out update.
	 */
	virtual void Resize(AppContext_ty_c appContext) override;

	/**
	 * moves the scene and all its elements by a certain speed to a certain direction.
	 * result is a linear movement.
	 * moved until it gets Stopped with StopMoving.
	 * the angle is clockwise.
	 */
	void MoveBySpeed(float relativeSpeed, float angle) override;
	/**
	 * moves the scene and all elements to the provided position.
	 * result is a linear movement.
	 * stops movement when the position is reached.
	 */
	void MoveToPositionLinear(Vector2 position, float relativeSpeed) override;
	/**
	 * moves the scene and all elements to the provided position.
	 * result is a asymptotic movement.
	 * stops movement when the position is reached.
	 */
	void MoveToPositionAsymptotic(Vector2 position, float relativeSpeed) override;
	/**
	 * Stopps every movement immediately.
	 * resets all movement parameters. 
	 */
	void StopMoving() override;
};
