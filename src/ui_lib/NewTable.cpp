//
// Purpur Tentakel
// 22.12.2023
//

#include "NewTable.hpp"
#include "Slider.hpp"
#include <cassert>
#include <helper/HFocusEvents.hpp>
#include <utils/Vec2.hpp>

namespace uil {

    bool NewTable::IsValidRow(utl::usize const row) const {
        return row > 0 and row <= m_rowCount;
    }
    bool NewTable::IsValidColumn(utl::usize const column) const {
        return column > 0 and column <= m_columnCount;
    }
    bool NewTable::IsValidIndex(utl::usize const row, utl::usize const column) const {
        return IsValidRow(row) and IsValidColumn(column);
    }

    bool NewTable::IsValidSpecialRow(utl::usize const row) const {
        return row == 0;
    }
    bool NewTable::IsValidSpecialColumn(utl::usize const column) const {
        return column == 0;
    }
    bool NewTable::IsValidSpecialIndex(utl::usize const row, utl::usize const column) const {
        return IsValidRow(row) or IsValidColumn(column);
    }

    void NewTable::UpdateCellFocusID() {
        auto const ID{ [&](utl::usize const row, utl::usize const column) {
            return row * m_columnCount + column + 1;
        } };

        for (utl::usize row = 0; row <= m_rowCount; ++row) {
            for (utl::usize column = 0; column <= m_columnCount; ++column) {
                m_cells[row][column]->SetFocusID(ID(row, column));
            }
        }
    }
    void NewTable::SetCellFocus() {
        SetNestedFocus(true);

        hlp::AddFocusLayer();
        for (auto const& row : m_cells) {
            for (auto const& cell : row) {
                hlp::AddFocusElement(cell.get());
            }
        }
    }
    void NewTable::RemoveCellFocus() {
        hlp::DeleteFocusLayer();
        SetNestedFocus(false);
    }

    void NewTable::UpdateCellPositionAndSize() {
        auto cellWidth{ 0.0f };
        auto cellHeight{ 0.0f };

        auto const rowOffset    = m_isNumbered or m_isHeadline ? 0 : 1;
        auto const columnOffset = m_isNumbered ? 0 : 1;
        auto const rowCount     = m_rowCount - rowOffset;
        auto const columnCount  = m_columnCount - columnOffset;


        if (m_isScrollable) {

            Vector2 const tableSize{ m_minCellSize.x * static_cast<float>(rowCount),
                                     m_minCellSize.y * static_cast<float>(columnCount) };

            auto cellSize = m_minCellSize;

            if (tableSize.x < m_size.x) {
                cellSize.x += (m_size.x - tableSize.x) / static_cast<float>(columnCount);
            }

            cellWidth  = cellSize.x;
            cellHeight = cellSize.y;
        } else {
            cellHeight = m_size.y / static_cast<float>(rowCount);
            cellWidth  = m_size.x / static_cast<float>(columnCount);
        }

        for (utl::usize row = rowOffset; row <= rowCount; ++row) {
            for (utl::usize column = columnOffset; column <= columnCount; ++column) {
                auto const& cell = m_cells[row][column];
                cell->SetPosition({ m_pos.x + (cellWidth * static_cast<float>(column - columnOffset)),
                                    m_pos.y + (cellHeight * static_cast<float>(row - rowOffset)) });
                cell->SetSize({ cellWidth, cellHeight });
                cell->UpdateTextSize();
            }
        }
    }
    void NewTable::ClampScrollOffset(Vector2& offset) {
        hlp::Print(hlp::PrintType::DEBUG, "Need to Implement ClampScrollOffset");
    }

    void NewTable::CheckAndUpdateClickCell(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
            return;
        }

        if (not IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return;
        }

        auto cell = m_cells[0][0];
        if (m_isHeadline or m_isNumbered) {
            if (cell->IsColliding(mousePosition)) {
                goto clicked;
            }

            for (utl::usize column = 1; column <= m_columnCount; ++column) {
                cell = m_cells[0][column];
                if (cell->IsColliding(mousePosition)) {
                    goto clicked;
                }
            }
        }

        if (m_isNumbered) {
            for (utl::usize row = 1; row <= m_rowCount; ++row) {
                cell = m_cells[row][0];
                if (cell->IsColliding(mousePosition)) {
                    goto clicked;
                }
            }
        }

