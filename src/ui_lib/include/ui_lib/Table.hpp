//
// Purpur Tentakel
// 03.04.2023
//

#pragma once

#include "Focusable.hpp"
#include "TableCell.hpp"
#include "UIElement.hpp"
#include "utils/Vec2.hpp"
#include <helper/HFocusEvents.hpp>
#include <helper/HPrint.hpp>
#include <memory>
#include <stdexcept>


class Slider;

class Table final : public UIElement, public Focusable {
private:
    using cells_ty = std::vector<std::vector<AbstractTableCell_ty>>;
    size_t m_rowCount;
    size_t m_columnCount;
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
    bool m_activeHorizontalSlider;
    Slider_ty m_verticalSlider;
    bool m_activeVerticalSlider;

    bool m_isHoveredHighlighted{ false };
    utl::vec2pos_ty m_currentHighlighted{ -1, -1 };

    std::function<void(AbstractTableCell const*, std::string, std::string)> m_updatedStringCell{
        [](AbstractTableCell const*, std::string, std::string) {}
    };
    std::function<void(AbstractTableCell const*, int, int)> m_updatedIntCell{ [](AbstractTableCell const*, int, int) {
    } }; ///< int
    std::function<void(AbstractTableCell const*, float, float)> m_updatedFloatCell{
        [](AbstractTableCell const*, float, float) {}
    }; ///< float
    std::function<void(AbstractTableCell const*, double, double)> m_updatedDoubleCell{
        [](AbstractTableCell const*, double, double) {}
    }; ///< double
    std::function<void(AbstractTableCell const*, Color, Color)> m_updatedColorCell{
        [](AbstractTableCell const*, Color, Color) {}
    }; ///< color

    [[nodiscard]] bool IsValidIndex(size_t row, size_t column) const;

    [[nodiscard]] bool IsValidRow(size_t row) const;

    [[nodiscard]] bool IsValidColumn(size_t column) const;

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

    template<typename T>
    void CellUpdated(AbstractTableCell const* cell, T oldValue, T newValue) {
        if constexpr (std::is_same_v<T, std::string>) {
            m_updatedStringCell(cell, oldValue, newValue);
            return;
        }
        if constexpr (std::is_same_v<T, int>) {
            m_updatedIntCell(cell, oldValue, newValue);
            return;
        }
        if constexpr (std::is_same_v<T, float>) {
            m_updatedFloatCell(cell, oldValue, newValue);
            return;
        }
        if constexpr (std::is_same_v<T, double>) {
            m_updatedDoubleCell(cell, oldValue, newValue);
            return;
        }
        if constexpr (std::is_same_v<T, Color>) {
            m_updatedColorCell(cell, oldValue, newValue);
            return;
        }
    }

public:
    Table(Vector2 pos,
          Vector2 size,
          Alignment alignment,
          unsigned int focusID,
          size_t rowCount,
          size_t columnCount,
          Vector2 minCellSize,
          float scrollSpeed);

    template<typename T>
    void SetValue(size_t row, size_t column, T input) {
        if (not IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "Index out of range"), throw std::out_of_range("index");
        }

        auto const oldCell{ m_cells.at(row).at(column) };
        if (IsNestedFocus()) {
            hlp::DeleteFocusElement(oldCell.get());
        }

