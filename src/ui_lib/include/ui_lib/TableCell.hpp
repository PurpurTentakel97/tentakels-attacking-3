//
// Purpur Tentakel
// 23.04.2023
//

#include "AbstractTableCell.h"
#include "AppContext.h"
#include "event/UIEvents.hpp"
#include "helper/HColors.h"
#include "helper/HInput.h"
#include "helper/HPrint.h"
#pragma once

template<typename T>
class TableCell final : public AbstractTableCell {
private:
    T m_value;                 ///< contains the value
    std::string m_stringValue; ///< contains the value as string
    std::function<void(TableCell*, T, T)> m_updated{ [](TableCell*, T, T) {
    } }; ///< conains a lambda that provides that the value has chanced

    /**
	 * Sets the value as string.
	 */
    void SetStringValue() {
        m_stringValue = std::to_string(m_value);
    }

    /**
	 * updates the cell value.
	 */
    void UpdateValue(T newValue) {
        T const oldValue{ m_value };
        m_value = newValue;
        SetStringValue();
        m_updated(this, oldValue, m_value);
    }

public:
    /**
	 * ctor
	 */
    TableCell(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            unsigned int focusID,
            T value,
            std::function<void(TableCell*, T, T)> updated
    )
        : AbstractTableCell{ pos, size, alignment, focusID },
          m_value{ value },
          m_updated{ updated } {
        SetStringValue();
        CalculateTextSize();
    }

    /**
	 * use this if the cell is clicked.
	 * need to be implemented by every cell.
	 */
    void Clicked(Vector2 const&, AppContext_ty_c appContext) override {

        if (not IsEditable()) {
            return;
        }

        ShowCellPopUpEvent<T> event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                     m_value,
                                     [this](T value) { this->UpdateValue(value); } };
        appContext.eventManager.InvokeEvent(event);
    }
    /**
	 * calls the CheckAndUpdate member function of UIElement.
	 * contains the logic of the cell.
	 */
    void CheckAndUpdate(Vector2 const&, AppContext_ty_c appContext) override {
        if (not IsEditable()) {
            return;
        }

        bool shouldEdit{ false };

        if (IsFocused()) {
            if (IsConfirmInputPressed()) {
                shouldEdit = true;
            }
        }

        if (shouldEdit) {
            ShowCellPopUpEvent<T> event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                         m_value,
                                         [this](T value) { this->UpdateValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        }
    }
    /**
	 * renders the cell
	 */
    void Render(AppContext_ty_c appContext) override {
        AbstractTableCell::Render(appContext);

        DrawTextEx(
                *appContext.assetManager.GetFont(),
                m_stringValue.c_str(),
                m_textPosition,
                m_textSize,
                0.0f,
                m_textColor
        );
    }

    /**
	 * calculates a new text size from the collider.
	 */
    void CalculateTextSize() override {
        m_textSize = m_collider.height / 1.5f;
        float const margin{ (m_collider.height - m_textSize) / 2 };
        m_textPosition = { m_collider.x + m_collider.width * 0.05f, m_collider.y + margin };
    }
    /**
	 * returns the current value.
	 */
    [[nodiscard]] std::any GetValue() const override {
        return m_value;
    }
    /**
	 * returns the current value as string.
	 */
    [[nodiscard]] std::string GetValueAsString() const override {
        return m_stringValue;
    }
};

/**
 * overload because std::string has no overload for string.
 */
template<>
inline void TableCell<std::string>::SetStringValue() {
    m_stringValue = m_value;
}
/**
 * overload because color has no string representation.
 */
template<>
inline void TableCell<Color>::SetStringValue() {
    m_stringValue = Colors::AsString(m_value);
}

/**
 * overload because color is rendered different.
 */
template<>
inline void TableCell<Color>::Render(AppContext_ty_c appContext) {
    AbstractTableCell::Render(appContext);

    auto const offset{ m_collider.height / 10.0f };
    DrawRectangle(
            static_cast<int>(m_collider.x + offset),
            static_cast<int>(m_collider.y + offset),
            static_cast<int>(m_collider.width - 2.0f * offset),
            static_cast<int>(m_collider.height - 2.0f * offset),
            m_value
    );
}
