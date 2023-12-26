//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "Alignment.h"
#include "AppContext.hpp"
#include "CustomRaylib.h"
#include "event/EventsUI.hpp"
#include "helper/HAssetType.hpp"
#include "helper/HSoundType.hpp"
#include "helper/HUIAlias.hpp"
#include "helper/HVector2Operator.h"
#include <cmath>
#include <numbers>


/**
 * provides the basic UIElement.
 * all elements in the ui should implement this.
 */
class UIElement {
protected:
	enum class MoveType { ///< contains the possible movement types of the element
		POINT_LINEAR,
		SPEED_LINEAR,
		POINT_ASYNPTOTIC,
		NONE,
	};
	MoveType m_moveType{ MoveType::NONE }; ///< contains the current movement type.
	Vector2 m_pos, m_size; ///< contains the relative position (top left) and size on the screen
	
	Vector2 m_targetPosition{ 0.0f,0.0f }; ///< contains the target position the element is moving to
	Vector2 m_startingPosition{ 0.0f,0.0f }; ///< contains the atsrting position the element is moving from
	Vector2 m_relativeSpeed{ 0.0f, 0.0f }; ///< contains the speed the element is moving with
	float m_targetDiff{ 1.0f }; ///< contains the difference between the target position and the current position of the last tick
	
	Rectangle m_collider;  ///< contains the absolute position (top left) and size on the screen
	Alignment m_alignment; ///< contains the alignment of the element

	/**
	 * calculates the absolute position and size out of the relative position and size and the current resolution.
	 */
	virtual void UpdateCollider() {
		Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
		m_collider = {
			m_pos.x  * resolution.x,
			m_pos.y  * resolution.y,
			m_size.x * resolution.x,
			m_size.y * resolution.y
		};
	}
	/**
	 * calculates the relative position and size out of the absolute position and size and the current resolution.
	 */
	virtual void UpdateColliderReverse() {
		Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
		m_pos = {
			m_collider.x / resolution.x,
			m_collider.y / resolution.y
		};
		m_size = {
			m_collider.width  / resolution.x,
			m_collider.height / resolution.y
		};
	}

	/**
	 * moves the element to the set position in a linear way.
	 */
	void MovePointLinear() {
		if (m_moveType != MoveType::POINT_LINEAR) { return; }

		float const time{ GetFrameTime() };
		Vector2 const diff{
			(m_targetPosition.x - m_startingPosition.x) * m_relativeSpeed.x * time,
			(m_targetPosition.y - m_startingPosition.y) * m_relativeSpeed.y * time
		};
		Move(diff);
	}
	/**
	 * moves the element to the set position in a asymptotic way.
	 */
	void MovePointAsymptotic() {

		if (m_moveType != MoveType::POINT_ASYNPTOTIC) { return; }

		float const time{ GetFrameTime() };
		Vector2 const diff{
			(m_targetPosition.x - m_pos.x) * m_relativeSpeed.x * time,
			(m_targetPosition.y - m_pos.y) * m_relativeSpeed.y * time
		};
		Move(diff);
	}
	/**
	 * moves the element at a certain speed in a linear way.
	 */
	void MoveSpeedLinear() {
		if (m_moveType != MoveType::SPEED_LINEAR) { return; }

		float const time{ GetFrameTime() };
		Vector2 const diff{
			m_relativeSpeed.x * time,
			m_relativeSpeed.y * time
		};
		Move(diff);
	}
	/**
	 * moves the element by the offset.
	 */
	void Move(Vector2 offset) {
		m_pos = {
			m_pos.x + offset.x,
			m_pos.y + offset.y
		};

		UpdateCollider();
		CheckStopMoving();
	}
	/**
	 * checks if the element has arrived at the target point.
	 * if so it claps the current position and stops the movement.
	 */
	void CheckStopMoving() {
		if (m_moveType == MoveType::SPEED_LINEAR 
			or m_moveType == MoveType::NONE) { return; }

		Vector2 const diffVec{ m_targetPosition - m_pos };
		float const diff{ LenVec2(diffVec) };

		bool const stopMoving{
				diffVec.x < 0.001f
			and diffVec.x > -0.001f
			and diffVec.y < 0.001f
			and diffVec.y > -0.001f 
		};

		if (diff > m_targetDiff
			or stopMoving) {
			m_pos = m_targetPosition;
			UpdateCollider();
			StopMoving();
		}
		else {
			m_targetDiff = diff;
		}
	}

public:
	/**
	 * ctor.
	 * calls the aligned collider.
	 */
	UIElement(Vector2 pos, Vector2 size, Alignment alignment)
		: m_pos{ pos }, m_size{ size }, m_alignment{ alignment } {
		
		m_collider = GetAlignedCollider(m_pos, m_size, alignment);
	}
	/**
	 * default virtual dtor.
	 */
	virtual ~UIElement() = default;

