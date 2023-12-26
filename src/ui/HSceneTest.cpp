//
// Purpur Tentakel
// 01.10.2022
//

#include "AppContext.hpp"
#include "HSceneTestScene.hpp"
#include "helper/HPrint.hpp"
#include "ui_lib/ButtonClassic.hpp"
#include "ui_lib/NewTable.hpp"
#include "ui_lib/SceneType.hpp"

void TestScene::Initialize([[maybe_unused]] AppContext_ty appContext) {
	auto table = std::make_shared<NewTable>(
		1,
		Vector2{ 0.5f, 0.5f },
		Vector2{ 0.8f, 0.8f },
		Alignment::MID_MID,
		10,
		4,
		30.0f
	);
	m_elements.push_back(table);

	std::vector<std::string> const headlines{
		"first column",
		"best column"
	};
	table->setHeadlines(headlines);
	table->setHeadline<std::string>(size_t{ 4 }, "extra column");
	table->showHeadline(true);
	table->showNumbers(true);
	table->set_render_hovered(true);
	table->setValue(6, 1, PURPLE);
	table->update_cells();

	auto constexpr x{ 0.005f };
	auto constexpr y{ 0.005f };

	auto constexpr xs{ 0.05f };
	auto constexpr ys{ 0.05f };

	auto count{ 0 };

	auto insertLineBtn = std::make_shared<ClassicButton>(
		100,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"+",
		SoundType::CLICKED_RELEASE_STD
	);
	insertLineBtn->SetOnClick([table]() {
		auto const result = table->insertRow(2);
		Print(PrintType::DEBUG, "Result new Row: {}", result);
		table->update_cells();
		});
	m_elements.push_back(insertLineBtn);

	++count;

	auto addLineBtn = std::make_shared<ClassicButton>(
		101,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"+",
		SoundType::CLICKED_RELEASE_STD
	);
	addLineBtn->SetOnClick([table]() {
		auto const result = table->appendRow();
		Print(PrintType::DEBUG, "Result new Row: {}", result);
		table->update_cells();
		});
	m_elements.push_back(addLineBtn);

	++count;

	auto removeLineBtn = std::make_shared<ClassicButton>(
		102,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"-",
		SoundType::CLICKED_RELEASE_STD
	);
	removeLineBtn->SetOnClick([table]() {
		table->removeRow(2);
		table->update_cells();
		});
	m_elements.push_back(removeLineBtn);

	++count;

	auto popLineBtn = std::make_shared<ClassicButton>(
		103,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"-",
		SoundType::CLICKED_RELEASE_STD
	);
	popLineBtn->SetOnClick([table]() {
		table->popRow();
		table->update_cells();
		});
	m_elements.push_back(popLineBtn);

	++count;

	auto button = std::make_shared<ClassicButton>(
		104,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"new",
		SoundType::CLICKED_RELEASE_STD
	);
	button->SetOnClick([table]() {
		table->setValue<std::string>(5,3,"RESIZE!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!");
		table->update_cells();
		});
	m_elements.push_back(button);

	++count;

	auto button2 = std::make_shared<ClassicButton>(
		105,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"new+",
		SoundType::CLICKED_RELEASE_STD
	);
	button2->SetOnClick([table]() {
		table->setValue<std::string>(5, 2, "RESIZE!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!\n!!!!!!!!");
		table->update_cells();
		});
	m_elements.push_back(button2);

	++count;

	auto button3 = std::make_shared<ClassicButton>(
		106,
		GetElementPosition(x, y + ys * count),
		GetElementSize(xs, ys),
		Alignment::TOP_LEFT,
		"scroll",
		SoundType::CLICKED_RELEASE_STD
	);
	button3->SetOnClick([table]() {
		auto const scroll{ table->is_scrollable() };
		table->set_scrollable(not scroll);
		table->update_cells();
		});
	m_elements.push_back(button3);

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
