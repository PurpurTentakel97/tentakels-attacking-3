//
// Purpur Tentakel
// 24.08.2022
//

#pragma once
#include "Alignment.hpp"
#include <CustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <cmath>
#include <event/EventsUI.hpp>
#include <helper/HAssetType.hpp>
#include <helper/HSoundType.hpp>
#include <helper/HUIAlias.hpp>
#include <helper/HVector2Operator.hpp>
#include <numbers>


class UIElement {
protected:
    enum class MoveType {
        POINT_LINEAR,
        SPEED_LINEAR,
        POINT_ASYMPTOTIC,
        NONE,
    };
    MoveType m_moveType{ MoveType::NONE };
    Vector2 m_pos, m_size;

    Vector2 m_targetPosition{ 0.0f, 0.0f };
    Vector2 m_startingPosition{ 0.0f, 0.0f };
    Vector2 m_relativeSpeed{ 0.0f, 0.0f };
    float m_targetDiff{ 1.0f };

    Rectangle m_collider{};
    Alignment m_alignment;


    virtual void UpdateCollider() {
        Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        m_collider = { m_pos.x * resolution.x,
                       m_pos.y * resolution.y,
                       m_size.x * resolution.x,
                       m_size.y * resolution.y };
    }

    virtual void UpdateColliderReverse() {
        Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        m_pos = { m_collider.x / resolution.x, m_collider.y / resolution.y };
        m_size = { m_collider.width / resolution.x, m_collider.height / resolution.y };
    }

    void MovePointLinear() {
        if (m_moveType != MoveType::POINT_LINEAR) {
            return;
        }

        float const time{ GetFrameTime() };
        Vector2 const diff{ (m_targetPosition.x - m_startingPosition.x) * m_relativeSpeed.x * time,
                            (m_targetPosition.y - m_startingPosition.y) * m_relativeSpeed.y * time };
        Move(diff);
    }

    void MovePointAsymptotic() {

        if (m_moveType != MoveType::POINT_ASYMPTOTIC) {
            return;
        }

        float const time{ GetFrameTime() };
        Vector2 const diff{ (m_targetPosition.x - m_pos.x) * m_relativeSpeed.x * time,
                            (m_targetPosition.y - m_pos.y) * m_relativeSpeed.y * time };
        Move(diff);
    }

    void MoveSpeedLinear() {
        if (m_moveType != MoveType::SPEED_LINEAR) {
            return;
        }

        float const time{ GetFrameTime() };
        Vector2 const diff{ m_relativeSpeed.x * time, m_relativeSpeed.y * time };
        Move(diff);
    }

    void Move(Vector2 const offset) {
        m_pos = { m_pos.x + offset.x, m_pos.y + offset.y };

        UpdateCollider();
        CheckStopMoving();
    }

    void CheckStopMoving() {
        if (m_moveType == MoveType::SPEED_LINEAR or m_moveType == MoveType::NONE) {
            return;
        }

        Vector2 const diffVec{ m_targetPosition - m_pos };
        float const diff{ hlp::LenVec2(diffVec) };

        bool const stopMoving{ diffVec.x < 0.001f and diffVec.x > -0.001f and diffVec.y < 0.001f
                               and diffVec.y > -0.001f };

        if (diff > m_targetDiff or stopMoving) {
            m_pos = m_targetPosition;
            UpdateCollider();
            StopMoving();
        } else {
            m_targetDiff = diff;
        }
    }

public:
    UIElement(Vector2 const pos, Vector2 const size, Alignment const alignment) : m_pos{ pos }, m_size{ size }, m_alignment{ alignment } {

        m_collider = GetAlignedCollider(m_pos, m_size, alignment);
    }

    virtual ~UIElement() = default;

    [[nodiscard]] bool IsMoving() const {
        return m_moveType != MoveType::NONE;
    }

    [[nodiscard]] Alignment GetAlignment() const {
        return m_alignment;
    }

    virtual void SetPosition(Vector2 const pos) {
        m_pos = pos;
        m_collider = GetAlignedCollider(m_pos, m_size, m_alignment);
    }

    virtual void SetPositionUnaligned(Vector2 pos) {
        m_pos = pos;
        UpdateCollider();
    }

    [[nodiscard]] Vector2 GetPosition() const {
        return m_pos;
    }

    virtual void SetSize(Vector2 size) {
        m_size = size;
        UpdateCollider();
    }

    [[nodiscard]] Vector2 GetSize() const {
        return m_size;
    }

    virtual void SetCollider(Rectangle const collider) {
        m_collider = collider;
        UpdateColliderReverse();
    }

    [[nodiscard]] Rectangle GetCollider() const {
        return m_collider;
    }

    virtual void MoveBySpeed(float const relativeSpeed, float const angle) {
        m_moveType = MoveType::SPEED_LINEAR;
        m_targetPosition = { 0.0f, 0.0f };
        m_startingPosition = { 0.0f, 0.0f };

        float const tau{ std::numbers::pi_v<float> * 2.0f };

        float const speedX{ std::sin(angle * tau / 360.0f) * relativeSpeed };
        float const speedY{ -(std::cos(angle * tau / 360.0f) * relativeSpeed) };

        m_relativeSpeed = { speedX, speedY };
    }

    virtual void MoveToPositionLinear(Vector2 const position, float const relativeSpeed) {
        StopMoving();
        m_moveType = MoveType::POINT_LINEAR;
        m_startingPosition = m_pos;
        m_targetPosition = GetAlignedPosition(m_alignment, position, m_size);
        m_relativeSpeed = { relativeSpeed, relativeSpeed };
    }

    virtual void MoveToPositionAsymptotic(Vector2 const position, float const relativeSpeed) {
        StopMoving();
        m_moveType = MoveType::POINT_ASYMPTOTIC;
        m_startingPosition = m_pos;
        m_targetPosition = GetAlignedPosition(m_alignment, position, m_size);
        m_relativeSpeed = { relativeSpeed, relativeSpeed };
    }

    virtual void StopMoving() {
        m_moveType = MoveType::NONE;
        m_startingPosition = { 0.0f, 0.0f };
        m_targetPosition = { 0.0f, 0.0f };
        m_relativeSpeed = { 0.0f, 0.0f };
        m_targetDiff = 1.0f;
    }

    void UpdateMove() {
        switch (m_moveType) {
            default:
            case MoveType::NONE:
                break;
            case MoveType::POINT_LINEAR:
                MovePointLinear();
                break;
            case MoveType::POINT_ASYMPTOTIC:
                MovePointAsymptotic();
                break;
            case MoveType::SPEED_LINEAR:
                MoveSpeedLinear();
                break;
        }
    }

    virtual void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c) {
        UpdateMove();
    }

    virtual void Render(app::AppContext_ty_c appContext) = 0;

    virtual void Resize(app::AppContext_ty_c) {
        UpdateCollider();
    };
};
