//
// Purpur Tentakel
// 29.08.2022
//

#include "Slider.h"
#include "Alignment.h"
#include "AppContext.h"

void Slider::CalculateInitialButton() {
	float const sizeX{ m_isHorizontal ? m_size.x / m_absoluteDimension : m_size.x };
	float const sizeY{ m_isHorizontal ? m_size.y : m_size.y / m_absoluteDimension };

	m_btn = SliderButton(
		m_pos,
		Vector2(sizeX, sizeY),
		Alignment::TOP_LEFT,
		"",
		SoundType::CLICKED_RELEASE_STD
	);
	m_btn.SetOnPress([this]() {this->Slide();});
}

void Slider::CalculateOnSlide() const {

	auto btnCollider{ m_btn.GetCollider() };

	float const total{ m_isHorizontal
		? m_collider.width - btnCollider.width
		: m_collider.height - btnCollider.height 
	};
	float const slide{ m_isHorizontal
		? btnCollider.x - m_collider.x
		: btnCollider.y - m_collider.y 
	};

	float const calculated{ slide / total * 100 };

	m_onSlide(calculated);
}
void Slider::Slide() {
	m_isPressed = true;
	Vector2 mousePosition{ GetMousePosition() };
	if (m_isHorizontal) {
		mousePosition.x -= m_btnOffset;
	}
	else {
		mousePosition.y -= m_btnOffset;
	}
	Rectangle btnCollider{ m_btn.GetCollider() };

	float const mousePoint{ m_isHorizontal ? mousePosition.x : mousePosition.y };
	float* const btnColliderPoint{ m_isHorizontal ? &btnCollider.x : &btnCollider.y };
	float const btnColliderLength{ m_isHorizontal ? btnCollider.width : btnCollider.height };
	float const sliderColliderPoint{ m_isHorizontal ? m_collider.x : m_collider.y };
	float const sliderColliderLength{ m_isHorizontal ? m_collider.width : m_collider.height };

	float const maxValue{ sliderColliderPoint + btnColliderLength / 2 };
	float const minValue{ sliderColliderPoint + sliderColliderLength - btnColliderLength / 2 };
	if (mousePoint < maxValue) {
		*btnColliderPoint = sliderColliderPoint;
	}
	else if (mousePoint > minValue) {
		*btnColliderPoint = sliderColliderPoint + sliderColliderLength - btnColliderLength;
	}
	else {
		*btnColliderPoint = mousePoint - btnColliderLength / 2;
	}

	m_btn.SetCollider(btnCollider);

	CalculateOnSlide();
}
void Slider::SlideIfPressed() {
	if (!m_isPressed) { return; }
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		m_isPressed = false;
		return;
	}
	Slide();
}
void Slider::MoveButtonIfColliderIsPressed(Vector2 const& mousePosition) {
	bool const hover{ CheckCollisionPointRec(mousePosition, m_collider) };
	if (!hover) {
		return;
	}

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		return;
	}

	Slide();
}
void Slider::SlideIfScroll() {
	if (!m_isScroll) { return; }
	if (m_isPressed) { return; }
	if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) { return; }

	float const mouseWheel{ GetMouseWheelMove() * -1 };
	if (mouseWheel == 0.0f) { return; }
	if (m_isHorizontal != (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) { return; }

	auto btnCollider{ m_btn.GetCollider() };
	float const total{ m_isHorizontal
		? m_collider.width - btnCollider.width
		: m_collider.height - btnCollider.height 
	};

	float const slidingDifference{ total / 100 * mouseWheel * 3 };

	if (m_isHorizontal) {
		float value{ btnCollider.x + slidingDifference };
		value = value < m_collider.x ? m_collider.x : value;
		value = value > m_collider.x + total ? m_collider.x + total : value;
		btnCollider.x = value;
	}
	else {
		float value{ btnCollider.y + slidingDifference };
		value = value < m_collider.y ? m_collider.y : value;
		value = value > m_collider.y + total ? m_collider.y + total : value;
		btnCollider.y = value;
	}

	m_btn.SetCollider(btnCollider);
	CalculateOnSlide();
}
void Slider::SetOffset(Vector2 mousePosition) {

	auto const btnCollider{ m_btn.GetCollider() };

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		&& !CheckCollisionPointRec(mousePosition, btnCollider)) {
		m_btnOffset = 0.0f;
			return;
	}

	if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		|| !CheckCollisionPointRec(mousePosition, btnCollider)) { return; }

	if (m_isHorizontal) {
		m_btnOffset = mousePosition.x - (btnCollider.x + (btnCollider.width / 2));
	}
	else {
		m_btnOffset = mousePosition.y - (btnCollider.y + (btnCollider.height / 2));
	}
}

Slider::Slider(Vector2 pos, Vector2 size, Alignment alignment, 
	bool isHorizontal, float absoluteDimension)
	: UIElement{ pos, size, alignment }, m_isHorizontal{ isHorizontal },
	m_absoluteDimension{ absoluteDimension } {

	CalculateInitialButton();
}

void Slider::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {

	UIElement::CheckAndUpdate(mousePosition, appContext);

	if (!m_isEnabled) { return; }

	SetOffset(mousePosition);

	if (!m_isPressed) {
		MoveButtonIfColliderIsPressed(mousePosition);
	}
	else {
		SlideIfPressed();
	}

	SlideIfScroll();

	m_btn.CheckAndUpdate(mousePosition, appContext);
}
void Slider::Render(AppContext_ty_c appContext) {
	DrawRectangleRec(
		m_collider,
		GREY_100
	);
	m_btn.Render(appContext);
}
void Slider::Resize(AppContext_ty_c appContext) {

	UIElement::Resize(appContext);

	m_btn.Resize(appContext);
}

void Slider::SetOnSlide(std::function<void(float)> onSlide) {
	m_onSlide = onSlide;
}
void Slider::SetButtonPosition(float position) {
	auto btnCollider{ m_btn.GetCollider() };

	float const total{ m_isHorizontal
		? m_collider.width - btnCollider.width
		: m_collider.height - btnCollider.height 
	};

	float const deferens{ total / 100 * position };
	float const newPosition{ m_isHorizontal
		? m_collider.x + deferens
		: m_collider.y + deferens 
	};

	if (m_isHorizontal) {
		btnCollider.x = newPosition;
	}
	else {
		btnCollider.y = newPosition;
	}

	m_btn.SetCollider(btnCollider);
}

void Slider::SetScrolling(bool isScroll) {
	m_isScroll = isScroll;
}
bool Slider::IsScrolling() const {
	return m_isScroll;
}

void Slider::SetAbsoluteDimension(float absolutDimension) {
	m_absoluteDimension = absolutDimension;
	CalculateInitialButton();
}
float Slider::GetAbsoluteDimension() const {
	return m_absoluteDimension;
}

void Slider::SetEnabled(bool isEnabled) {
	m_isEnabled = isEnabled;
	m_btn.SetEnabled(isEnabled);
}

bool Slider::IsColliding(Vector2 point) const {
	return CheckCollisionPointRec(point, m_collider);
}
