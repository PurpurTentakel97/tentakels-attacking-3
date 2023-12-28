//
// Purpur Tentakel
// 05.10.2022
//

#include "ColorPicker.hpp"
#include "ColorPickerCell.hpp"
#include <AppContext.hpp>
#include <cmath>
#include <helper/HFocusEvents.hpp>
#include <helper/HGeneral.hpp>
#include <helper/HInput.hpp>


void ColorPicker::Initialize() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    auto const colors{ appContext.colors.GetColors() };

    double const countX_D{ std::ceil(std::sqrt(colors.size())) };
    m_countX = static_cast<size_t>(countX_D);
    m_countY = static_cast<size_t>(std::ceil(colors.size() / countX_D));

    for (size_t row = 0; row < m_countY; ++row) {
        for (size_t column = 0; column < m_countX; ++column) {

            size_t const index{ GetIndexFromRowAndColumn(row, column, m_countX) };
            // start					offset
            float const posX{ (1.0f / static_cast<float>((2 * m_countX)))
                              + (1.0f / static_cast<float>(m_countX * column)) };
            float const posY{ (1.0f / static_cast<float>((2 * m_countY)))
                              + (1.0f / static_cast<float>(m_countY * row)) };
            float const sizeX{ 0.8f / static_cast<float>(m_countX) };
            float const sizeY{ 0.7f / static_cast<float>(m_countY) };

            Color const color{ colors.size() > index ? colors.at(index) : BLANK };

            m_cells.push_back(std::make_unique<ColorPickerCell>(
                    static_cast<unsigned int>(index + 1),
                    GetElementPosition(m_pos, m_size, posX, posY),
                    GetElementSize(m_size, sizeX, sizeY),
                    Alignment::MID_MID,
                    color,
                    this
            ));
        }
    }
}

void ColorPicker::SetUsedColors(AppContext_ty_c appContext) {
    auto const& players = appContext.playerCollection.GetPlayerData();

    for (auto& c : m_cells) {
        bool sameColor{ false };
        for (auto& p : players) {
            if (c->GetColor() == p.color) {
                sameColor = true;
                break;
            }
        }

        c->SetEnabled(!sameColor);
    }
}

void ColorPicker::SetColorFromFocus() {
    if (!m_isNestedFocus) {
        return;
    }

    for (auto const& c : m_cells) {
        if (c->IsFocused()) {
            m_currentColorCell = c.get();
            return;
        }
    }
}

void ColorPicker::CheckForValidColor(AppContext_ty_c appContext) {
    if (m_currentColorCell) {
        if (m_currentColorCell->IsEnabled()) {
            return;
        }
    }

    SetColor(appContext.playerCollection.GetPossibleColor());
}

ColorPicker::ColorPicker(
        unsigned int const ID,
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        bool const isPopUp
)
    : UIElement{ pos, size, alignment },
      Focusable{ ID },
      m_isPopUp{ isPopUp } {

    Initialize();
}

ColorPicker::~ColorPicker() {
    if (!m_isNestedFocus) {
        return;
    }

    DeleteFocusLayer(m_isPopUp);
}

Color ColorPicker::GetColor() const {
    if (m_currentColorCell) {
        return m_currentColorCell->GetColor();
    }
    return BLANK;
}

bool ColorPicker::HasColorChanced() const {
    return m_currentColorCell->GetColor() != m_previousColorCell->GetColor();
}

bool ColorPicker::SetInitialColor(Color const color) {
    bool const set{ SetColor(color) };
    m_previousColorCell = m_currentColorCell;
    return set;
}

bool ColorPicker::SetColor(Color const color) {
    for (auto& c : m_cells) {
        if (c->GetColor() == color) {
            if (!c->IsEnabled()) {
                m_currentColorCell = nullptr;
                return false;
            }

            m_currentColorCell = c.get();
            if (m_isNestedFocus) {
                eve::SelectFocusElementEvent const event{ c.get() };
                AppContext::GetInstance().eventManager.InvokeEvent(event);
            }
            return true;
        }
    }

    return false;
}

void ColorPicker::SetOnEnter(std::function<void()> onEnter) {
    m_onEnter = std::move(onEnter);
}

void ColorPicker::SetCellFocuses([[maybe_unused]] AppContext_ty_c appContext) {
    if (m_isNestedFocus) {
        return;
    }

    AddFocusLayer(m_isPopUp);

    for (auto const& c : m_cells) {
        AddFocusElement(c.get(), m_isPopUp);
    }

    if (m_currentColorCell) {
        SelectFocusElement(m_currentColorCell, m_isPopUp);
    } else {
        SelectFocusElement(m_cells.at(0).get(), m_isPopUp);
    }

    m_isNestedFocus = true;
}

void ColorPicker::SetEnabled(bool const enabled, Color const color) {
    for (auto& c : m_cells) {
        if (c->GetColor() == color) {
            c->SetEnabled(enabled);
            return;
        }
    }
}

bool ColorPicker::IsEnabled() const {
    return true;
}

[[nodiscard]] bool ColorPicker::IsPopUp() const {
    return m_isPopUp;
}

void ColorPicker::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

    UIElement::CheckAndUpdate(mousePosition, appContext);

    if (IsBackInputPressed()) {
        if (!m_isNestedFocus) {
            return;
        }
        DeleteFocusLayer(m_isPopUp);
        m_isNestedFocus = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mousePosition, m_collider)) {
            SelectFocusElement(this, m_isPopUp);
        }
    }

    if (IsFocused() and IsConfirmInputPressed()) {
        if (!m_isNestedFocus) {
            SetCellFocuses(appContext);
        } else {
            m_onEnter();
        }
    }

    for (auto const& c : m_cells) {
        c->CheckAndUpdate(mousePosition, appContext);
    }

    SetUsedColors(appContext);
    SetColorFromFocus();
    CheckForValidColor(appContext);
}

void ColorPicker::Render(AppContext_ty_c appContext) {
    // update here to make sure all CheckAndUpdate() is done
    m_previousColorCell = m_currentColorCell;

    DrawRectangleRec(m_collider, GREY_100);

    DrawRectangleLinesEx(m_collider, 3.0f, PURPLE);


    for (auto const& c : m_cells) {
        c->Render(appContext);
    }

    if (m_currentColorCell) {
        DrawRectangleLinesEx(m_currentColorCell->GetCollider(), 3.0f, WHITE);
    }
}

void ColorPicker::Resize(AppContext_ty_c appContext) {

    UIElement::Resize(appContext);

    for (auto const& c : m_cells) {
        c->Resize(appContext);
    }
}

Rectangle ColorPicker::GetCollider() const {
    return UIElement::GetCollider();
}