        auto cell = std::make_shared<TableCell<T>>(
                oldCell->GetPosition(),
                oldCell->GetSize(),
                oldCell->GetAlignment(),
                oldCell->GetFocusID(),
                input,
                [this](AbstractTableCell const* c, T oldValue, T newValue) {
                    this->CellUpdated<T>(c, oldValue, newValue);
                }
        );
        cell->SetEditable(oldCell->IsEditable());
        m_cells.at(row).at(column) = cell;
        if (IsNestedFocus()) {
            hlp::AddFocusElement(cell.get());
        }
    }

    template<typename T>
    [[nodiscard]] T GetValue(size_t row, size_t column) const {
        if (not IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "index out of range");
            throw std::out_of_range("index");
        }

        std::any const value{ m_cells.at(row).at(column)->GetValue() };
        return std::any_cast<T>(value);
    }

    [[nodiscard]] std::string GetValueAsString(size_t row, size_t column) const {
        if (not IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "index out of range");
            throw std::out_of_range("index");
        }

        return m_cells.at(row).at(column)->GetValueAsString();
    }

    void SetRowCount(size_t newRowCount);

    [[nodiscard]] size_t GetRowCount() const;

    template<typename T>
    void SetUpdateSpecificCell(std::function<void(AbstractTableCell const*, T, T)> updateCell) {
        if constexpr (std::is_same_v<T, std::string>) {
            m_updatedStringCell = updateCell;
            return;
        }
        if constexpr (std::is_same_v<T, int>) {
            m_updatedIntCell = updateCell;
            return;
        }
        if constexpr (std::is_same_v<T, float>) {
            m_updatedFloatCell = updateCell;
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

    void SetColumnCount(size_t newColumnCount);

    [[nodiscard]] size_t GetColumnCount() const;

    template<typename T>
    void AddSpecificRow(size_t row, T defaultValue) {
        if (row == m_cells.size()) { /* nothing */
        } else if (!IsValidRow(row)) {
            hlp::Print(hlp::PrintType::ERROR, "invalid row index"), throw std::out_of_range("row-index");
        }

        auto line{ std::vector<AbstractTableCell_ty>() };

        for (size_t column = 0; column < m_columnCount; ++column) {

            auto cell = std::make_shared<TableCell<T>>(
                    Vector2(0.0f, 0.0f),
                    Vector2(0.1f, 0.1f),
                    Alignment::TOP_LEFT,
                    0,
                    defaultValue,
                    [this](AbstractTableCell const* c, T oldValue, T newValue) {
                        this->CellUpdated<T>(c, oldValue, newValue);
                    }
            );
            if (not m_editableRowsColumns.at(1).at(column)) {
                cell->SetEditable(false);
            }
            line.push_back(cell);
        }

        m_cells.insert(m_cells.begin() + static_cast<int>(row), line);
        m_editableRowsColumns.at(0).insert(m_editableRowsColumns.at(0).begin() + static_cast<int>(row), true);
        ++m_rowCount;
    }

    template<typename T>
    void AddLastRow(T defaultValue) {
        AddSpecificRow<T>(m_cells.size(), defaultValue);
    }

    template<typename T>
    void AddSpecificColumn(size_t column, T defaultValue) {
        if (m_cells.size() == 0) {
            hlp::Print(hlp::PrintType::ERROR, "no rows available in the table"), throw std::out_of_range("no rows");
        } else if (column == m_cells.at(0).size()) { /* nothing */
        } else if (!IsValidColumn(column)) {
            hlp::Print(hlp::PrintType::ERROR, "column-index out of range"), throw std::out_of_range("column index");
        }

        for (size_t i = 0; i < m_rowCount; ++i) {
            auto row = m_cells.at(i);
            auto cell = std::make_shared<TableCell<T>>(
                    Vector2(0.0f, 0.0f),
                    Vector2(0.1f, 0.1f),
                    Alignment::TOP_LEFT,
                    0,
                    defaultValue,
                    [this](AbstractTableCell const* c, T oldValue, T newValue) {
                        this->CellUpdated<T>(c, oldValue, newValue);
                    }
            );
            if (not m_editableRowsColumns.at(0).at(i)) {
                cell->SetEditable(false);
            }
            row.insert(row.begin() + static_cast<int>(column), cell);
        }
        m_editableRowsColumns.at(1).insert(m_editableRowsColumns.at(1).begin() + static_cast<int>(column), true);
        ++m_columnCount;
    }

    template<typename T>
    void AddLastColumn(T defaultValue) {
        if (m_cells.size() == 0) {
            hlp::Print(hlp::PrintType::ERROR, "no rows in table"), throw std::out_of_range("no rows");
        }
        AddSpecificColumn<T>(m_cells.at(0).size(), defaultValue);
    }


    void RemoveSpecificRow(size_t row);

    void RemoveLastRow();

    void RemoveSpecificColumn(size_t column);

    void RemoveLastColum();

    void SetHighlightHover(bool isHoveredHighlighted);

    [[nodiscard]] bool IsHighlightedHover() const;

    void SetScrollable(bool isScollable);

    [[nodiscard]] bool IsScrollable() const;

    void SetSingleEditable(size_t row, size_t column, bool isEditable);

    [[nodiscard]] bool IsSingleEditable(size_t row, size_t column) const;

    void SetAllEditable(bool IsEditable) noexcept;

    [[nodiscard]] bool IsAllEditable() const noexcept;

    void SetRowEditable(size_t row, bool isEditable);

    [[nodiscard]] bool IsRowEditable(size_t row) const;

    void SetColumnEditable(size_t column, bool isEditable);

    [[nodiscard]] bool IsColumnEditable(size_t column) const;

    void SetSingleCellTextColor(Color color, size_t row, size_t column);

    [[nodiscard]] Color GetSingleCellTextColor(size_t row, size_t column) const;

    void SetAllCellTextColor(Color color);

    void SetRowCellTextColor(Color color, size_t row);

    void SetColumnCellTextColor(Color color, size_t column);

    void SetFixedHeadline(bool isFixedHeadline);

    [[nodiscard]] bool IsFixedHeadline() const;

    void SetFixedFirstColumn(bool isFixedFirstColumn);

    [[nodiscard]] bool IsFixedFirstColumn() const;

    template<typename T>
    void SetHeadlineValues(std::vector<T> values) {
        for (size_t i = 0; i < m_columnCount; ++i) {
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
