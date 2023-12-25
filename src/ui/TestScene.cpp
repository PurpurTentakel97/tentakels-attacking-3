//
// Purpur Tentakel
// 01.10.2022
//

#include "helper/HPrint.h"
#include "TestScene.h"
#include "ui_lib/SceneType.h"
#include "AppContext.h"
#include "ui_lib/ExpandingButton.h"
#include "ui_lib/ClassicButton.h"
#include "ui_lib/Table.h"

void TestScene::Initialize([[maybe_unused]] AppContext_ty appContext) {
	auto mainBtn = std::make_shared<ExpandingButton>(
		1,
		GetElementPosition(0.1f,0.5f),
		GetElementSize(0.2f,0.1f),
		Alignment::MID_MID,
		ExpandingButton::RIGHT,
		0.005f,
		10.0f,
		"main button"
	);
	m_elements.push_back(mainBtn);

	auto firstBtn = std::make_shared<ClassicButton>(
		2,
		Vector2(0.0f,0.0f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		"first expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(firstBtn, true);

	auto secondBtn = std::make_shared<ClassicButton>(
		3,
		Vector2(0.0f,0.1f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		"second expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(secondBtn, false);

	auto thirdBtn = std::make_shared<ClassicButton>(
		4,
		Vector2(0.0f,0.2f),
		Vector2(0.0f,0.0f),
		Alignment::DEFAULT,
		"third expanding",
		SoundType::CLICKED_RELEASE_STD
	);
	mainBtn->Add(thirdBtn, true);
	mainBtn->Update();

	// to get Back No testing
	auto backBtn = std::make_shared<ClassicButton>(
		1000,
		GetElementPosition(0.05f, 0.95f),
		GetElementSize(0.15f, 0.1f),
		Alignment::BOTTOM_LEFT,
		"Back",
		SoundType::CLICKED_PRESS_STD
	);
	backBtn->SetOnClick([]() {
		SwitchSceneEvent const event{ SceneType::MAIN_MENU };
		AppContext::GetInstance().eventManager.InvokeEvent(event);
		});
	m_elements.push_back(backBtn);
}

TestScene::TestScene()
	: Scene{ {0.5f, 0.5f}, {1.0f, 1.0f}, Alignment::MID_MID } {

	AppContext_ty appContext{ AppContext::GetInstance() };
	Initialize(appContext);
}

void TestScene::SetActive(bool active, AppContext_ty_c appContext) {
	Scene::SetActive(active, appContext);
}

void TestScene::TestLambda(bool toggled) {
	Print(
		PrintType::DEBUG,
		"toggled -> {}",
		toggled
	);
}

void TestScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
	Scene::CheckAndUpdate(mousePosition, appContext);
}
void TestScene::Render(AppContext_ty_c appContext) {
	Scene::Render(appContext);
}
void TestScene::Resize(AppContext_ty_c appContext) {
	Scene::Resize(appContext);
}