	/**
	 * returns if the element is currently moving
	 */
	[[nodiscard]] bool IsMoving() const {
		return m_moveType != MoveType::NONE;
	}
	/**
	 * returns the current alignment.
	 */
	[[nodiscard]] Alignment GetAlignment() const {
		return m_alignment;
	}
	/**
	 * sets a new relative position.
	 * calls to update and align the collider.
	 */
	virtual void SetPosition(Vector2 pos) {
		m_pos = pos;
		m_collider = GetAlignedCollider(m_pos, m_size, m_alignment);
	}
	/**
	 * sets a new relative position.
	 * calls to update the collider.
	 */
	virtual void SetPositionUnaligned(Vector2 pos) {
		m_pos = pos;
		UpdateCollider();
	}
	/**
	 * returns the current relative position. 
	 */
	[[nodiscard]] Vector2 GetPosition() const {
		return m_pos;
	}
	/**
	 * sets a new relative size.
	 * calls to update the collider.
	 */
	virtual void SetSize(Vector2 size) {
		m_size = size;
		UpdateCollider();
	}
	/**
	 * returns the current relative size.
	 */
	[[nodiscard]] Vector2 GetSize() const {
		return m_size;
	}
	/**
	 * sets a new absolute position and size.
	 * calls to update the relative position and size.
	 */
	virtual void SetCollider(Rectangle collider) {
		m_collider = collider;
		UpdateColliderReverse();
	}
	/**
	 * returns the current absolute position and size.
	 */
	[[nodiscard]] Rectangle GetCollider() const {
		return m_collider;
	}

	/**
	 * moves the element at a certain speed in a certain direction until it gets stoppt by StopMoving().
	 * result is a linear movement in one direction.
	 * the angle is clockwise.
	 */
	virtual void MoveBySpeed(float relativeSpeed, float angle) {
		m_moveType = MoveType::SPEED_LINEAR;
		m_targetPosition = { 0.0f,0.0f };
		m_startingPosition = { 0.0f,0.0f };

		float const tau{ std::numbers::pi_v<float> *2.0f };

		float const speedX{ std::sin(angle * tau / 360.0f) * relativeSpeed };
		float const speedY{ -(std::cos(angle * tau / 360.0f) * relativeSpeed) };

		m_relativeSpeed = { speedX, speedY };
	}
	/**
	 * moves the element to the provided position at the provided speed.
	 * result ia a linear movement in one direction.
	 */
	virtual void MoveToPositionLinear(Vector2 position, float relativeSpeed) {
		StopMoving();
		m_moveType = MoveType::POINT_LINEAR;
		m_startingPosition = m_pos;
		m_targetPosition = GetAlignedPosition(m_alignment, position, m_size);
		m_relativeSpeed = { relativeSpeed, relativeSpeed };
	}
	/**
	 * moves the element to the provided position at the provided speed.
	 * result is an asymptotic movement in one direction.
	 */
	virtual void MoveToPositionAsymptotic(Vector2 position, float relativeSpeed) {
		StopMoving();
		m_moveType = MoveType::POINT_ASYNPTOTIC;
		m_startingPosition = m_pos;
		m_targetPosition = GetAlignedPosition(m_alignment, position, m_size);
		m_relativeSpeed = { relativeSpeed, relativeSpeed };
	}
	/**
	 * stops all kinds off movements immediately.
	 * resets all moving related values.
	 */
	virtual void StopMoving() {
		m_moveType = MoveType::NONE;
		m_startingPosition = { 0.0f,0.0f };
		m_targetPosition = { 0.0f,0.0f };
		m_relativeSpeed = { 0.0f,0.0f };
		m_targetDiff = 1.0f;
	}

	/**
	 * updates the movement event if CheckAndUpdate is not called.
	 * it is not recommended to call this and CheckAndUpdate.
	 */
	void UpdateMove() {
				switch (m_moveType) {
			default:
			case MoveType::NONE:
				break;
			case MoveType::POINT_LINEAR:
				MovePointLinear();
				break;
			case MoveType::POINT_ASYNPTOTIC:
				MovePointAsymptotic();
				break;
			case MoveType::SPEED_LINEAR:
				MoveSpeedLinear();
				break;
		}
	}

	/**
	 * checks if there is a current movement.
	 * calls the element to move
	 */
	virtual void CheckAndUpdate(Vector2 const&, AppContext_ty_c) {
		UpdateMove();
	}
	/**
	 * just virtual.
	 * to implement.
	 * should render the element.
	 */
	virtual void Render(AppContext_ty_c appContext) = 0;
	/**
	 * sets new resolution.
	 * calls update collider.
	 */
	virtual void Resize(AppContext_ty_c) {
		UpdateCollider();
	};
};
