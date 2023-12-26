//
// Purpur Tentakel
// 08.05.2023
//

#include "Hover.h"
#include "AppContext.hpp"
#include "event/EventsUI.hpp"
#include "helper/HTextProcessing.h"

void Hover::CalculateDefault(AppContext_ty_c appContext) {
	Resolution_ty_c resolution{ appContext.GetResolution() };
	Vector2 const textOffset {
		resolution.x * 0.01f,
		resolution.y * 0.01f,
	};

	Vector2 const measure{ MeasureTextEx(
		*appContext.assetManager.GetFont(),
		m_text.c_str(),
		m_textHeight,
		0.0f
	) };

	Rectangle const newCollider{
		m_collider.x,
		m_collider.y,
		measure.x + textOffset.x,
		measure.y + textOffset.y
	};
	SetCollider(newCollider);

	m_textPosition = {
		m_collider.x + textOffset.x / 2,
		m_collider.y + textOffset.y / 2
	};
}

Hover::Hover(float height, std::string text, Color color, Vector2 hoverOffset)
	: UIElement{ { 0.0f, 0.0f }, { 0.0f, 0.0f }, Alignment::BOTTOM_LEFT },
      m_text{ text },m_color(color),m_hoverOffset{ hoverOffset }, m_textHeight{ 0.0f } {

    AppContext_ty appContext{ AppContext::GetInstance() };
	Resolution_ty_c resolution{ appContext.GetResolution() };
	m_textHeight = { height * resolution.y };

	CalculateDefault(appContext);


	m_absoluteHoverOffset = {
		hoverOffset.x * resolution.x,
		hoverOffset.y * resolution.y
	};
}

Vector2 Hover::GetRenderOffset() const {
	Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
	Vector2 renderOffset{ 0, 0 };
	if (m_collider.x + m_collider.width > resolution.x) {
		renderOffset.x = m_collider.x + m_collider.width - resolution.x;
	}
	if (m_collider.y < 0) {
		renderOffset.y = -m_collider.y;
	}

	return renderOffset;
}
void Hover::SetRenderHover(Vector2 mousePosition, AppContext_ty_c appContext) {
	Rectangle const newCollider{
		mousePosition.x + m_absoluteHoverOffset.x,
		mousePosition.y - m_absoluteHoverOffset.y - m_collider.height,
		m_collider.width,
		m_collider.height
	};
	SetCollider(newCollider);
	CalculateDefault(appContext);

	RenderHoverEvent event{ this };
	appContext.eventManager.InvokeEvent(event);
}

void Hover::SetText(std::string const& text) {
	m_text = { text };
}

void Hover::Render(AppContext_ty_c appContext) {
	auto const& renderOffset{ GetRenderOffset() };
	RenderOffset(appContext, renderOffset);
}
float Hover::RenderOffset(AppContext_ty_c, Vector2 const& offset) const {
	Rectangle const dummyCollider{
		m_collider.x - offset.x,
		m_collider.y - offset.y,
		m_collider.width,
		m_collider.height
	};
	Vector2 const dummyTextPosition{
		m_textPosition.x - offset.x,
		m_textPosition.y - offset.y
	};

	DrawRectangleRec(
		dummyCollider,
		GREY_100
	);
	DrawRectangleLinesEx(
		dummyCollider,
		2.0f,
		PURPLE
	);

	DrawTextWithOutline(m_text, dummyTextPosition, m_textHeight, m_color, true);

	return m_collider.height;
}

void Hover::Resize(AppContext_ty_c appContext) {
	UIElement::Resize(appContext);
	CalculateDefault(appContext);
}
