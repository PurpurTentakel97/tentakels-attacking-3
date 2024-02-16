//
// Purpur Tentakel
// 12.11.2022
//

#include "UIGalaxy.hpp"
#include "UIFleet.hpp"
#include "UIPlanet.hpp"
#include "UITargetPoint.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HInput.hpp>
#include <ui_lib/LineDrag.hpp>


namespace ui {
    void UIGalaxy::Initialize(eve::SendGalaxyRepresentationEvent const* const event) {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        m_currentGalaxy = { event->GetGalaxy() };

        // scale ui galaxy dimensions
        auto const ratioX{ static_cast<float>(m_collider.width) / static_cast<float>(m_currentGalaxy.size.x) };
        auto const ratioY{ static_cast<float>(m_collider.height) / static_cast<float>(m_currentGalaxy.size.y) };

        auto newCollider = m_collider;
        if (ratioY > ratioX) {
            auto const newHeight = newCollider.height / ratioY * ratioX;
            newCollider.y += newCollider.height - newHeight;
            newCollider.height = newHeight;
        } else {
            newCollider.width = newCollider.width / ratioX * ratioY;
        }

        newCollider.x += (m_collider.width - newCollider.width) / 2;
        newCollider.y -= (m_collider.height - newCollider.height) / 2;

        SetCollider(newCollider);
        m_absoluteSize = m_collider;

        // place space objects
        auto currentFocusID{ 1 };
        for (auto const& p : m_currentGalaxy.planets) {
            currentFocusID = static_cast<int>(p.ID);
            auto planet    = std::make_shared<UIPlanet>(currentFocusID,
                                                     p.ID,
                                                     appContext.playerCollection.GetPlayerOrNpcByID(p.playerID),
                                                     GetAbsolutePosition(
                                                             {
                                                                     static_cast<float>(p.position.x),
                                                                     static_cast<float>(p.position.y),
                                                             },
                                                             appContext),
                                                     GetRelativePosition(
                                                             {
                                                                     static_cast<float>(p.position.x),
                                                                     static_cast<float>(p.position.y),
                                                             },
                                                             appContext),
                                                     p);
            planet->SetOnClick([this](UIGalaxyElement* p_) { this->SelectUIGalaxyElement(p_); });
            planet->UpdatePosition(m_absoluteSize);
            m_uiGalaxyElements.push_back(planet);
            m_uiPlanets.push_back(planet);
        }
        for (auto const& t : m_currentGalaxy.targetPoints) {
            ++currentFocusID;
            auto point = std::make_shared<UITargetPoint>(currentFocusID,
                                                         t.ID,
                                                         appContext.playerCollection.GetPlayerOrNpcByID(t.playerID),
                                                         GetAbsolutePosition(
                                                                 {
                                                                         static_cast<float>(t.position.x),
                                                                         static_cast<float>(t.position.y),
                                                                 },
                                                                 appContext),
                                                         GetRelativePosition(
                                                                 {
                                                                         static_cast<float>(t.position.x),
                                                                         static_cast<float>(t.position.y),
                                                                 },
                                                                 appContext),
                                                         t);
            point->SetOnClick([this](UIGalaxyElement* p) { this->SelectUIGalaxyElement(p); });
            point->UpdatePosition(m_absoluteSize);
            m_uiTargetPoints.push_back(point);
            m_uiGalaxyElements.push_back(point);
        }
        for (auto const& f : m_currentGalaxy.fleets) {
            auto fleet = std::make_shared<UIFleet>(
                    f.ID,
                    appContext.playerCollection.GetPlayerOrNpcByID(f.playerID),
                    GetAbsolutePosition({ static_cast<float>(f.position.x), static_cast<float>(f.position.y) },
                                        appContext),
                    GetAbsolutePosition({ static_cast<float>(f.destRepresentation.position.x),
                                          static_cast<float>(f.destRepresentation.position.y) },
                                        appContext),
                    GetRelativePosition({ static_cast<float>(f.position.x), static_cast<float>(f.position.y) },
                                        appContext),
                    GetRelativePosition({ static_cast<float>(f.destRepresentation.position.x),
                                          static_cast<float>(f.destRepresentation.position.y) },
                                        appContext),
                    f,
                    [this](Vector2 const& mousePosition) {
                        return CheckCollisionPointRec(mousePosition, this->m_collider);
                    });
            m_uiFleets.push_back(fleet);
        }
        m_onZoom(1.0f, GetCurrentScaleReference());
    }

