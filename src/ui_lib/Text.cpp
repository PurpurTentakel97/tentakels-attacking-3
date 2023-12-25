//
// Purpur Tentakel
// 14.09.2022
//

#include "Text.h"
#include "helper/HTextProcessing.h"
#include "AppContext.h"
#include "helper/HPrint.h"
#include <cassert>

void Text::CreateToRender() {
	std::vector<std::string> const spitedText{ BreakLines(m_text) };
	std::vector<float> const horizontalOffset{ GetHorizontalAlignedOffset(spitedText, m_collider, m_textSize, m_textAlignment) };
	std::vector<float> const verticalOffset{ GetVerticalAlignedOffset(spitedText, m_textSize, m_collider, m_textAlignment) };

	assert(spitedText.size() == horizontalOffset.size());
	assert(spitedText.size() == verticalOffset.size());

	m_toRender.clear();
	for (int i = 0; i < spitedText.size(); ++i) {
		std::pair<std::string, Vector2> const a =
			{ spitedText[i],{horizontalOffset[i] + m_collider.x, verticalOffset[i] + m_collider.y}};
		m_toRender.emplace_back(a);
	}
}
std::vector<std::string> Text::BreakLines(std::string toBreak) const {
	if (!m_lineBreaks) {
		return { toBreak };
	}

	std::vector<std::string> const toReturn{ BreakTextInVector(toBreak, m_textSize, m_collider.width) };

	return toReturn;
}

void Text::OpenURL() const {
	if (!m_URL.empty()) {
		::OpenURL(m_URL.c_str());
	}
}

void Text::UpdateCollider() {
	UIElement::UpdateCollider();

	CreateToRender();
}

Text::Text(Vector2 pos, Vector2 size, Alignment alignment,
	Alignment textAlignment, float textHeight, std::string text)
	: UIElement{ pos, size, alignment }, m_textSize{ textHeight * AppContext::GetInstance().GetResolution().y },
	m_text{ text }, m_textHeight{ textHeight }, m_textAlignment{ textAlignment } {

	CreateToRender();
}

void Text::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (CheckCollisionPointRec(mousePosition, m_collider)) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			OpenURL();
		}
	}
}
void Text::Render([[maybe_unused]] AppContext_ty_c appContext) {
	for (auto const&[text, position] : m_toRender) {
		DrawTextWithOutline(text, position, m_textSize, m_color, m_renderBackground);
	}

	if (m_renderRectangle) {
		DrawRectangleLinesEx(
			m_collider,
			1.0f,
			PURPLE
		);
	}
}
void Text::Resize(AppContext_ty_c appContext) {
	Resolution_ty_c resolution{ appContext.GetResolution() };
	UIElement::Resize(appContext);
	m_textSize = m_textHeight * resolution.y;
	CreateToRender();
}

void Text::SetPosition(Vector2 pos) {
	UIElement::SetPosition(pos);
	CreateToRender();
}

void Text::SetSize(Vector2 size) {
	UIElement::SetSize(size);
	CreateToRender();
}

void Text::SetCollider(Rectangle collider) {
	UIElement::SetCollider(collider);
	CreateToRender();
}

float Text::GetRelativeTextHeight() {
	return m_textSize;
}

void Text::SetText(std::string text) {
	m_text = text;
	CreateToRender();
}
std::string Text::GetText() const {
	return m_text;
}

void Text::SetColor(Color color) {
	m_color = color;
}

Color Text::GetColor() const{
	return m_color;
}

void Text::SetURL(std::string URL) {
	StripString(URL);
	m_URL = URL;
}
void Text::ClearURL() {
	m_URL.clear();
}
std::string Text::GetURL() const {
	return m_URL;
}

void Text::LineBreaks(bool lineBreaks) {
	m_lineBreaks = lineBreaks;
	CreateToRender();
}
void Text::RenderRectangle(bool renderRectangle) {
	m_renderRectangle = renderRectangle;
}

void Text::SetRenderBackground(bool isRenderBackround) {
	m_renderBackground = isRenderBackround;
}
bool Text::GetRenderBackground() const {
	return m_renderBackground;
}
