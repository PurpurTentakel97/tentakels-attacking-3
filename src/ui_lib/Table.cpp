//
// Purpur Tentakel
// 03.04.2023
//

#include "Table.hpp"
#include "Slider.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <helper/HInput.hpp>


namespace uil {
    bool Table::IsValidIndex(utl::usize row, utl::usize column) const {
        return IsValidRow(row) and IsValidColumn(column);
    }
    bool Table::IsValidRow(utl::usize row) const {
        return row < m_cells.size();
    }
    bool Table::IsValidColumn(utl::usize column) const {
        if (m_cells.empty()) {
            return false;
        }
        return column < m_cells.at(0).size();
    }

    void Table::UpdateCellFocusID() {
        for (utl::usize row = 0; row < m_cells.size(); ++row) {
            for (utl::usize column = 0; column < m_cells.at(row).size(); ++column) {
                m_cells.at(row).at(column)->SetFocusID(row * m_columnCount + column);
            }
        }
    }
    void Table::UpdateCellPositionAndSize() {

        float cellWidth;
        float cellHeight;

        if (m_isScrollable) {

            Vector2 const tableSize{ m_minCellSize.x * static_cast<float>(m_columnCount),
                                     m_minCellSize.y * static_cast<float>(m_rowCount) };

            auto cellSize = m_minCellSize;

            if (tableSize.x < m_size.x) {
                cellSize.x += (m_size.x - tableSize.x) / static_cast<float>(m_columnCount);
            }

            cellWidth  = cellSize.x;
            cellHeight = cellSize.y;
        } else {
            cellWidth  = m_size.x / static_cast<float>(m_columnCount);
            cellHeight = m_size.y / static_cast<float>(m_rowCount);
        }

        for (utl::usize row = 0; row < m_cells.size(); ++row) {
            for (utl::usize column = 0; column < m_cells.at(row).size(); ++column) {
                auto const& cell = m_cells.at(row).at(column);
                cell->SetPosition({ m_pos.x + cellWidth * static_cast<float>(column),
                                    m_pos.y + cellHeight * static_cast<float>(row) });
                cell->SetSize({ cellWidth, cellHeight });
                cell->CalculateTextSize();
            }
        }

        if (m_isScrollable) {
            ScrollMove(m_absoluteScrollingOffset);
        }
    }

    void Table::SetCellFocus() {
        SetNestedFocus(true);

        hlp::AddFocusLayer();
        for (auto const& line : m_cells) {
            for (auto const& cell : line) {
                hlp::AddFocusElement(cell.get());
            }
        }
    }
    void Table::RemoveCellFocus() {
        hlp::DeleteFocusLayer();
        SetNestedFocus(false);
    }