    Vector2 UIGalaxy::GetAbsolutePosition(Vector2 const pos, app::AppContext_ty_c appContext) const {
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 const newPos{
            (m_collider.x) / resolution.x,
            (m_collider.y) / resolution.y,
        };
        Vector2 const newSize{
            (m_collider.width) / resolution.x,
            (m_collider.height) / resolution.y,
        };
        if (m_isShowGalaxy) {
            return {
                newPos.x + pos.x / static_cast<float>(appContext.constants.world.showDimensionX) * newSize.x,
                newPos.y + pos.y / static_cast<float>(appContext.constants.world.showDimensionY) * newSize.y,
            };
        } else {
            return {
                newPos.x + pos.x / static_cast<float>(appContext.constants.world.currentDimensionX) * newSize.x,
                newPos.y + pos.y / static_cast<float>(appContext.constants.world.currentDimensionY) * newSize.y,
            };
        }
    }

    Vector2 UIGalaxy::GetRelativePosition(Vector2 const pos, app::AppContext_ty_c appContext) const {
        if (m_isShowGalaxy) {
            return {
                pos.x / static_cast<float>(appContext.constants.world.showDimensionX),
                pos.y / static_cast<float>(appContext.constants.world.showDimensionY),
            };
        } else {
            return {
                pos.x / static_cast<float>(appContext.constants.world.currentDimensionX),
                pos.y / static_cast<float>(appContext.constants.world.currentDimensionY),
            };
        }
    }

    bool UIGalaxy::IsUIGalaxyElementInCollider(UIGalaxyElement_ty const& element, Rectangle const& col) const {
        auto const elementCollider = element->GetCollider();

        if (elementCollider.x + elementCollider.width <= col.x) {
            return false;
        }
        if (elementCollider.y + elementCollider.height <= col.y) {
            return false;
        }
        if (elementCollider.x >= col.x + col.width) {
            return false;
        }
        if (elementCollider.y >= col.y + col.height) {
            return false;
        }

        return true;
    }

    void UIGalaxy::UpdateUIGalaxyElementPosition() {
        for (auto const& e : m_uiGalaxyElements) {
            e->UpdatePosition(m_absoluteSize);
        }
        for (auto const& f : m_uiFleets) {
            f->UpdatePositions(m_absoluteSize);
        }
    }

    void UIGalaxy::SelectUIGalaxyElement(UIGalaxyElement* const planet) {
        m_onUIGalaxyElementClick(planet->GetID());
    }

    void UIGalaxy::ClampsPositionAndSize() {
        m_absoluteSize.x = m_absoluteSize.x < m_collider.x ? m_absoluteSize.x : m_collider.x;

        m_absoluteSize.x = m_absoluteSize.x + m_absoluteSize.width > m_collider.x + m_collider.width
                                 ? m_absoluteSize.x
                                 : m_collider.x + m_collider.width - m_absoluteSize.width;

        m_absoluteSize.y = m_absoluteSize.y < m_collider.y ? m_absoluteSize.y : m_collider.y;

        m_absoluteSize.y = m_absoluteSize.y + m_absoluteSize.height > m_collider.y + m_collider.height
                                 ? m_absoluteSize.y
                                 : m_collider.y + m_collider.height - m_absoluteSize.height;
    }

    void UIGalaxy::PrepForOnSlide() {
        float difference{ m_absoluteSize.width - m_collider.width };
        float offset{ m_collider.x - m_absoluteSize.x };
        float percent{ offset / difference * 100 };
        m_onSlide(percent, true);

        difference = m_absoluteSize.height - m_collider.height;
        offset     = m_collider.y - m_absoluteSize.y;
        percent    = offset / difference * 100;
        m_onSlide(percent, false);
    }

    void UIGalaxy::MoveByKey(Direction const direction, float const speed) {
        float difference;
        float offset;
        float percent;

        switch (direction) {
            case Direction::UP:
                difference = m_absoluteSize.height - m_collider.height;
                offset     = m_collider.y - m_absoluteSize.y;
                percent    = offset / difference * 100 + speed;
                Slide(percent, false);
                break;
            case Direction::DOWN:
                difference = m_absoluteSize.height - m_collider.height;
                offset     = m_collider.y - m_absoluteSize.y;
                percent    = offset / difference * 100 - speed;
                Slide(percent, false);
                break;
            case Direction::LEFT:
                difference = m_absoluteSize.width - m_collider.width;
                offset     = m_collider.x - m_absoluteSize.x;
                percent    = offset / difference * 100 + speed;
                Slide(percent, true);
                break;
            case Direction::RIGHT:
                difference = m_absoluteSize.width - m_collider.width;
                offset     = m_collider.x - m_absoluteSize.x;
                percent    = offset / difference * 100 - speed;
                Slide(percent, true);
                break;
        }
        ClampsPositionAndSize();
        UpdateUIGalaxyElementPosition();
    }

