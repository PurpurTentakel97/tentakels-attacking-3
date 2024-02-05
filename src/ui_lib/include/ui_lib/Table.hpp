//
// Purpur Tentakel
// 03.04.2023
//

#pragma once

#include "Focusable.hpp"
#include "TableCell.hpp"
#include "UIElement.hpp"
#include "utils/Vec2.hpp"
#include <alias/AliasUiLib.hpp>
#include <alias/AliasUtils.hpp>
#include <helper/HFocusEvents.hpp>
#include <helper/HPrint.hpp>
#include <memory>
#include <stdexcept>


namespace uil {
    class Table final : public UIElement, public Focusable {
    private:
        using cells_ty = std::vector<std::vector<TableCell_ty>>;
        utl::usize m_rowCount;
        utl::usize m_columnCount;
        cells_ty m_cells;
        Vector2 m_minCellSize;
        std::array<std::vector<bool>, 2> m_editableRowsColumns;

        bool m_setScrollable{ false };
        bool m_isScrollable{ false };
        bool m_setFixedHeadline{ false };
        bool m_isFixedHeadline{ false };
        bool m_setFixedFirstColumn{ false };
        bool m_isFixedFirstColumn{ false };
        float m_scroll_speed;
        Vector2 m_absoluteScrollingOffset{ 0.0f, 0.0f };

        Slider_ty m_horizontalSlider;
        bool m_activeHorizontalSlider{ false };
        Slider_ty m_verticalSlider;
        bool m_activeVerticalSlider{ false };

        bool m_isHoveredHighlighted{ false };
        utl::vec2pos_ty m_currentHighlighted{ 0, 0 };

        TableCell::callback_ty m_updatedStringCell{ [](TableCell&) {} };
        TableCell::callback_ty m_updatedUSizeCell{ [](TableCell&) {} };
        TableCell::callback_ty m_updatedDoubleCell{ [](TableCell&) {} };
        TableCell::callback_ty m_updatedColorCell{ [](TableCell&) {} };

        [[nodiscard]] bool IsValidIndex(utl::usize row, utl::usize column) const;

        [[nodiscard]] bool IsValidRow(utl::usize row) const;

        [[nodiscard]] bool IsValidColumn(utl::usize column) const;

        void UpdateCellFocusID();

        void UpdateCellPositionAndSize();

        [[nodiscard]] Vector2 GetAbsoluteSize() const;

        void SetCellFocus();

        void RemoveCellFocus();

        void ResizeTable();

        void UpdateHeadlinePosition();

        void UpdateFirstRowPosition();

        void CheckAndUpdateClickCell(Vector2 const& mousePositon, app::AppContext_ty_c appContext);

        void CheckAndUpdateScroll(Vector2 const& mousePosition);

        void ClampScrollOffset(Vector2& offset);

        void ScrollFocused();

        void ScrollPercent(float percent, bool isHorisonzal);

        void ScrollMove(Vector2 const& offset);

        void CalculateSlider();

        void CalculateHoverHighlighted(Vector2 mousePosition);

        void SetHighlightBackground(bool reset);

        void RenderTopLeft(app::AppContext_ty_c appContext);

        void RenderHeadline(app::AppContext_ty_c appContext);

        void RenderFirstColumn(app::AppContext_ty_c appContext);

        void RenderOtherCells(app::AppContext_ty_c appContext);

        void RenderOutline() const;

        void CellUpdated(TableCell& cell);

    public:
        Table(Vector2 pos,
              Vector2 size,
              Alignment alignment,
              utl::usize focusID,
              utl::usize rowCount,
              utl::usize columnCount,
              Vector2 minCellSize,
              float scrollSpeed);

        [[nodiscard]] std::pair<utl::usize, utl::usize> Index(TableCell const* cell) const;

        template<utl::InputValueTypeCol T>
        void SetValue(utl::usize row, utl::usize column, T input) {
            if (not IsValidIndex(row, column)) {
                hlp::Print(hlp::PrintType::ERROR, "Index out of range"), throw std::out_of_range("index");
            }

            auto const cell{ m_cells.at(row).at(column) };
            if (cell->IsA<T>()) {
                cell->SetValue(input);
            } else {
                cell->SetType(input);
            }
        }

        template<utl::InputValueTypeCol T>
        [[nodiscard]] T ValueCell(utl::usize row, utl::usize column) const {
            if (not IsValidIndex(row, column)) {
                hlp::Print(hlp::PrintType::ERROR, "index out of range");
                throw std::out_of_range("index");
            }

            return m_cells.at(row).at(column)->Value<T>();
        }

        [[nodiscard]] std::string ValueCellStr(utl::usize row, utl::usize column) const {
            if (not IsValidIndex(row, column)) {
                hlp::Print(hlp::PrintType::ERROR, "index out of range");
                throw std::out_of_range("index");
            }

            return m_cells.at(row).at(column)->ValueStr();
        }

        void SetRowCount(utl::usize newRowCount);

        [[nodiscard]] utl::usize GetRowCount() const;

        template<utl::InputValueTypeCol T>
        void SetUpdateCellType(std::function<void(TableCell&)> updateCell) {
            if constexpr (std::is_same_v<T, std::string>) {
                m_updatedStringCell = updateCell;
                return;
            }
            if constexpr (std::is_same_v<T, utl::usize>) {
                m_updatedUSizeCell = updateCell;
                return;
            }
            if constexpr (std::is_same_v<T, double>) {
                m_updatedDoubleCell = updateCell;
                return;
            }
            if constexpr (std::is_same_v<T, Color>) {
                m_updatedColorCell = updateCell;
                return;
            }
        }