    void Table::ResizeTable() {
        bool const needResize{ m_rowCount != m_cells.size() + 1 and m_columnCount != m_cells.at(0).size() + 1
                               and m_setScrollable != m_isScrollable };
        if (not needResize) {
            return;
        }

        m_isScrollable = m_setScrollable;

        // rows
        if (m_cells.size() == m_rowCount) { /* nothing */
        } else if (m_cells.size() < m_rowCount) {
            while (m_cells.size() < m_rowCount) {
                AddLastRow<std::string>("");
            }
        } else if (m_cells.size() > m_rowCount) {
            while (m_cells.size() > m_rowCount) {
                RemoveLastRow();
            }
        }

        if (m_cells.empty()) {
            hlp::Print(hlp::PrintType::ERROR, "no rows in table"), throw std::out_of_range("no rows");
        }

        // columns
        auto const& row = m_cells.at(0);
        if (row.size() == m_columnCount) { /* nothing */
        } else if (row.size() < m_columnCount) {
            while (row.size() < m_columnCount) {
                AddLastColumn<std::string>("");
            }
        } else if (row.size() > m_columnCount) {
            while (row.size() > m_columnCount) {
                RemoveLastColum();
            }
        }

        UpdateCellFocusID();
        UpdateCellPositionAndSize();
        CalculateSlider();
    }
    void Table::UpdateHeadlinePosition() {
        if (m_setFixedHeadline == m_isFixedHeadline) {
            return;
        }
        m_isFixedHeadline = m_setFixedHeadline;

        if (m_isFixedHeadline) {
            for (auto const& cell : m_cells.at(0)) {
                auto col = cell->GetCollider();
                col.y    = m_collider.y;
                cell->SetCollider(col);
                cell->CalculateTextSize();
            }
        } else {
            if (m_rowCount < 2) {
                hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not able to move headline");
                return;
            }
            float height = m_cells.at(0).at(0)->GetCollider().height;
            float pos    = m_cells.at(1).at(0)->GetCollider().y;
            for (auto const& cell : m_cells.at(0)) {
                auto col = cell->GetCollider();
                col.y    = pos - height;
                cell->SetCollider(col);
                cell->CalculateTextSize();
            }
        }
    }
    void Table::UpdateFirstRowPosition() {
        if (m_setFixedFirstColumn == m_isFixedFirstColumn) {
            return;
        }
        m_isFixedFirstColumn = m_setFixedFirstColumn;

        if (m_isFixedFirstColumn) {
            for (utl::usize row = 0; row < m_cells.size(); ++row) {
                auto const cell{ m_cells.at(row).at(0) };
                auto col{ cell->GetCollider() };
                col.x = m_collider.x;
                cell->SetCollider(col);
                cell->CalculateTextSize();
            }
        } else {
            if (m_columnCount < 2) {
                hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not able to move first row");
                return;
            }

            float const width{ m_cells.at(0).at(0)->GetCollider().width };
            float const pos{ m_cells.at(0).at(1)->GetCollider().x };

            for (utl::usize row = 0; row < m_cells.size(); ++row) {
                auto const cell{ m_cells.at(row).at(0) };
                auto col{ cell->GetCollider() };
                col.x = pos - width;
                cell->SetCollider(col);
                cell->CalculateTextSize();
            }
        }
    }

    void Table::CheckAndUpdateClickCell(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
            return;
        }
        if (not IsMouseButtonPressed(0)) {
            return;
        }

        auto cell{ m_cells.at(0).at(0) };
        if (cell->IsColliding(mousePosition)) {
            goto clicked;
        }

        for (utl::usize row = 1; row < m_rowCount; ++row) {
            cell = m_cells.at(row).at(0);
            if (cell->IsColliding(mousePosition)) {
                goto clicked;
            }
        }

        for (utl::usize column = 1; column < m_columnCount; ++column) {
            cell = m_cells.at(0).at(column);
            if (cell->IsColliding(mousePosition)) {
                goto clicked;
            }
        }

        for (utl::usize row = 1; row < m_rowCount; ++row) {
            for (utl::usize column = 1; column < m_columnCount; ++column) {
                cell = m_cells.at(row).at(column);
                if (cell->IsColliding(mousePosition)) {
                    goto clicked;
                }
            }
        }