    void UIGalaxy::MoveByMouse(Vector2 const mousePosition) {
        if (m_lastMousePosition.x == 0.0f && m_lastMousePosition.y == 0.0f) {
            m_lastMousePosition = mousePosition;
            return;
        }

        m_absoluteSize.x -= m_lastMousePosition.x - mousePosition.x;
        m_absoluteSize.y -= m_lastMousePosition.y - mousePosition.y;

        m_lastMousePosition = mousePosition;

        ClampsPositionAndSize();
        PrepForOnSlide();
        UpdateUIGalaxyElementPosition();
    }

    Vector2 UIGalaxy::GetCurrentScaleReference() const {
        return { m_absoluteSize.width / static_cast<float>(m_currentGalaxy.size.x * 10),
                 m_absoluteSize.height / static_cast<float>(m_currentGalaxy.size.y * 10) };
    }

    bool UIGalaxy::IsCollidingObjectPoint(Vector2 const point) const {
        // don't check if point is in galaxy collider because the other planets get displayed on the edge of the collider
        for (auto const& p : m_uiPlanets) {
            auto const& collider{ p->GetCollider() };
            if (CheckCollisionPointRec(point, collider)) {
                return true;
            }
        }
        for (auto const& tp : m_uiTargetPoints) {
            auto const& collider{ tp->GetCollider() };
            if (CheckCollisionPointRec(point, collider)) {
                return true;
            }
        }

        for (auto const& f : m_uiFleets) {
            if (f->IsColliding(point)) {
                return true;
            }
        }

        return false;
    }

    utl::usize UIGalaxy::GetIDFromPoint(Vector2 const point) const {
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 absolutePoint{ resolution.x * point.x, resolution.y * point.y };
        // don't check if point is in galaxy collider because the other planets get displayed on the edge of the collider

        for (auto const& p : m_uiPlanets) {
            if (CheckCollisionPointRec(absolutePoint, p->GetCollider())) {
                return p->GetID();
            }
        }
        for (auto const& tp : m_uiTargetPoints) {
            if (CheckCollisionPointRec(absolutePoint, tp->GetCollider())) {
                return tp->GetID();
            }
        }
        for (auto const& f : m_uiFleets) {
            if (f->IsColliding(absolutePoint)) {
                return f->GetID();
            }
        }
        return 0;
    }

    utl::vec2pos_ty UIGalaxy::GetCoordinatesFromPoint(Vector2 const point) const {
        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 const absolutePoint{ resolution.x * point.x, resolution.y * point.y };
        if (!CheckCollisionPointRec(absolutePoint, m_collider)) {
            return { 0, 0 };
        }

        auto const galaxySize{ m_currentGalaxy.size };
        auto const relative = hlp::GetElementPositionReversed(
                { m_absoluteSize.x, m_absoluteSize.y }, { m_absoluteSize.width, m_absoluteSize.height }, absolutePoint);
        return { static_cast<int>(relative.x * static_cast<float>(galaxySize.x)),
                 static_cast<int>(relative.y * static_cast<float>(galaxySize.y)) };
    }

    void UIGalaxy::HandleDragLineResult(Vector2 const start, Vector2 const end) {
        auto const originID{ GetIDFromPoint(start) };
        auto const destID{ GetIDFromPoint(end) };
        utl::vec2pos_ty destCo{ 0, 0 };
        if (destID <= 0) {
            destCo = GetCoordinatesFromPoint(end);
        }

        m_updateLineDrag = false;

        eve::DragLineFleetInstructionEvent const event{ originID, destID, destCo };
        app::AppContext::GetInstance().eventManager.InvokeEvent(event);
    }

    UIGalaxy::UIGalaxy(utl::usize const ID,
                       Vector2 const pos,
                       Vector2 const size,
                       uil::Alignment const alignment,
                       bool const isShowGalaxy,
                       bool const isAcceptInput)
        : UIElement{ pos, size, alignment },
          Focusable{ ID },
          m_isShowGalaxy{ isShowGalaxy },
          m_isAcceptingInput{ isAcceptInput } {
        m_absoluteSize    = m_collider;
        m_renderRectangle = m_collider;

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.eventManager.AddListener(this);

        m_lineDrag = std::make_shared<uil::LineDrag>(
                2.0f, WHITE, [this](Vector2 start, Vector2 end) -> void { this->HandleDragLineResult(start, end); });

        if (isShowGalaxy) {
            eve::GetShowGalaxyPointerEvent event;
            appContext.eventManager.InvokeEvent(event);
        } else {
            eve::GetGalaxyPointerEvent event;
            appContext.eventManager.InvokeEvent(event);
        }
    }

