//
// Purpur Tentakel
// 12.11.2022
//

#include "include/ui/UIGalaxy.h"
#include "AppContext.hpp"
#include "UIFleet.h"
#include "UIPlanet.h"
#include "UITargetPoint.h"
#include "event/EventGenerel.hpp"
#include "helper/HFocusEvents.hpp"
#include "helper/HInput.hpp"
#include "logic/Galaxy.h"
#include "logic/Player.h"
#include "ui_lib/LineDrag.h"

void UIGalaxy::Initialize(SendGalaxyPointerEvent const* event) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    Galaxy_ty_c_raw galaxy{ event->GetGalaxy() };

    m_currentGalaxy = galaxy;
    int currentFocusID{ 1 };
    for (auto const& p : galaxy->GetPlanets()) {
        currentFocusID = static_cast<int>(p->GetID());
        auto planet = std::make_shared<UIPlanet>(
                currentFocusID,
                p->GetID(),
                appContext.playerCollection.GetPlayerOrNpcByID(p->GetPlayer()->GetID()),
                GetAbsolutePosition(
                        {
                                static_cast<float>(p->GetPos().x),
                                static_cast<float>(p->GetPos().y),
                        },
                        appContext
                ),
                GetRelativePosition(
                        {
                                static_cast<float>(p->GetPos().x),
                                static_cast<float>(p->GetPos().y),
                        },
                        appContext
                ),
                p.get()
        );
        if (p->IsDestroyed()) {
            planet->SetEnabled(false);
            planet->SetColor(DARKGRAY);
        } else if (not p->GetPlayer()->IsHumanPlayer()) {
            if (not p->IsDiscovered() and not event->IsShowGalaxy()) {
                planet->SetColor(GRAY);
            }
        }
        planet->SetOnClick([this](UIGalaxyElement* p_) { this->SelectUIGalaxyElement(p_); });
        planet->UpdatePosition(m_absoluteSize);
        m_uiGalaxyElements.push_back(planet);
        m_uiPlanets.push_back(planet);
    }
    for (auto const& t : galaxy->GetTargetPoints()) {
        ++currentFocusID;
        auto point = std::make_shared<UITargetPoint>(
                currentFocusID,
                t->GetID(),
                appContext.playerCollection.GetPlayerOrNpcByID(t->GetPlayer()->GetID()),
                GetAbsolutePosition(
                        {
                                static_cast<float>(t->GetPos().x),
                                static_cast<float>(t->GetPos().y),
                        },
                        appContext
                ),
                GetRelativePosition(
                        {
                                static_cast<float>(t->GetPos().x),
                                static_cast<float>(t->GetPos().y),
                        },
                        appContext
                ),
                t.get()
        );
        point->SetOnClick([this](UIGalaxyElement* p) { this->SelectUIGalaxyElement(p); });
        point->UpdatePosition(m_absoluteSize);
        m_uiTargetPoints.push_back(point);
        m_uiGalaxyElements.push_back(point);
    }
    for (auto const& f : galaxy->GetFleets()) {
        auto fleet = std::make_shared<UIFleet>(
                f->GetID(),
                appContext.playerCollection.GetPlayerOrNpcByID(f->GetPlayer()->GetID()),
                GetAbsolutePosition(
                        { static_cast<float>(f->GetPos().x), static_cast<float>(f->GetPos().y) },
                        appContext
                ),
                GetAbsolutePosition(
                        { static_cast<float>(f->GetTarget()->GetPos().x),
                          static_cast<float>(f->GetTarget()->GetPos().y) },
                        appContext
                ),
                GetRelativePosition(
                        { static_cast<float>(f->GetPos().x), static_cast<float>(f->GetPos().y) },
                        appContext
                ),
                GetRelativePosition(
                        { static_cast<float>(f->GetTarget()->GetPos().x),
                          static_cast<float>(f->GetTarget()->GetPos().y) },
                        appContext
                ),
                f.get(),
                [this](Vector2 const& mousePosition) { return CheckCollisionPointRec(mousePosition, this->m_collider); }
        );
        m_uiFleets.push_back(fleet);
    }
    m_onZoom(1.0f, GetCurrentScaleReference());
}
Vector2 UIGalaxy::GetAbsolutePosition(Vector2 pos, AppContext_ty_c appContext) const {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
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
Vector2 UIGalaxy::GetRelativePosition(Vector2 pos, AppContext_ty_c appContext) const {
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

bool UIGalaxy::IsUIGalaxyElementInCollider(UIGalaxyElement_ty element) const {
    Rectangle const elementCollider{ element->GetCollider() };

    if (elementCollider.x + elementCollider.width <= m_collider.x) {
        return false;
    }
    if (elementCollider.y + elementCollider.height <= m_collider.y) {
        return false;
    }
    if (elementCollider.x >= m_collider.x + m_collider.width) {
        return false;
    }
    if (elementCollider.y >= m_collider.y + m_collider.height) {
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
void UIGalaxy::SelectUIGalaxyElement(UIGalaxyElement* planet) {
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
    float deferens{ m_absoluteSize.width - m_collider.width };
    float offset{ m_collider.x - m_absoluteSize.x };
    float percent{ offset / deferens * 100 };
    m_onSlide(percent, true);

    deferens = m_absoluteSize.height - m_collider.height;
    offset = m_collider.y - m_absoluteSize.y;
    percent = offset / deferens * 100;
    m_onSlide(percent, false);
}
void UIGalaxy::MoveByKey(Direction direction, float speed) {
    float deferens;
    float offset;
    float percent;

    switch (direction) {
        case Direction::UP:
            deferens = m_absoluteSize.height - m_collider.height;
            offset = m_collider.y - m_absoluteSize.y;
            percent = offset / deferens * 100 + speed;
            Slide(percent, false);
            break;
        case Direction::DOWN:
            deferens = m_absoluteSize.height - m_collider.height;
            offset = m_collider.y - m_absoluteSize.y;
            percent = offset / deferens * 100 - speed;
            Slide(percent, false);
            break;
        case Direction::LEFT:
            deferens = m_absoluteSize.width - m_collider.width;
            offset = m_collider.x - m_absoluteSize.x;
            percent = offset / deferens * 100 + speed;
            Slide(percent, true);
            break;
        case Direction::RIGHT:
            deferens = m_absoluteSize.width - m_collider.width;
            offset = m_collider.x - m_absoluteSize.x;
            percent = offset / deferens * 100 - speed;
            Slide(percent, true);
            break;
    }
    ClampsPositionAndSize();
    UpdateUIGalaxyElementPosition();
}
void UIGalaxy::MoveByMouse(Vector2 mousePosition) {
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
    return { m_absoluteSize.width / static_cast<float>(m_currentGalaxy->GetSize().x * 10),
             m_absoluteSize.height / static_cast<float>(m_currentGalaxy->GetSize().y * 10) };
}

bool UIGalaxy::IsCollidingObjectPoint(Vector2 point) const {
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
unsigned int UIGalaxy::GetIDFromPoint(Vector2 point) const {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
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
vec2pos_ty UIGalaxy::GetCoordinatesFromPoint(Vector2 point) const {
    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    Vector2 const absolutePoint{ resolution.x * point.x, resolution.y * point.y };
    if (!CheckCollisionPointRec(absolutePoint, m_collider)) {
        return { -1, -1 };
    }

    auto const galaxySize{ m_currentGalaxy->GetSize() };
    auto const relative = GetElementPositionReversed(
            { m_absoluteSize.x, m_absoluteSize.y },
            { m_absoluteSize.width, m_absoluteSize.height },
            absolutePoint
    );
    return { static_cast<int>(relative.x) * galaxySize.x, static_cast<int>(relative.y) * galaxySize.y };
}

void UIGalaxy::HandleDragLineResult(Vector2 start, Vector2 end) {
    auto const originID{ GetIDFromPoint(start) };
    auto const destID{ GetIDFromPoint(end) };
    vec2pos_ty destCo{ -1, -1 };
    if (destID <= 0) {
        destCo = GetCoordinatesFromPoint(end);
    }

    m_updateLineDrag = false;

    DragLineFleetInstructionEvent const event{ originID, destID, destCo };
    AppContext::GetInstance().eventManager.InvokeEvent(event);
}

UIGalaxy::UIGalaxy(
        unsigned int ID,
        Vector2 pos,
        Vector2 size,
        Alignment alignment,
        bool isShowGalaxy,
        bool isAcceptingInput
)
    : UIElement{ pos, size, alignment },
      Focusable{ ID },
      m_isShowGalaxy{ isShowGalaxy },
      m_isAcceptingInput{ isAcceptingInput } {
    m_absoluteSize = m_collider;

    AppContext_ty appContext{ AppContext::GetInstance() };
    appContext.eventManager.AddListener(this);

    m_lineDrag = std::make_shared<LineDrag>(2.0f, WHITE, [this](Vector2 start, Vector2 end) -> void {
        this->HandleDragLineResult(start, end);
    });

    if (isShowGalaxy) {
        GetShowGalaxyPointerEvent event;
        appContext.eventManager.InvokeEvent(event);
    } else {
        GetGalaxyPointerEvent event;
        appContext.eventManager.InvokeEvent(event);
    }
}
UIGalaxy::~UIGalaxy() {
    AppContext::GetInstance().eventManager.RemoveListener(this);
}

void UIGalaxy::SetIsScaling(bool isScaling) {
    m_isScaling = isScaling;
}
bool UIGalaxy::IsScaling() const {
    return m_isScaling;
}

float UIGalaxy::GetScaleFactor() const {
    return m_scaleFactor;
}

void UIGalaxy::Zoom(bool zoomIn, int factor) {
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

    Vector2 const deferens{
        newSize.width - m_absoluteSize.width,
        newSize.height - m_absoluteSize.height,
    };

    Vector2 mouseFactor{ 0.5f, 0.5f };
    Vector2 const mousePosition{ GetMousePosition() };
    if (CheckCollisionPointRec(mousePosition, m_collider)) {
        mouseFactor.x = (mousePosition.x - m_collider.x) / m_collider.width;
        mouseFactor.y = (mousePosition.y - m_collider.y) / m_collider.height;
    }

    newSize.x -= deferens.x * mouseFactor.x;
    newSize.y -= deferens.y * mouseFactor.y;

    m_absoluteSize = newSize;

    ClampsPositionAndSize();

    m_onZoom(m_scaleFactor, GetCurrentScaleReference());
    PrepForOnSlide();
    UpdateUIGalaxyElementPosition();
}
void UIGalaxy::Slide(float position, bool isHorizontal) {
    if (isHorizontal) {
        float const deferens{ m_absoluteSize.width - m_collider.width };
        float const offset{ deferens / 100 * position };
        m_absoluteSize.x = m_collider.x - offset;
    } else {
        float const deferens{ m_absoluteSize.height - m_collider.height };
        float const offset{ deferens / 100 * position };
        m_absoluteSize.y = m_collider.y - offset;
    }
    ClampsPositionAndSize();
    PrepForOnSlide();
    UpdateUIGalaxyElementPosition();
}

void UIGalaxy::SetOnZoom(std::function<void(float, Vector2)> onZoom) {
    m_onZoom = onZoom;
}
void UIGalaxy::SetOnSlide(std::function<void(float, bool)> onSlide) {
    m_onSlide = onSlide;
}
void UIGalaxy::SetOnUIGalaxyElementClick(std::function<void(unsigned int)> onUIGalaxyElementClick) {
    m_onUIGalaxyElementClick = onUIGalaxyElementClick;
}

void UIGalaxy::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

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
            } else if (CheckCollisionPointRec(mousePosition, m_collider)) {
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
            m_lastMousePosition = { 0.0f, 0.0f };
            m_isScrollingByMouse = false;
        }
    }

    if (m_isEnabled) {
        for (auto const& e : m_uiGalaxyElements) {

            if (IsUIGalaxyElementInCollider(e) != e->IsEnabled()) {
                e->SetEnabled(IsUIGalaxyElementInCollider(e));
                if (!IsUIGalaxyElementInCollider(e) && e->IsFocused()) {
                    SelectNextFocusElement();
                }
            }

            if (IsUIGalaxyElementInCollider(e)) {
                e->CheckAndUpdate(mousePosition, appContext);
            }
        }
        for (auto const& f : m_uiFleets) {
            f->CheckAndUpdate(mousePosition, appContext);
        }

        if (IsFocused() && !IsNestedFocus()) {
            if (IsConfirmInputPressed()) {
                m_isNestedFocus = true;
                AddFocusLayer();
                for (auto const& e : m_uiGalaxyElements) {
                    AddFocusElement(e.get());
                }
            }
        }

        if (IsNestedFocus()) {
            if (IsBackInputPressed() or !CheckCollisionPointRec(mousePosition, m_collider)) {
                DeleteFocusLayer();
                m_isNestedFocus = false;
            }
        }
    }
}
void UIGalaxy::Render(AppContext_ty_c appContext) {

    for (auto const& e : m_uiGalaxyElements) {
        if (IsUIGalaxyElementInCollider(e)) {
            e->RenderRing(appContext);
        }
    }
    for (auto const& f : m_uiFleets) {
        if (f->IsRingOverlappingWithRectangle(m_collider)) {
            f->RenderRing(appContext);
        }
    }
    BeginScissorMode(
            static_cast<int>(m_collider.x),
            static_cast<int>(m_collider.y),
            static_cast<int>(m_collider.width),
            static_cast<int>(m_collider.height)
    );

    for (auto const& f : m_uiFleets) {
        f->Render(appContext);
    }

    EndScissorMode();

    for (auto const& p : m_uiPlanets) {
        if (IsUIGalaxyElementInCollider(p)) {
            p->Render(appContext);
        }
    }
    for (auto const& t : m_uiTargetPoints) {
        if (IsUIGalaxyElementInCollider(t)) {
            t->Render(appContext);
        }
    }

    if (m_updateLineDrag) {
        m_lineDrag->Render(appContext);
    }

    /*
	DrawRectangleLinesEx(
		m_absoluteSize,
		1.0f,
		WHITE
	);
	DrawRectangleLinesEx(
		m_collider,
		1.0f,
		PURPLE
	);
	*/
}
void UIGalaxy::Resize(AppContext_ty_c appContext) {

    UIElement::Resize(appContext);
    m_lineDrag->Resize(appContext);

    Resolution_ty_c resolution{ appContext.GetResolution() };
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

void UIGalaxy::FilterByCurrentPlayer(PlayerData player) {
    for (auto const& f : m_uiFleets) {
        f->SetDisplayedAsPoint(f->GetPlayer().ID != player.ID);
    }
}

void UIGalaxy::SetEnabled(bool isEnabled) {
    m_isEnabled = isEnabled;
}
bool UIGalaxy::IsEnabled() const {
    return m_isEnabled;
}
Rectangle UIGalaxy::GetCollider() const {
    return UIElement::GetCollider();
}

Galaxy_ty_raw UIGalaxy::GetGalaxy() const {
    return m_currentGalaxy;
}

void UIGalaxy::OnEvent(Event const& event) {

    if (auto const* galaxyEvent = dynamic_cast<SendGalaxyPointerEvent const*>(&event)) {
        Initialize(galaxyEvent);
        return;
    }
}