        for (utl::usize row = 1; row <= m_rowCount; ++row) {
            for (utl::usize column = 1; column <= m_columnCount; ++column) {
                cell = m_cells[row][column];
                if (cell->IsColliding(mousePosition)) {
                    goto clicked;
                }
            }
        }

    clicked:
        cell->Clicked(mousePosition, appContext);
    }
    void NewTable::CheckAndUpdateScroll(Vector2 const& mousePosition) {
        if (not m_isScrollable) {
            return;
        }

        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
            return;
        }

        auto const mouseWheel{ GetMouseWheelMove() };
        if (mouseWheel == 0.0f) {
            return;
        }


        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        Vector2 offset{ 0.0f, 0.0f };
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            offset.x = mouseWheel * m_scrollSpeed * resolution.x;
        } else {
            offset.y = mouseWheel * m_scrollSpeed * resolution.y;
        }

        ClampScrollOffset(offset);
        ScrollMove(offset);
        m_absoluteScrollingOffset.x += offset.x;
        m_absoluteScrollingOffset.y += offset.y;

        auto const size = GetAbsoluteTableSize();
        m_horizontalSlider->SetButtonPosition((-m_absoluteScrollingOffset.x / (size.x - m_collider.width)) * 100);
        m_verticalSlider->SetButtonPosition((-m_absoluteScrollingOffset.y / (size.y - m_collider.height)) * 100);

        if (IsNestedFocus()) {
            eve::RenderFocusEvent const event{ false };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }

    void NewTable::ScrollFocused() {
        if (not m_isScrollable) {
            return;
        }

        if (not IsNestedFocus()) {
            return;
        }

        single_cell_ty cell{ nullptr };
        for (utl::usize row = 0; row <= m_rowCount; ++row) {
            for (utl::usize column = 0; column <= m_columnCount; ++column) {
                auto const currentCell{ m_cells[row][column] };
                if (currentCell->IsFocused()) {
                    cell = currentCell;
                    goto out;
                }
            }
        }

    out:
        if (not cell) {
            return;
        }

        auto const col = cell->GetCollider();
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
        m_absoluteScrollingOffset.y += offset.x;
    }
    void NewTable::ScrollPercent(float const percent,
                                 NewTable::ScrollDirection const direction,
                                 app::AppContext_ty_c appContext) {

        auto size = GetAbsoluteTableSize();
        Vector2 offset{ 0.0f, 0.0f };

        switch (direction) {
            case ScrollDirection::HORIZONTAL:
                size.x -= m_collider.width;
                size.x *= percent / 100;
                offset.x = -(size.x + m_absoluteScrollingOffset.x);
                break;
            case ScrollDirection::VERTICAL:
                size.y -= m_collider.height;
                size.y *= percent / 100;
                offset.y = -(size.y + m_absoluteScrollingOffset.y);
                break;
        }

        ClampScrollOffset(offset);
        ScrollMove(offset);
        m_absoluteScrollingOffset.x += offset.x;
        m_absoluteScrollingOffset.y += offset.y;

        if (IsNestedFocus()) {
            eve::RenderFocusEvent const event{ false };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        }
    }
    void NewTable::ScrollMove(Vector2 const& offset) {

        for (utl::usize row = 0; row <= m_rowCount; ++row) {
            for (utl::usize column = 0; column <= m_columnCount; ++column) {
                Vector2 individualOffset{ offset };
                if (row == 0 and (m_isHeadline or m_isNumbered)) {
                    individualOffset.y = 0.0f;
                }
                if (column == 0 and m_isNumbered) {
                    individualOffset.x = 0.0f;
                }

                auto const cell{ m_cells[row][column] };
                auto collider = cell->GetCollider();
                collider.x += individualOffset.x;
                collider.y += individualOffset.y;
                cell->SetCollider(collider);
                cell->UpdateTextSize();
            }
        }
    }

    Vector2 NewTable::GetAbsoluteTableSize() const {
        Vector2 toReturn{ 0.0f, 0.0f };
        auto const rowIndex{ m_isNumbered or m_isHeadline ? 0 : 1 };
        auto const columnIndex{ m_isNumbered ? 0 : 1 };

        for (utl::usize column = columnIndex; column <= m_columnCount; ++column) {
            toReturn.x += m_cells[0][column]->GetCollider().width;
        }

        for (utl::usize row = rowIndex; row <= m_rowCount; ++row) {
            toReturn.y += m_cells[row][0]->GetCollider().height;
        }

        return toReturn;
    }

    void NewTable::CalculateSlider() {
        auto const rowIndex{ m_isNumbered or m_isHeadline ? 0 : 1 };
        auto const columnIndex{ m_isNumbered ? 0 : 1 };

        auto width{ 0.0f };
        for (utl::usize column = columnIndex; column <= m_columnCount; ++column) {
            width += m_cells[0][column]->GetSize().x;
        }
        m_activeHorizontalSlider = width > m_size.x + (static_cast<float>(m_columnCount) * 0.001f);
        auto const widthFactor{ (m_horizontalSlider->GetSize().x / m_size.x / 2.0f) + 1.0f };
        m_horizontalSlider->SetAbsoluteDimension(width * widthFactor);

        auto height{ 0.0f };
        for (utl::usize row = rowIndex; row <= m_rowCount; ++row) {
            height += m_cells[row][0]->GetSize().y;
        }
        m_activeVerticalSlider = height > m_size.y + (static_cast<float>(m_rowCount) * 0.001f);
        auto const heightFactor{ (m_verticalSlider->GetSize().y / m_size.y / 2.0f) + 1.0f };
        m_verticalSlider->SetAbsoluteDimension(height * heightFactor);
    }
    void NewTable::CalculateHoverHighlighted(Vector2 const& mousePosition) { }
} // namespace uil