    UIGalaxy::~UIGalaxy() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void UIGalaxy::SetIsScaling(bool const isScaling) {
        m_isScaling = isScaling;
    }

    bool UIGalaxy::IsScaling() const {
        return m_isScaling;
    }

    float UIGalaxy::GetScaleFactor() const {
        return m_scaleFactor;
    }

    void UIGalaxy::Zoom(bool const zoomIn, utl::usize const factor) {
        if (!m_isScaling) {
            return;
        }

        if (zoomIn) {
            m_scaleFactor *= 1.0f + 0.01f * static_cast<float>(factor);
        } else {
            m_scaleFactor *= 1.0f - 0.01f * static_cast<float>(factor);
        }

        if (m_scaleFactor < 1.0f) {
            m_scaleFactor = 1.0f;
        }
        if (m_scaleFactor > 7.5f) {
            m_scaleFactor = 7.5f;
        }

        Rectangle newSize{
            m_absoluteSize.x,
            m_absoluteSize.y,
            m_collider.width * m_scaleFactor,
            m_collider.height * m_scaleFactor,
        };

        Vector2 const difference{
            newSize.width - m_absoluteSize.width,
            newSize.height - m_absoluteSize.height,
        };

        Vector2 mouseFactor{ 0.5f, 0.5f };
        Vector2 const mousePosition{ GetMousePosition() };
        if (CheckCollisionPointRec(mousePosition, m_collider)) {
            mouseFactor.x = (mousePosition.x - m_collider.x) / m_collider.width;
            mouseFactor.y = (mousePosition.y - m_collider.y) / m_collider.height;
        }

        newSize.x -= difference.x * mouseFactor.x;
        newSize.y -= difference.y * mouseFactor.y;

        m_absoluteSize = newSize;

        ClampsPositionAndSize();

        m_onZoom(m_scaleFactor, GetCurrentScaleReference());
        PrepForOnSlide();
        UpdateUIGalaxyElementPosition();
    }

    void UIGalaxy::Slide(float const position, bool const isHorizontal) {
        if (isHorizontal) {
            float const difference{ m_absoluteSize.width - m_collider.width };
            float const offset{ difference / 100 * position };
            m_absoluteSize.x = m_collider.x - offset;
        } else {
            float const difference{ m_absoluteSize.height - m_collider.height };
            float const offset{ difference / 100 * position };
            m_absoluteSize.y = m_collider.y - offset;
        }
        ClampsPositionAndSize();
        PrepForOnSlide();
        UpdateUIGalaxyElementPosition();
    }

    void UIGalaxy::SetOnZoom(std::function<void(float, Vector2)> onZoom) {
        m_onZoom = std::move(onZoom);
    }

    void UIGalaxy::SetOnSlide(std::function<void(float, bool)> onSlide) {
        m_onSlide = std::move(onSlide);
    }

    void UIGalaxy::SetOnUIGalaxyElementClick(std::function<void(utl::usize)> onUIGalaxyElementClick) {
        m_onUIGalaxyElementClick = std::move(onUIGalaxyElementClick);
    }

    void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        UIElement::CheckAndUpdate(mousePosition, appContext);

        if (m_isScaling) {
            if (!m_updateLineDrag) {
                // zoom
                if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
                    float const mouseWheel{ GetMouseWheelMove() };
                    if (mouseWheel != 0.0f) {
                        Zoom(mouseWheel > 0.0f, 5);
                    }
                }

                // move by keys
                if (IsKeyDown(KEY_UP)) {
                    MoveByKey(Direction::UP, 2.0f);
                }
                if (IsKeyDown(KEY_DOWN)) {
                    MoveByKey(Direction::DOWN, 2.0f);
                }
                if (IsKeyDown(KEY_LEFT)) {
                    MoveByKey(Direction::LEFT, 1.5f);
                }
                if (IsKeyDown(KEY_RIGHT)) {
                    MoveByKey(Direction::RIGHT, 1.5f);
                }
            }

