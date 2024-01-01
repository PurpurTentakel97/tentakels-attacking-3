//
// Purpur Tentakel
// 23.04.2023
//

#pragma once

#include "TableCellAbstract.hpp"
#include <app/AppContext.hpp>
#include <event/EventsUI.hpp>
#include <helper/HInput.hpp>
#include <helper/HPrint.hpp>
#include <utils/Colors.hpp>


namespace uil {
    template<typename T>
    class TableCell final : public AbstractTableCell {
    private:
        T m_value;
        std::string m_stringValue;
        std::function<void(TableCell*, T, T)> m_updated{ [](TableCell*, T, T) {} };


        void SetStringValue() {
            m_stringValue = std::to_string(m_value);
        }

        void UpdateValue(T newValue) {
            T const oldValue{ m_value };
            m_value = newValue;
            SetStringValue();
            m_updated(this, oldValue, m_value);
        }

    public:
        TableCell(
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                utl::usize focusID,
                T value,
                std::function<void(TableCell*, T, T)> updated
        )
            : AbstractTableCell{ pos, size, alignment, focusID },
              m_value{ value },
              m_updated{ updated } {
            SetStringValue();
            CalculateTextSize();
        }


        void Clicked(Vector2 const&, app::AppContext_ty_c appContext) override {

            if (not IsEditable()) {
                return;
            }

            eve::ShowCellPopUpEvent<T> event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                              m_value,
                                              [this](T value) { this->UpdateValue(value); } };
            appContext.eventManager.InvokeEvent(event);
        }

        void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c appContext) override {
            if (not IsEditable()) {
                return;
            }

            bool shouldEdit{ false };

            if (IsFocused()) {
                if (hlp::IsConfirmInputPressed()) {
                    shouldEdit = true;
                }
            }

            if (shouldEdit) {
                eve::ShowCellPopUpEvent<T> event{ appContext.languageManager.Text("ui_table_cell_edit_entry_popup"),
                                                  m_value,
                                                  [this](T value) { this->UpdateValue(value); } };
                appContext.eventManager.InvokeEvent(event);
            }
        }

        void Render(app::AppContext_ty_c appContext) override {
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

        void CalculateTextSize() override {
            m_textSize = m_collider.height / 1.5f;
            float const margin{ (m_collider.height - m_textSize) / 2 };
            m_textPosition = { m_collider.x + m_collider.width * 0.05f, m_collider.y + margin };
        }

        [[nodiscard]] std::any GetValue() const override {
            return m_value;
        }

        [[nodiscard]] std::string GetValueAsString() const override {
            return m_stringValue;
        }
    };

    template<>
    inline void TableCell<std::string>::SetStringValue() {
        m_stringValue = m_value;
    }

    template<>
    inline void TableCell<Color>::SetStringValue() {
        m_stringValue = utl::Colors::AsString(m_value);
    }

    template<>
    inline void TableCell<Color>::Render(app::AppContext_ty_c appContext) {
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
} // namespace uil