    clicked:
        cell->Clicked(mousePosition, appContext);
    }
    void Table::CheckAndUpdateScroll(Vector2 const& mousePosition) {
        if (not m_isScrollable) {
            return;
        }
        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
            return;
        } // check if collider is maybe to big

        float const mouseWheel{ GetMouseWheelMove() };
        if (mouseWheel == 0.0f) {
            return;
        }

        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 offset{ 0.0f, 0.0f };
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            offset.x = mouseWheel * m_scroll_speed * resolution.x;
        } else {
            offset.y = mouseWheel * m_scroll_speed * resolution.y;
        }

        ClampScrollOffset(offset);
        ScrollMove(offset);
        m_absoluteScrollingOffset.x += offset.x;
        m_absoluteScrollingOffset.y += offset.y;

        Vector2 const size = GetAbsoluteSize();
        m_horizontalSlider->SetButtonPosition((-m_absoluteScrollingOffset.x / (size.x - m_collider.width)) * 100);
        m_verticalSlider->SetButtonPosition((-m_absoluteScrollingOffset.y / (size.y - m_collider.height)) * 100);

        if (IsNestedFocus()) {
            eve::RenderFocusEvent event{ false };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    Vector2 Table::GetAbsoluteSize() const {

        Vector2 toReturn{ 0.0f, 0.0f };

        for (auto const& cell : m_cells.at(0)) {
            toReturn.x += cell->GetCollider().width;
        }
        for (utl::usize i = 0; i < m_rowCount; ++i) {
            auto const cell = m_cells.at(i).at(0);
            toReturn.y += cell->GetCollider().height;
        }

        return toReturn;
    }
    void Table::ClampScrollOffset(Vector2& offset) {
        if (m_rowCount < 2) {
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not enough rows in table for clamping");
            return;
        }
        if (m_columnCount < 2) {
            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not enough columns in table for clamping");
            return;
        }

        // get cells
        auto const cellTopLeft       = m_cells[0][0]->GetCollider();
        auto const cellSecondTopLeft = m_cells[1][1]->GetCollider();
        auto const cellBottomLeft    = m_cells[m_rowCount - 1][m_columnCount - 1]->GetCollider();

        // clamp right x
        float cell = cellBottomLeft.x + cellBottomLeft.width + offset.x;
        float table{ m_collider.x + m_collider.width };
        if (cell < table) {
            offset.x += table - cell;
        }

        // clamp left x
        cell  = cellSecondTopLeft.x + offset.x;
        table = m_collider.x + cellTopLeft.width;
        if (cell > table) {
            offset.x -= cell - table;
        }

        // clamp bottom y
        cell = cellBottomLeft.y + cellBottomLeft.height + offset.y;
        if (m_activeHorizontalSlider) {
            cell += cellBottomLeft.height;
        }
        table = m_collider.y + m_collider.height;
        if (cell < table) {
            offset.y += table - cell;
        }

        // clamp top y
        cell  = cellSecondTopLeft.y + offset.y;
        table = m_collider.y + cellTopLeft.height;
        if (cell > table) {
            offset.y -= cell - table;
        }
    }
    void Table::ScrollFocused() {
        if (not m_isScrollable) {
            return;
        }
        if (not IsNestedFocus()) {
            return;
        }

        TableCell_ty cell{ nullptr };
        for (utl::usize row = 0; row < m_cells.size(); ++row) {
            for (utl::usize column = 0; column < m_cells.at(row).size(); ++column) {
                auto const cCell = m_cells.at(row).at(column);
                if (cCell->IsFocused()) {
                    cell = cCell;
                    goto out;
                }
            }
        }
    out:
        if (not cell) {
            return;
        }

        auto col = cell->GetCollider();
        bool const cellInCollider{
            m_collider.x < col.x                                      // left
            and m_collider.x + m_collider.width > col.x + col.width   // right
            and m_collider.y < col.y                                  // top
            and m_collider.y + m_collider.height > col.y + col.height // bottom
        };
        if (cellInCollider) {
            return;
        }

        Vector2 offset{ 0.0f, 0.0f };
        if (m_collider.x > col.x) { // left
            offset.x = m_collider.x - col.x;
        } else if (m_collider.x + m_collider.width < col.x + col.width) { // right
            offset.x = (m_collider.x + m_collider.width) - (col.x + col.width);
        }

        if (m_collider.y > col.y) { // top
            offset.y = m_collider.y - col.y;
        } else if (m_collider.y + m_collider.height < col.y + col.height) { // bottom
            offset.y = (m_collider.y + m_collider.height) - (col.y + col.height);
        }

        ScrollMove(offset);
        m_absoluteScrollingOffset.x += offset.x;
        m_absoluteScrollingOffset.y += offset.y;
    }
    void Table::ScrollPercent(float percent, bool isHorizontal) {

        auto size = GetAbsoluteSize();
        Vector2 offset{ 0.0f, 0.0f };

        if (isHorizontal) {
            size.x -= m_collider.width;
            size.x *= percent / 100;
            offset.x = -(size.x + m_absoluteScrollingOffset.x);
        } else {
            size.y -= m_collider.height;
            size.y *= percent / 100;
            offset.y = -(size.y + m_absoluteScrollingOffset.y);
        }

        ClampScrollOffset(offset);
        ScrollMove(offset);
        m_absoluteScrollingOffset.x += offset.x;
        m_absoluteScrollingOffset.y += offset.y;

        if (IsNestedFocus()) {
            eve::RenderFocusEvent event{ false };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }
    void Table::ScrollMove(Vector2 const& offset) {
        for (utl::usize row = 0; row < m_cells.size(); ++row) {
            for (utl::usize column = 0; column < m_cells.at(row).size(); ++column) {
                Vector2 individualOffset{ offset };
                if (row == 0 and m_isFixedHeadline) {
                    individualOffset.y = 0.0f;
                }
                if (column == 0 and m_isFixedFirstColumn) {
                    individualOffset.x = 0.0f;
                }

                auto const cell{ m_cells.at(row).at(column) };
                auto collider = cell->GetCollider();
                collider.x += individualOffset.x;
                collider.y += individualOffset.y;
                cell->SetCollider(collider);
                cell->CalculateTextSize();
            }
        }
    }
    void Table::CalculateSlider() {

        float width{ 0.0f };
        for (auto const& cell : m_cells.at(0)) {
            width += cell->GetSize().x;
        }
        m_activeHorizontalSlider = width > m_size.x + static_cast<float>(m_columnCount) * 0.001f;
        float const widthFactor{ m_horizontalSlider->GetSize().x / m_size.x / 2 + 1 };
        m_horizontalSlider->SetAbsoluteDimension(width * widthFactor);

        float height{ 0.0f };
        for (utl::usize i = 0; i < m_rowCount; ++i) {
            auto const& cell = m_cells[i][1];
            height += cell->GetSize().y;
        }
        m_activeVerticalSlider = height > m_size.y + static_cast<float>(m_rowCount) * 0.001f;
        float const heightFactor{ (m_verticalSlider->GetSize().y / m_size.y / 2) + 1 };
        m_verticalSlider->SetAbsoluteDimension(height * heightFactor);
    }

    void Table::CalculateHoverHighlighted(Vector2 mousePosition) {
        utl::vec2pos_ty newPosition{ 0, 0 };
        if (not m_isHoveredHighlighted) {
            goto found;
        }
        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
            goto found;
        }

        if (m_cells.at(0).at(0)->IsColliding(mousePosition)) {
            newPosition = { 0, 0 };
            goto found;
        }

        for (utl::usize column = 1; column < m_columnCount; ++column) {
            auto const& cell = m_cells[0][column];
            if (cell->IsColliding(mousePosition)) {
                newPosition = { 0, static_cast<int>(column) };
                goto found;
            }
        }

        for (utl::usize row = 1; row < m_rowCount; ++row) {
            auto const& cell = m_cells[row][0];
            if (cell->IsColliding(mousePosition)) {
                newPosition = { static_cast<int>(row), 0 };
                goto found;
            }
        }

        for (utl::usize row = 1; row < m_rowCount; ++row) {
            for (utl::usize column = 1; column < m_columnCount; ++column) {
                auto const& cell = m_cells[row][column];
                if (cell->IsColliding(mousePosition)) {
                    newPosition = { static_cast<int>(row), static_cast<int>(column) };
                    goto found;
                }
            }
        }

    found:
        if (m_currentHighlighted == newPosition) {
            return;
        }

        SetHighlightBackground(true);
        m_currentHighlighted = newPosition;
        SetHighlightBackground(false);
    }
    void Table::SetHighlightBackground(bool reset) {
        Color const newColor{ reset ? BLACK : LIGHT_GREY_100 };

        for (auto const& cell : m_cells[static_cast<utl::usize>(m_currentHighlighted.x)]) {
            cell->SetBackgroundColor(newColor);
        }


        for (utl::usize i = 0; i < m_rowCount; ++i) {
            auto const& cell = m_cells[i][static_cast<utl::usize>(m_currentHighlighted.y)];
            cell->SetBackgroundColor(newColor);
        }
    }

    void Table::RenderTopLeft(app::AppContext_ty_c appContext) {
        m_cells.at(0).at(0)->Render(appContext);
    }
    void Table::RenderHeadline(app::AppContext_ty_c appContext) {

        auto const row{ m_cells.at(0) };
        for (utl::usize column = 1; column < row.size(); ++column) { // start at 1 because cell 0 is rendered in TopLeft
            row[column]->Render(appContext);
        }
    }
    void Table::RenderFirstColumn(app::AppContext_ty_c appContext) {

        for (utl::usize row = 1; row < m_cells.size(); ++row) { // start at 1 because cell 0 is rendered in TopLeft
            m_cells[row][0]->Render(appContext);
        }
    }
    void Table::RenderOtherCells(app::AppContext_ty_c appContext) {

        for (utl::usize row = 1; row < m_cells.size();
             ++row) { // start at 1 because cell 0 is rendered in TopLeft or headline
            for (utl::usize column = 1; column < m_cells.at(row).size();
                 ++column) { // start at 1 because cell 0 is renderd in TopLeft or first column
                m_cells[row][column]->Render(appContext);
            }
        }
    }
    void Table::RenderOutline() const {

        DrawRectangleLinesEx(m_collider, 2.0f, WHITE);
    }

    Table::Table(Vector2 pos,
                 Vector2 size,
                 Alignment alignment,
                 utl::usize focusID,
                 utl::usize rowCount,
                 utl::usize columnCount,
                 Vector2 minCellSize,
                 float scrollSpeed)
        : UIElement{ pos, size, alignment },
          Focusable{ focusID },
          m_rowCount{ rowCount },
          m_columnCount{ columnCount },
          m_minCellSize{ minCellSize },
          m_scroll_speed{ scrollSpeed } {


        m_minCellSize = { m_minCellSize.x * m_size.x, m_minCellSize.y * m_size.y };
        float const cellWidth{ m_size.x / static_cast<float>(m_columnCount) };
        float const cellHeight{ m_size.y / static_cast<float>(m_rowCount) };

        m_cells.clear();
        for (utl::usize row = 0; row < m_rowCount; ++row) {
            auto line{ std::vector<TableCell_ty>() };
            for (utl::usize column = 0; column < columnCount; ++column) {
                auto cell = std::make_shared<TableCell>(Vector2(m_pos.x + cellWidth * static_cast<float>(column),
                                                                m_pos.y + cellHeight * static_cast<float>(row)),
                                                        Vector2(cellWidth, cellHeight),
                                                        Alignment::TOP_LEFT,
                                                        row * columnCount + column,
                                                        [this](TableCell& c) { this->CellUpdated(c); });

                line.push_back(cell);
            }
            m_cells.push_back(line);
        }

        m_editableRowsColumns = { std::vector<bool>(m_rowCount, true), std::vector<bool>(m_columnCount, true) };

        m_verticalSlider = std::make_shared<Slider>(hlp::GetElementPosition(m_pos, m_size, 0.995f, 0.5f),
                                                    hlp::GetElementSize(m_size, 0.01f, 0.9f),
                                                    Alignment::MID_RIGHT,
                                                    false,
                                                    20.0f);
        m_verticalSlider->SetOnSlide([this](float percent) { this->ScrollPercent(percent, false); });
        m_horizontalSlider = std::make_shared<Slider>(hlp::GetElementPosition(m_pos, m_size, 0.5f, 0.99f),
                                                      hlp::GetElementSize(m_size, 0.9f, 0.02f),
                                                      Alignment::BOTTOM_MID,
                                                      true,
                                                      20.0f);
        m_horizontalSlider->SetOnSlide([this](float percent) { this->ScrollPercent(percent, true); });
        CalculateSlider();
    }

    void Table::SetRowCount(utl::usize newRowCount) {
        if (newRowCount <= 0) {
            hlp::Print(hlp::PrintType::ERROR,
                       "tried to set a row count inside of a table that is lower than or equal to 0.");
            return;
        }

        m_rowCount = newRowCount;
    }
    utl::usize Table::GetRowCount() const {
        return m_rowCount;
    }

    void Table::SetColumnCount(utl::usize newColumnCount) {
        if (newColumnCount <= 0) {
            hlp::Print(hlp::PrintType::ERROR,
                       "tried to set a column count inside of a table that is lower than or equal to 0.");
            return;
        }

        m_columnCount = newColumnCount;
    }
    utl::usize Table::GetColumnCount() const {
        return m_columnCount;
    }


    void Table::RemoveSpecificRow(utl::usize row) {
        if (!IsValidRow(row)) {
            hlp::Print(hlp::PrintType::ERROR, "row out of range"), throw std::out_of_range("row index");
        }

        m_cells.erase(m_cells.begin() + static_cast<int>(row));
        m_editableRowsColumns.at(0).erase(m_editableRowsColumns.at(0).begin() + static_cast<int>(row));
        --m_rowCount;
    }
    void Table::RemoveLastRow() {
        RemoveSpecificRow(m_cells.size() - 1);
    }
    void Table::RemoveSpecificColumn(utl::usize column) {
        if (!IsValidColumn(column)) {
            hlp::Print(hlp::PrintType::ERROR, "column index out of range"), throw std::out_of_range("column index");
        }

        for (auto& row : m_cells) {
            row.erase(row.begin() + static_cast<int>(column));
        }

        m_editableRowsColumns.at(1).erase(m_editableRowsColumns.at(1).begin() + static_cast<int>(column));
        --m_columnCount;
    }
    void Table::RemoveLastColum() {
        if (m_cells.empty()) {
            hlp::Print(hlp::PrintType::ERROR, "no rows in table"), throw std::out_of_range("no rows");
        }
        RemoveSpecificColumn(m_cells.at(0).size() - 1);
    }

    void Table::SetHighlightHover(bool isHoveredHighlighted) {
        m_isHoveredHighlighted = isHoveredHighlighted;
    }
    bool Table::IsHighlightedHover() const {
        return m_isHoveredHighlighted;
    }

    void Table::SetScrollable(bool isScrollable) {
        m_setScrollable = isScrollable;
    }
    bool Table::IsScrollable() const {
        return m_isScrollable;
    }

    void Table::SetSingleEditable(utl::usize row, utl::usize column, bool isEditable) {
        if (!IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "row or column index out auf range");
            throw std::out_of_range("invalid index");
        }

        m_cells.at(row).at(column)->SetEditable(isEditable);
    }
    bool Table::IsSingleEditable(utl::usize row, utl::usize column) const {
        if (!IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "row or column index out auf range");
            throw std::out_of_range("invalid index");
        }
        return m_cells.at(row).at(column)->IsEditable();
    }

    void Table::SetAllEditable(bool isEditable) noexcept {
        for (auto& row : m_cells) {
            for (auto& cell : row) {
                cell->SetEditable(isEditable);
            }
        }
        for (utl::usize i = 0; i < m_editableRowsColumns.size(); ++i) {
            for (utl::usize j = 0; j < m_editableRowsColumns.at(i).size(); ++j) {
                m_editableRowsColumns.at(i).at(j) = isEditable;
            }
        }
    }
    bool Table::IsAllEditable() const noexcept {
        for (auto& row : m_cells) {
            for (auto& cell : row) {
                if (!cell->IsEditable()) {
                    return false;
                }
            }
        }

        return true;
    }

    void Table::SetRowEditable(utl::usize row, bool isEditable) {
        if (!IsValidRow(row)) {
            hlp::Print(hlp::PrintType::ERROR, "row out of range"), throw std::out_of_range("row index");
        }

        for (auto& cell : m_cells.at(row)) {
            cell->SetEditable(isEditable);
        }
        m_editableRowsColumns.at(0).at(row) = isEditable;
    }
    bool Table::IsRowEditable(utl::usize row) const {
        if (!IsValidRow(row)) {
            hlp::Print(hlp::PrintType::ERROR, "row out of range"), throw std::out_of_range("row index");
        }

        return m_editableRowsColumns.at(0).at(row);
    }

    void Table::SetColumnEditable(utl::usize column, bool isEditable) {
        if (!IsValidColumn(column)) {
            hlp::Print(hlp::PrintType::ERROR, "column out of Range");
            throw std::out_of_range("column index");
        }

        for (auto& row : m_cells) {
            row.at(column)->SetEditable(isEditable);
        }
        m_editableRowsColumns.at(1).at(column) = isEditable;
    }
    bool Table::IsColumnEditable(utl::usize column) const {
        if (!IsValidColumn(column)) {
            hlp::Print(hlp::PrintType::ERROR, "column out of Range");
            throw std::out_of_range("column index");
        }

        return m_editableRowsColumns.at(1).at(column);
    }

    void Table::SetSingleCellTextColor(Color color, utl::usize row, utl::usize column) {
        if (!IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "row or column index out auf range");
            throw std::out_of_range("invalid index");
        }

        m_cells.at(row).at(column)->SetTextColor(color);
    }
    Color Table::GetSingleCellTextColor(utl::usize row, utl::usize column) const {
        if (!IsValidIndex(row, column)) {
            hlp::Print(hlp::PrintType::ERROR, "row or column index out auf range");
            throw std::out_of_range("invalid index");
        }

        return m_cells.at(row).at(column)->GetTextColor();
    }
    void Table::SetAllCellTextColor(Color color) {
        for (auto const& row : m_cells) {
            for (auto const& cell : row) {
                cell->SetTextColor(color);
            }
        }
    }
    void Table::SetRowCellTextColor(Color color, utl::usize row) {
        if (!IsValidRow(row)) {
            hlp::Print(hlp::PrintType::ERROR, "row out of range"), throw std::out_of_range("row index");
        }

        for (auto const& cell : m_cells.at(row)) {
            cell->SetTextColor(color);
        }
    }
    void Table::SetColumnCellTextColor(Color color, utl::usize column) {
        if (!IsValidColumn(column)) {
            hlp::Print(hlp::PrintType::ERROR, "column out of Range");
            throw std::out_of_range("column index");
        }

        for (auto const& row : m_cells) {
            row.at(column)->SetTextColor(color);
        }
    }

    void Table::SetFixedHeadline(bool isFixedHeadline) {
        m_setFixedHeadline = isFixedHeadline;
    }
    bool Table::IsFixedHeadline() const {
        return m_isFixedHeadline;
    }

    void Table::SetFixedFirstColumn(bool isFixedFirstColumn) {
        m_setFixedFirstColumn = isFixedFirstColumn;
    }
    bool Table::IsFixedFirstColumn() const {
        return m_isFixedFirstColumn;
    }

    bool Table::IsEnabled() const noexcept {
        return true;
    }
    Rectangle Table::GetCollider() const noexcept {
        return m_collider;
    }

    void Table::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {

        ResizeTable();
        UpdateHeadlinePosition();
        UpdateFirstRowPosition();
        CheckAndUpdateScroll(mousePosition);

        if (IsNestedFocus()) {
            if (hlp::IsBackInputPressed()) {
                RemoveCellFocus();
            }
        }

        else if (IsFocused()) {
            if (hlp::IsConfirmInputPressed()) {
                SetCellFocus();
            }
        }

        if (m_activeHorizontalSlider) {
            m_horizontalSlider->CheckAndUpdate(mousePosition, appContext);
        }
        if (m_activeVerticalSlider) {
            m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
        }

        for (auto const& row : m_cells) {
            for (auto const& cell : row) {
                cell->CheckAndUpdate(mousePosition, appContext);
            }
        }
        bool const sliderHover{ (m_activeHorizontalSlider and m_horizontalSlider->IsColliding(mousePosition))
                                or (m_activeVerticalSlider and m_verticalSlider->IsColliding(mousePosition)) };
        if (not sliderHover) {
            CheckAndUpdateClickCell(mousePosition, appContext);
        }

        if (IsKeyPressed(KEY_TAB)) {
            ScrollFocused();
        }

        CalculateHoverHighlighted(mousePosition);
    }
    void Table::Render(app::AppContext_ty_c appContext) {

        BeginScissorMode(static_cast<int>(m_collider.x),
                         static_cast<int>(m_collider.y),
                         static_cast<int>(m_collider.width),
                         static_cast<int>(m_collider.height));

        RenderOtherCells(appContext);
        RenderFirstColumn(appContext);
        RenderHeadline(appContext);
        RenderTopLeft(appContext);
        RenderOutline();

        EndScissorMode();

        if (m_activeHorizontalSlider) {
            m_horizontalSlider->Render(appContext);
        }
        if (m_activeVerticalSlider) {
            m_verticalSlider->Render(appContext);
        }
    }
    void Table::CellUpdated(TableCell& cell) {
        if (cell.IsA<std::string>()) {
            m_updatedStringCell(cell);
        } else if (cell.IsA<utl::usize>()) {
            m_updatedUSizeCell(cell);
        } else if (cell.IsA<double>()) {
            m_updatedDoubleCell(cell);
        } else if (cell.IsA<Color>()) {
            m_updatedColorCell(cell);
        } else {
            assert(false and "unreachable");
        }
    }
} // namespace uil