            // move by mouse
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (m_isAcceptingInput and IsCollidingObjectPoint(mousePosition)) {
                    m_updateLineDrag = true;
                } else if (CheckCollisionPointRec(mousePosition, m_renderRectangle)) {
                    m_isScrollingByMouse = true;
                }
            }
            if (m_isScrollingByMouse) {
                MoveByMouse(mousePosition);
            }
            if (m_updateLineDrag) {
                m_lineDrag->CheckAndUpdate(mousePosition, appContext);
            }
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                m_lastMousePosition  = { 0.0f, 0.0f };
                m_isScrollingByMouse = false;
            }
        }

        if (m_isEnabled) {
            for (auto const& e : m_uiGalaxyElements) {

                if (IsUIGalaxyElementInCollider(e, m_renderRectangle) != e->IsEnabled()) {
                    e->SetEnabled(IsUIGalaxyElementInCollider(e, m_renderRectangle));
                    if (!IsUIGalaxyElementInCollider(e, m_renderRectangle) && e->IsFocused()) {
                        hlp::SelectNextFocusElement();
                    }
                }

                if (IsUIGalaxyElementInCollider(e, m_renderRectangle)) {
                    e->CheckAndUpdate(mousePosition, appContext);
                }
            }
            for (auto const& f : m_uiFleets) {
                f->CheckAndUpdate(mousePosition, appContext);
            }

            if (IsFocused() && !IsNestedFocus()) {
                if (hlp::IsConfirmInputPressed()) {
                    m_isNestedFocus = true;
                    hlp::AddFocusLayer();
                    for (auto const& e : m_uiGalaxyElements) {
                        hlp::AddFocusElement(e.get());
                    }
                }
            }

            if (IsNestedFocus()) {
                if (hlp::IsBackInputPressed() or !CheckCollisionPointRec(mousePosition, m_collider)) {
                    hlp::DeleteFocusLayer();
                    m_isNestedFocus = false;
                }
            }
        }
    }

    void UIGalaxy::Render(app::AppContext_ty_c appContext) {

        for (auto const& e : m_uiGalaxyElements) {
            if (IsUIGalaxyElementInCollider(e, m_renderRectangle)) {
                e->RenderRing(appContext);
            }
        }
        for (auto const& f : m_uiFleets) {
            if (f->IsRingOverlappingWithRectangle(m_renderRectangle)) {
                f->RenderRing(appContext);
            }
        }
        BeginScissorMode(static_cast<int>(m_renderRectangle.x),
                         static_cast<int>(m_renderRectangle.y),
                         static_cast<int>(m_renderRectangle.width),
                         static_cast<int>(m_renderRectangle.height));

        for (auto const& f : m_uiFleets) {
            f->Render(appContext);
        }

        EndScissorMode();

        for (auto const& p : m_uiPlanets) {
            if (IsUIGalaxyElementInCollider(p, m_renderRectangle)) {
                p->Render(appContext);
            }
        }
        for (auto const& t : m_uiTargetPoints) {
            if (IsUIGalaxyElementInCollider(t, m_renderRectangle)) {
                t->Render(appContext);
            }
        }

        if (m_updateLineDrag) {
            m_lineDrag->Render(appContext);
        }
    }

    void UIGalaxy::Resize(app::AppContext_ty_c appContext) {

        UIElement::Resize(appContext);
        m_lineDrag->Resize(appContext);

        cst::Resolution_ty_c resolution{ appContext.GetResolution() };
        m_absoluteSize = {
            m_absoluteSize.x / resolution.x * resolution.x,
            m_absoluteSize.y / resolution.y * resolution.y,
            m_absoluteSize.width / resolution.x * resolution.x,
            m_absoluteSize.height / resolution.y * resolution.y,
        };

        for (auto const& e : m_uiGalaxyElements) {
            e->Resize(appContext);
            e->UpdatePosition(m_absoluteSize);
        }
    }

    void UIGalaxy::FilterByCurrentPlayer(app::PlayerData const& player) {
        for (auto const& f : m_uiFleets) {
            f->SetDisplayedAsPoint(f->GetPlayer().ID != player.ID);
        }
    }

    void UIGalaxy::SetEnabled(bool const isEnabled) {
        m_isEnabled = isEnabled;
    }

    bool UIGalaxy::IsEnabled() const {
        return m_isEnabled;
    }

    Rectangle UIGalaxy::GetCollider() const {
        return UIElement::GetCollider();
    }

    utl::RepresentationGalaxy UIGalaxy::GetGalaxy() const {
        return m_currentGalaxy;
    }

    void UIGalaxy::OnEvent(eve::Event const& event) {

        if (auto const* galaxyEvent = dynamic_cast<eve::SendGalaxyRepresentationEvent const*>(&event)) {
            Initialize(galaxyEvent);
            return;
        }
    }
} // namespace ui
