//
// Purpur Tentakel
// 22.12.2023
//

#pragma once
#include "Focusable.hpp"
#include "NewTableCell.hpp"
#include "UIElement.hpp"

#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>

static inline const std::function<std::string(size_t, size_t)> IndexOutOfRangeExceptionString{
	[](size_t const row, size_t const column) -> std::string {
		return "no such cell - row: " + std::to_string(row) + " | column: " + std::to_string(column);
	}
};

class NewTable final : public UIElement, public Focusable {
public:
	using cell_vec_ty = std::vector<std::vector<std::shared_ptr<NewTableCell>>>;
	using headlines_ty = std::unordered_map<size_t, NewTableCell::variant_ty>;

private:
	cell_vec_ty m_cells{ };
	size_t m_row_count, m_column_count;
	headlines_ty m_headlines{ };
	Vector2 m_scroll_offset{ 0.0f,0.0f };
	float m_preference_text_size;
	float m_scroll_speed{ 0.05f };
	bool m_isHeadline{ false };
	bool m_isNumbered{ false };
	bool m_isRenderHover{ false };
	bool m_isScrollable{ false };

	[[nodiscard]] NewTableCell& getSpecialCell(size_t row, size_t column);

	[[nodiscard]] NewTableCell const& getSpecialCell(size_t row, size_t column) const;

	[[nodiscard]] NewTableCell* getCellUnsafe(size_t row, size_t column);

	[[nodiscard]] NewTableCell const* getCellUnsafe(size_t row, size_t column) const;


	[[nodiscard]] bool validSpecialRow(size_t row) const;

	[[nodiscard]] bool validSpecialColumn(size_t column) const;

	[[nodiscard]] bool validSpecialIndex(size_t row, size_t column) const;

	[[nodiscard]] bool validRow(size_t row) const;

	[[nodiscard]] bool validColumn(size_t column) const;

	[[nodiscard]] bool validIndex(size_t row, size_t column) const;

	[[nodiscard]] NewTableCell::index_ty index(NewTableCell const& cell) const;

	[[nodiscard]] std::shared_ptr<NewTableCell> generate_cell() const;

	void updateSpecialCells();
	void update_cell_focus_ids();
	void update_cell_sizes();
	void update_cell_positions();

	void clamp_scroll_offset(Vector2& offset) const;

	void check_and_update_scroll(Vector2 const& mousePosition);

public:
	NewTable(unsigned int ID, Vector2 pos, Vector2 size, Alignment alignment, size_t row, size_t column, float text_size);

	[[nodiscard]] size_t rowCount() const;

	[[nodiscard]] size_t columnCount() const;

	// cells
	[[nodiscard]] bool hasCell(size_t row, size_t column) const;

	[[nodiscard]] NewTableCell& getCell(size_t row, size_t column);

	[[nodiscard]] NewTableCell const& getCell(size_t row, size_t column) const;

	void clearCell(size_t row, size_t column);

	template<CellValueType T>
	NewTableCell& setValue(size_t const row, size_t const column, T const value) {
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

	void setCellCallback(size_t row, size_t column, NewTableCell::callback_ty const& callback);

	void update_cells();

	// row
	[[nodiscard]] bool hasRow(size_t row) const;

	size_t insertRow(size_t row);

	size_t appendRow();

	bool removeRow(size_t row);

	bool popRow();

	// column
	[[nodiscard]] bool hasColumn(size_t column) const;

	size_t insertColumn(size_t column);

	size_t appendColumn();

	bool removeColumn(size_t column);

	bool popColumn();

	// headlines
	[[nodiscard]] bool isHeadline() const;

	void showHeadline(bool headline);

	template<CellValueType T>
	void setHeadline(size_t column, T value) {
		if (not validColumn(column)) {
			throw std::runtime_error{ IndexOutOfRangeExceptionString(size_t{ 0 },column) };
		}

		m_headlines[column] = value;

	}

	void clearHeadline(size_t column);

	template<CellValueType T>
	void setHeadlines(std::vector<T> values) {
		if (values.size() > m_column_count) {
			throw std::runtime_error{ "more headlines provided than columns existing" };
		}

		m_headlines.clear();

		for (size_t i = 0; i < values.size(); ++i) {
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
	void CheckAndUpdate(Vector2 const&, AppContext_ty_c) override;

	void Render(AppContext_ty_c appContext) override;
};
