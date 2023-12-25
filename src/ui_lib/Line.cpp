//
// Purpur Tentakel
// 06.10.2022
//

#include "Line.h"

Line::Line(Vector2 start, Vector2 end, float thick, Color color)
	: UIElement{ start, end - start, Alignment::DEFAULT }, m_thick{ thick }, m_color{ color }, m_start{ start }, m_end{ end } { }

void Line::Render(AppContext_ty_c) {
	DrawLineEx(
		Vector2(
			m_collider.x,
			m_collider.y
		),
		Vector2(
			m_collider.x + m_collider.width,
			m_collider.y + m_collider.height
		),
		m_thick,
		m_color
	);
}

void Line::Update() {
	SetPosition(m_start);
	SetSize(m_end - m_start);
}

Vector2 Line::GetStart() const {
	return m_start;
}

void Line::SetStart(Vector2 start) {
	m_start = start;
}

Vector2 Line::GetEnd() const {
	return m_end;
}

void Line::SetEnd(Vector2 end) {
	m_end = end;
}

float Line::GetThick() const {
	return m_thick;
}

void Line::SetThick(float thick) {
	m_thick = thick;
}

Color Line::GetColor() const{
	return m_color;
}

void Line::SetColor(Color color) {
	m_color = color;
}
