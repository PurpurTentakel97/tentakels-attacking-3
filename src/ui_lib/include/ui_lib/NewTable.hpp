//
// Purpur Tentakel
// 22.12.2023
//

#pragma once

#include "Focusable.hpp"
#include "NewTableCell.hpp"
#include "UIElement.hpp"
#include <alias/AliasUtils.hpp>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>


namespace uil {
    static inline std::function<std::string(utl::usize, utl::usize)> const IndexOutOfRangeExceptionString{
        [](utl::usize const row, utl::usize const column) -> std::string {
            return "no such cell - row: " + std::to_string(row) + " | column: " + std::to_string(column);
        }
    };

    class NewTable final : public UIElement, public Focusable {
    public:
        using cell_vec_ty = std::vector<std::vector<std::shared_ptr<NewTableCell>>>;
        using headlines_ty = std::unordered_map<utl::usize, utl::input_variant_col_ty>;

    private:
        cell_vec_ty m_cells{};
        utl::usize m_row_count, m_column_count;
        headlines_ty m_headlines{};
        Vector2 m_scroll_offset = Vector2(0.0f, 0.0f);
        float m_preference_text_size;
        float m_scroll_speed{ 0.05f };
        bool m_isHeadline{ false };
        bool m_isNumbered{ false };
        bool m_isRenderHover{ false };
        bool m_isScrollable{ false };

        [[nodiscard]] NewTableCell& getSpecialCell(utl::usize row, utl::usize column);

        [[nodiscard]] NewTableCell const& getSpecialCell(utl::usize row, utl::usize column) const;

        [[nodiscard]] NewTableCell* getCellUnsafe(utl::usize row, utl::usize column);

        [[nodiscard]] NewTableCell const* getCellUnsafe(utl::usize row, utl::usize column) const;


        [[nodiscard]] static bool validSpecialRow(utl::usize row);

        [[nodiscard]] static bool validSpecialColumn(utl::usize column);

        [[nodiscard]] bool validSpecialIndex(utl::usize row, utl::usize column) const;

        [[nodiscard]] bool validRow(utl::usize row) const;

        [[nodiscard]] bool validColumn(utl::usize column) const;

        [[nodiscard]] bool validIndex(utl::usize row, utl::usize column) const;

        [[nodiscard]] NewTableCell::index_ty index(NewTableCell const& cell) const;

        [[nodiscard]] std::shared_ptr<NewTableCell> generate_cell() const;

        void updateSpecialCells();
        void update_cell_focus_ids();
        void update_cell_sizes();
        void update_cell_positions();

        void clamp_scroll_offset(Vector2& offset) const;

        void check_and_update_scroll(Vector2 const& mousePosition);

    public:
        NewTable(
                utl::usize ID,
                Vector2 pos,
                Vector2 size,
                Alignment alignment,
                utl::usize row,
                utl::usize column,
                float text_size
        );

        [[nodiscard]] utl::usize rowCount() const;

        [[nodiscard]] utl::usize columnCount() const;

        // cells
        [[nodiscard]] bool hasCell(utl::usize row, utl::usize column) const;

        [[nodiscard]] NewTableCell& getCell(utl::usize row, utl::usize column);

        [[nodiscard]] NewTableCell const& getCell(utl::usize row, utl::usize column) const;

        void clearCell(utl::usize row, utl::usize column);

        template<utl::InputValueTypeCol T>
        NewTableCell& setValue(utl::usize const row, utl::usize const column, T const value) {
            if (not validIndex(row, column)) {
                throw std::runtime_error{ IndexOutOfRangeExceptionString(row, column) };
            }
            auto cell = getCellUnsafe(row, column);
            if (not cell) {
                throw std::runtime_error{ IndexOutOfRangeExceptionString(row, column) };
            }
            cell->setValue(value);
            return *cell;
        }

        void setCellCallback(utl::usize row, utl::usize column, NewTableCell::callback_ty const& callback);

        void update_cells();

        // row
        [[nodiscard]] bool hasRow(utl::usize row) const;

        utl::usize insertRow(utl::usize row);

        utl::usize appendRow();

        bool removeRow(utl::usize row);

        bool popRow();

        // column
        [[nodiscard]] bool hasColumn(utl::usize column) const;

        utl::usize insertColumn(utl::usize column);

        utl::usize appendColumn();

        bool removeColumn(utl::usize column);

        bool popColumn();

        // headlines
        [[nodiscard]] bool isHeadline() const;

        void showHeadline(bool headline);

        template<utl::InputValueTypeCol T>
        void setHeadline(utl::usize const column, T const value) {
            if (not validColumn(column)) {
                throw std::runtime_error{ IndexOutOfRangeExceptionString(utl::usize{ 0 }, column) };
            }

            m_headlines[column] = value;
        }

        void clearHeadline(utl::usize column);

        template<utl::InputValueTypeCol T>
        void setHeadlines(std::vector<T> const values) {
            if (values.size() > m_column_count) {
                throw std::runtime_error{ "more headlines provided than columns existing" };
            }

            m_headlines.clear();

            for (utl::usize i = 0; i < values.size(); ++i) {
                m_headlines[i + 1] = values[i];
            }
        }

        void clearHeadlines();

        // numbered
        [[nodiscard]] bool isNumbered() const;

        void showNumbers(bool numbers);

        // hovered
        [[nodiscard]] bool is_render_hovered() const;

        void set_render_hovered(bool hovering);

        // scrollable
        [[nodiscard]] bool is_scrollable() const;

        void set_scrollable(bool scrollable);

        // Focusable
        [[nodiscard]] bool IsEnabled() const override;

        [[nodiscard]] Rectangle GetCollider() const override;

        // UIElement
        void CheckAndUpdate(Vector2 const&, app::AppContext_ty_c) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