//#include "NewTable.hpp"
//#include <cassert>
//#include <utils/Vec2.hpp>
//
//
//namespace uil {
//    NewTableCell& NewTable::getSpecialCell(utl::usize const row, utl::usize const column) {
//        if (not validSpecialIndex(row, column)) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(row, column) };
//        }
//        return *m_cells[row][column];
//    }
//
//    NewTableCell const& NewTable::getSpecialCell(utl::usize const row, utl::usize const column) const {
//        if (not validSpecialIndex(row, column)) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(row, column) };
//        }
//        return *m_cells[row][column];
//    }
//
//    NewTableCell* NewTable::getCellUnsafe(utl::usize const row, utl::usize const column) {
//        if (not validIndex(row, column)) {
//            return nullptr;
//        }
//        return m_cells[row][column].get();
//    }
//
//    NewTableCell const* NewTable::getCellUnsafe(utl::usize const row, utl::usize const column) const {
//        if (not validIndex(row, column)) {
//            return nullptr;
//        }
//        return m_cells[row][column].get();
//    }
//
//    bool NewTable::validSpecialRow(utl::usize const row) {
//        return row == 0;
//    }
//
//    bool NewTable::validSpecialColumn(utl::usize const column) {
//        return column == 0;
//    }
//
//    bool NewTable::validSpecialIndex(utl::usize const row, utl::usize const column) const {
//        return row <= m_row_count and column <= m_column_count and (validSpecialRow(row) or validSpecialColumn(column));
//    }
//
//    bool NewTable::validRow(utl::usize const row) const {
//        return row > 0 and row <= m_row_count;
//    }
//
//    bool NewTable::validColumn(utl::usize const column) const {
//        return column > 0 and column <= m_column_count;
//    }
//
//    bool NewTable::validIndex(utl::usize const row, utl::usize const column) const {
//        return validRow(row) and validColumn(column);
//    }
//
//    NewTableCell::index_ty NewTable::index(NewTableCell const& cell) const {
//        for (utl::usize row = 0; row <= m_row_count; ++row) {
//            for (utl::usize column = 0; column <= m_column_count; ++column) {
//                if (cell.GetFocusID() == cell.GetFocusID()) {
//                    return { row, column };
//                }
//            }
//        }
//        throw std::runtime_error{ "cell not found" };
//    }
//
//    std::shared_ptr<NewTableCell> NewTable::generate_cell() const {
//        return std::make_shared<NewTableCell>(
//                0,
//                Vector2{ 0.0f, 0.0f },
//                Vector2{ 0.0f, 0.0f },
//                [this](NewTableCell const& cell) { return index(cell); }
//        );
//    }
//
//    void NewTable::updateSpecialCells() {
//        constexpr auto firstRow{ 0 };
//        constexpr auto firstColumn{ 0 };
//        if (not validSpecialIndex(firstRow, firstColumn)) {
//            return;
//        }
//        m_cells[firstRow][firstColumn]->clear();
//
//        for (utl::usize i = 1; i <= m_column_count; ++i) {
//            if (m_isHeadline) {
//                if (m_headlines.contains(i)) {
//                    m_cells[firstRow][i]->setValueVariant(m_headlines[i]);
//                } else {
//                    m_cells[firstRow][i]->setValue<std::string>("");
//                }
//            } else {
//                m_cells[firstRow][i]->setValue(i);
//            }
//        }
//
//        for (utl::usize i = 1; i <= m_row_count; ++i) {
//            m_cells[i][firstColumn]->setValue(i);
//        }
//    }
//
//    void NewTable::update_cell_focus_ids() {
//        auto const id{ [this](utl::usize row, utl::usize column) -> utl::usize {
//            return row * m_column_count + column + 1;
//        } };
//
//        for (utl::usize row = 0; row < m_cells.size(); ++row) {
//            for (utl::usize column = 0; column < m_cells[0].size(); ++column) {
//                m_cells[row][column]->SetFocusID(id(row, column));
//            }
//        }
//    }
//
//    void NewTable::update_cell_sizes() {
//        utl::usize const first_row{ m_isHeadline or m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//        utl::usize const first_column{ m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//        std::vector<float> row_heights{};
//        row_heights.resize(m_row_count + 1);
//        std::vector<float> column_widths{};
//        column_widths.resize(m_column_count + 1);
//
//        for (utl::usize row = first_row; row <= m_row_count; ++row) {
//            for (utl::usize column = first_column; column <= m_column_count; ++column) {
//                auto const size = m_cells[row][column]->needed_cell_size(m_preference_text_size);
//                if (size.x > column_widths[column]) {
//                    column_widths[column] = size.x;
//                }
//                if (size.y > row_heights[row]) {
//                    row_heights[row] = size.y;
//                }
//            }
//        }
//
//        if (not m_isScrollable) {
//            Vector2 difference{ m_size };
//            for (auto const& r : row_heights) {
//                difference.y -= r;
//            }
//            for (auto const& c : column_widths) {
//                difference.x -= c;
//            }
//
//            for (auto& r : row_heights) {
//                r += difference.y / static_cast<float>(row_heights.size());
//            }
//            for (auto& c : column_widths) {
//                c += difference.x / static_cast<float>(column_widths.size());
//            }
//        }
//
//        for (utl::usize row = first_row; row <= m_row_count; ++row) {
//            for (utl::usize column = first_column; column <= m_column_count; ++column) {
//                Vector2 size{ column_widths[column], row_heights[row] };
//                m_cells[row][column]->SetSize(size);
//            }
//        }
//    }
//
//    void NewTable::update_cell_positions() {
//        utl::usize const first_row{ m_isHeadline or m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//        utl::usize const first_column{ m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//        Vector2 const scroll_offset = m_isScrollable ? m_scroll_offset : Vector2(0.0f, 0.0f);
//
//        for (utl::usize row = first_row; row <= m_row_count; ++row) {
//            for (utl::usize column = first_column; column <= m_column_count; ++column) {
//                if (row == first_row and column == first_column) {
//                    if (row == 0 and column == 0) {
//                        m_cells[row][column]->SetPositionUnaligned(m_pos);
//                    } else {
//                        m_cells[row][column]->SetPositionUnaligned(Vector2{ m_pos.x - scroll_offset.x,
//                                                                            m_pos.y - scroll_offset.y });
//                    }
//                } else if (row == first_row) {
//                    auto const previous{ m_cells[first_row][column - 1] };
//                    auto& current{ m_cells[first_row][column] };
//                    if (row == 0) {
//                        current->SetPositionUnaligned(Vector2{ previous->GetPosition().x + previous->GetSize().x
//                                                                       - scroll_offset.x,
//                                                               previous->GetPosition().y });
//                    } else {
//                        current->SetPositionUnaligned(Vector2{ previous->GetPosition().x + previous->GetSize().x
//                                                                       - scroll_offset.x,
//                                                               previous->GetPosition().y - scroll_offset.y });
//                    }
//                } else if (column == first_column) {
//                    auto const previous{ m_cells[row - 1][first_column] };
//                    auto& current{ m_cells[row][first_column] };
//                    if (column == 0) {
//                        current->SetPositionUnaligned(Vector2{ previous->GetPosition().x,
//                                                               previous->GetPosition().y + previous->GetSize().y
//                                                                       - scroll_offset.y });
//                    } else {
//                        current->SetPositionUnaligned(Vector2{ previous->GetPosition().x - scroll_offset.x,
//                                                               previous->GetPosition().y + previous->GetSize().y
//                                                                       - scroll_offset.y });
//                    }
//                } else {
//                    auto const top_cell{ m_cells[first_row][column] };
//                    auto const left_cell{ m_cells[row][first_column] };
//                    auto& current{ m_cells[row][column] };
//                    current->SetPositionUnaligned(Vector2{ top_cell->GetPosition().x, left_cell->GetPosition().y });
//                }
//            }
//        }
//    }
//
//    void NewTable::clamp_scroll_offset(Vector2& offset) const {
//        utl::usize const first_row{ m_isHeadline or m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//        utl::usize const first_column{ m_isNumbered ? utl::usize{ 0 } : utl::usize{ 1 } };
//
//        if (m_row_count < first_row + 1) {
//            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not enough rows in table for clamping");
//            return;
//        }
//        if (m_column_count < first_column + 1) {
//            hlp::Print(hlp::PrintType::EXPECTED_ERROR, "not enough columns in table for clamping");
//            return;
//        }
//
//        // get cells
//        auto const cellTopLeft{ m_cells[first_row][first_column]->GetCollider() };
//        auto const cellSecondTopLeft{ m_cells[first_row + 1][first_column + 1]->GetCollider() };
//        auto const cellBottomLeft{ m_cells[m_row_count][m_column_count]->GetCollider() };
//
//        // clamp right x
//        float cell{ cellBottomLeft.x + cellBottomLeft.width + offset.x };
//        float table{ m_collider.x + m_collider.width };
//        if (cell < table) {
//            offset.x += table - cell;
//        }
//
//        // clamp left x
//        cell = cellSecondTopLeft.x + offset.x;
//        table = m_collider.x + cellTopLeft.width;
//        if (cell > table) {
//            offset.x -= cell - table;
//        }
//
//        // clamp bottom y
//        cell = cellBottomLeft.y + cellBottomLeft.height + offset.y;
//        // if (m_activeHorizontalSlider) { cell += cellBottomLeft.height; }
//        table = m_collider.y + m_collider.height;
//        if (cell < table) {
//            offset.y += table - cell;
//        }
//
//        // clamp top y
//        cell = cellSecondTopLeft.y + offset.y;
//        table = m_collider.y + cellTopLeft.height;
//        if (cell > table) {
//            offset.y -= cell - table;
//        }
//    }
//
//    void NewTable::check_and_update_scroll(Vector2 const& mousePosition) {
//        if (not m_isScrollable) {
//            return;
//        }
//        if (not CheckCollisionPointRec(mousePosition, m_collider)) {
//            return;
//        }
//
//        float const mouse_wheel{ GetMouseWheelMove() };
//        if (mouse_wheel == 0.0f) {
//            return;
//        }
//
//        Vector2 offset{ 0.0f, 0.0f };
//        if (IsKeyDown(KEY_LEFT_SHIFT)) {
//            offset.x = mouse_wheel * m_scroll_speed;
//        } else {
//            offset.y = mouse_wheel * m_scroll_speed;
//        }
//
//        // clamp_scroll_offset(offset);
//        m_scroll_offset.x -= offset.x;
//        m_scroll_offset.y -= offset.y;
//        update_cell_positions();
//        hlp::Print(
//                hlp::PrintType::DEBUG,
//                "current offset: x: {}, y: {} | new offset: x: {}, y:{}",
//                m_scroll_offset.x,
//                m_scroll_offset.y,
//                offset.x,
//                offset.y
//        );
//    }
//
//    NewTable::NewTable(
//            utl::usize const ID,
//            Vector2 const pos,
//            Vector2 const size,
//            Alignment const alignment,
//            utl::usize const row_count,
//            utl::usize const column_count,
//            float const text_size
//    )
//        : UIElement{ pos, size, alignment },
//          Focusable{ ID },
//          m_row_count{ row_count },
//          m_column_count{ column_count },
//          m_preference_text_size{ text_size } {
//        assert(m_row_count > 0);
//        assert(m_column_count > 0);
//
//
//        for (utl::usize row = 0; row <= m_row_count; ++row) {
//            std::vector<std::shared_ptr<NewTableCell>> cells{};
//            for (utl::usize column = 0; column <= m_column_count; ++column) {
//                cells.push_back(generate_cell());
//            }
//            m_cells.push_back(cells);
//        }
//
//        update_cells();
//    }
//
//    utl::usize NewTable::rowCount() const {
//        return m_row_count;
//    }
//
//    utl::usize NewTable::columnCount() const {
//        return m_column_count;
//    }
//
//    bool NewTable::hasCell(utl::usize const row, utl::usize const column) const {
//        return validIndex(row, column);
//    }
//
//    NewTableCell& NewTable::getCell(utl::usize const row, utl::usize const column) {
//        auto* cell{ getCellUnsafe(row, column) };
//        if (not cell) {
//            throw std::runtime_error(IndexOutOfRangeExceptionString(row, column));
//        }
//        return *cell;
//    }
//
//    NewTableCell const& NewTable::getCell(utl::usize const row, utl::usize const column) const {
//        auto* cell{ getCellUnsafe(row, column) };
//        if (not cell) {
//            throw std::runtime_error(IndexOutOfRangeExceptionString(row, column));
//        }
//        return *cell;
//    }
//
//    void NewTable::clearCell(utl::usize row, utl::usize column) {
//        auto* cell{ getCellUnsafe(row, column) };
//        if (not cell) {
//            throw std::runtime_error(IndexOutOfRangeExceptionString(row, column));
//        }
//        cell->clear();
//    }
//
//    void NewTable::setCellCallback(
//            utl::usize const row,
//            utl::usize const column,
//            NewTableCell::callback_ty const& callback
//    ) {
//        auto* cell{ getCellUnsafe(row, column) };
//        if (not cell) {
//            throw std::runtime_error(IndexOutOfRangeExceptionString(row, column));
//        }
//        cell->setCallback(callback);
//    }
//
//    void NewTable::update_cells() {
//        updateSpecialCells();
//        update_cell_focus_ids();
//        update_cell_sizes();
//        update_cell_positions();
//    }
//
//    bool NewTable::hasRow(utl::usize const row) const {
//        return validRow(row);
//    }
//
//    utl::usize NewTable::insertRow(utl::usize const row) {
//        if (not validRow(row) and row != 0) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(row, utl::usize{ 0 }) };
//        }
//        std::vector<std::shared_ptr<NewTableCell>> new_row{};
//        for (utl::usize column = 0; column <= m_column_count; ++column) {
//            new_row.push_back(generate_cell());
//        }
//
//        m_cells.insert(m_cells.begin() + static_cast<int>(row) + 1, new_row);
//        ++m_row_count;
//
//        return row;
//    }
//
//    utl::usize NewTable::appendRow() {
//        return insertRow(m_row_count);
//    }
//
//    bool NewTable::removeRow(utl::usize const row) {
//        if (m_row_count == 0) {
//            return false;
//        }
//        if (not validRow(row)) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(row, utl::usize{ 0 }) };
//        }
//
//        m_cells.erase(m_cells.begin() + static_cast<int>(row));
//        --m_row_count;
//
//        return true;
//    }
//
//    bool NewTable::popRow() {
//        return removeRow(m_row_count);
//    }
//
//    bool NewTable::hasColumn(utl::usize const column) const {
//        return validColumn(column);
//    }
//
//    utl::usize NewTable::insertColumn(utl::usize const column) {
//        if (not validColumn(column) and column != 0) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(utl::usize{ 0 }, column) };
//        }
//        for (auto& row : m_cells) {
//            row.insert(row.begin() + static_cast<int>(column) + 1, generate_cell());
//        }
//        ++m_column_count;
//
//        return column;
//    }
//
//    utl::usize NewTable::appendColumn() {
//        return insertColumn(m_column_count);
//    }
//
//    bool NewTable::removeColumn(utl::usize const column) {
//        if (m_column_count == 0) {
//            return false;
//        }
//        if (not validColumn(column)) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(utl::usize{ 0 }, column) };
//        }
//
//        for (auto& row : m_cells) {
//            row.erase(row.begin() + static_cast<int>(column));
//        }
//        --m_column_count;
//
//        return true;
//    }
//
//    bool NewTable::popColumn() {
//        return removeColumn(m_column_count);
//    }
//
//    bool NewTable::isHeadline() const {
//        return m_isHeadline;
//    }
//
//    void NewTable::showHeadline(bool const headline) {
//        m_isHeadline = headline;
//    }
//
//    void NewTable::clearHeadline(utl::usize const column) {
//        if (not validColumn(column)) {
//            throw std::runtime_error{ IndexOutOfRangeExceptionString(utl::usize{ 0 }, column) };
//        }
//        m_headlines.erase(column);
//    }
//
//    void NewTable::clearHeadlines() {
//        m_headlines.clear();
//    }
//
//    bool NewTable::isNumbered() const {
//        return m_isNumbered;
//    }
//
//    void NewTable::showNumbers(bool const numbers) {
//        m_isNumbered = numbers;
//    }
//
//    bool NewTable::is_render_hovered() const {
//        return m_isRenderHover;
//    }
//
//    void NewTable::set_render_hovered(bool const hovering) {
//        m_isRenderHover = hovering;
//    }
//
//    bool NewTable::is_scrollable() const {
//        return m_isScrollable;
//    }
//
//    void NewTable::set_scrollable(bool const scrollable) {
//        m_isScrollable = scrollable;
//    }
//
//    bool NewTable::IsEnabled() const {
//        return true;
//    }
//
//    Rectangle NewTable::GetCollider() const {
//        return m_collider;
//    }
//
//    void NewTable::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
//        UIElement::CheckAndUpdate(mousePosition, appContext);
//
//        if (m_isRenderHover and CheckCollisionPointRec(mousePosition, m_collider)) {
//            utl::Vec2<utl::usize> index{ 0, 0 };
//
//            for (utl::usize row = 0; row <= m_row_count; ++row) {
//                for (utl::usize column = 0; column <= m_column_count; ++column) {
//                    if (m_cells[row][column]->is_hovered(mousePosition)) {
//                        index = { column, row };
//                    }
//                }
//            }
//
//            for (utl::usize row = 0; row <= m_row_count; ++row) {
//                m_cells[row][index.x]->set_hovered(true);
//            }
//            for (utl::usize column = 0; column <= m_column_count; ++column) {
//                m_cells[index.y][column]->set_hovered(true);
//            }
//        }
//
//        check_and_update_scroll(mousePosition);
//    }
//
//    void NewTable::Render(app::AppContext_ty_c appContext) {
//        BeginScissorMode(
//                static_cast<int>(m_collider.x),
//                static_cast<int>(m_collider.y),
//                static_cast<int>(m_collider.width),
//                static_cast<int>(m_collider.height)
//        );
//
//        for (utl::usize row = 1; row <= m_row_count; ++row) {
//            for (utl::usize column = 1; column <= m_column_count; ++column) {
//                m_cells[row][column]->Render(appContext);
//            }
//        }
//        auto const first_row{ 0 };
//        auto const first_column{ 0 };
//
//        if (not m_isHeadline and not m_isNumbered) {
//            goto cleanup;
//        }
//
//        for (utl::usize column = 1; column <= m_column_count; ++column) {
//            m_cells[first_row][column]->Render(appContext);
//        }
//
//        if (not m_isNumbered) {
//            goto cleanup;
//        }
//
//        for (utl::usize row = 1; row <= m_row_count; ++row) {
//            m_cells[row][first_column]->Render(appContext);
//        }
//
//        m_cells[first_row][first_column]->Render(appContext);
//
//    cleanup:
//        EndScissorMode();
//
//        DrawRectangleLinesEx(m_collider, 1.0f, WHITE);
//    }
//} // namespace uil