        void SetSingleCallback(utl::usize row, utl::usize column, std::function<void(TableCell&)> callback);

        void SetColumnCount(utl::usize newColumnCount);

        [[nodiscard]] utl::usize GetColumnCount() const;

        template<utl::InputValueTypeCol T>
        void AddSpecificRow(utl::usize row, T defaultValue) {
            if (row == m_cells.size()) { /* nothing */
            } else if (!IsValidRow(row)) {
                hlp::Print(hlp::PrintType::ERROR, "invalid row index"), throw std::out_of_range("row-index");
            }

            auto line{ std::vector<TableCell_ty>{} };

            for (utl::usize column = 0; column < m_columnCount; ++column) {

                auto cell = std::make_shared<TableCell>(
                        Vector2(0.0f, 0.0f), Vector2(0.1f, 0.1f), Alignment::TOP_LEFT, 0, [this](TableCell& c) {
                            this->CellUpdated(c);
                        });
                if (not m_editableRowsColumns.at(1).at(column)) {
                    cell->SetEditable(false);
                }
                cell->SetType(defaultValue);
                line.push_back(cell);
            }

            m_cells.insert(m_cells.begin() + static_cast<int>(row), line);
            m_editableRowsColumns.at(0).insert(m_editableRowsColumns.at(0).begin() + static_cast<int>(row), true);
            ++m_rowCount;
        }

        template<utl::InputValueTypeCol T>
        void AddLastRow(T defaultValue) {
            AddSpecificRow<T>(m_cells.size(), defaultValue);
        }

        template<utl::InputValueTypeCol T>
        void AddSpecificColumn(utl::usize column, T defaultValue) {
            if (m_cells.size() == 0) {
                hlp::Print(hlp::PrintType::ERROR, "no rows available in the table"), throw std::out_of_range("no rows");
            } else if (column == m_cells.at(0).size()) { /* nothing */
            } else if (!IsValidColumn(column)) {
                hlp::Print(hlp::PrintType::ERROR, "column-index out of range"), throw std::out_of_range("column index");
            }

            for (utl::usize i = 0; i < m_rowCount; ++i) {
                auto row  = m_cells.at(i);
                auto cell = std::make_shared<TableCell>(
                        Vector2(0.0f, 0.0f), Vector2(0.1f, 0.1f), Alignment::TOP_LEFT, 0, [this](TableCell& c) {
                            this->CellUpdated(c);
                        });
                if (not m_editableRowsColumns.at(0).at(i)) {
                    cell->SetEditable(false);
                }
                cell->SetType(defaultValue);
                row.insert(row.begin() + static_cast<int>(column), cell);
            }
            m_editableRowsColumns.at(1).insert(m_editableRowsColumns.at(1).begin() + static_cast<int>(column), true);
            ++m_columnCount;
        }

        template<utl::InputValueTypeCol T>
        void AddLastColumn(T defaultValue) {
            if (m_cells.size() == 0) {
                hlp::Print(hlp::PrintType::ERROR, "no rows in table"), throw std::out_of_range("no rows");
            }
            AddSpecificColumn<T>(m_cells.at(0).size(), defaultValue);
        }


        void RemoveSpecificRow(utl::usize row);

        void RemoveLastRow();

        void RemoveSpecificColumn(utl::usize column);

        void RemoveLastColum();

        void SetHighlightHover(bool isHoveredHighlighted);

        [[nodiscard]] bool IsHighlightedHover() const;

        void SetScrollable(bool isScrollable);

        [[nodiscard]] bool IsScrollable() const;

        void SetSingleEditable(utl::usize row, utl::usize column, bool isEditable);

        [[nodiscard]] bool IsSingleEditable(utl::usize row, utl::usize column) const;

        void SetAllEditable(bool IsEditable) noexcept;

        [[nodiscard]] bool IsAllEditable() const noexcept;

        void SetRowEditable(utl::usize row, bool isEditable);

        [[nodiscard]] bool IsRowEditable(utl::usize row) const;

        void SetColumnEditable(utl::usize column, bool isEditable);

        [[nodiscard]] bool IsColumnEditable(utl::usize column) const;

        void SetSingleCellTextColor(Color color, utl::usize row, utl::usize column);

        [[nodiscard]] Color GetSingleCellTextColor(utl::usize row, utl::usize column) const;

        void SetAllCellTextColor(Color color);

        void SetRowCellTextColor(Color color, utl::usize row);

        void SetColumnCellTextColor(Color color, utl::usize column);

        void SetFixedHeadline(bool isFixedHeadline);

        [[nodiscard]] bool IsFixedHeadline() const;

        void SetFixedFirstColumn(bool isFixedFirstColumn);

        [[nodiscard]] bool IsFixedFirstColumn() const;

        template<utl::InputValueTypeCol T>
        void SetHeadlineValues(std::vector<T> values) {
            for (utl::usize i = 0; i < m_columnCount; ++i) {
                if (i >= values.size()) {
                    break;
                }
                SetValue<T>(0, i, values.at(i));
            }
        }

        [[nodiscard]] bool IsEnabled() const noexcept override;

        [[nodiscard]] Rectangle GetCollider() const noexcept override;

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;
    };
} // namespace uil
