//
// Purpur Tentakel
// 01.10.2022
//

#include "HSceneTestScene.hpp"
#include <alias/AliasUtils.hpp>
#include <app/AppContext.hpp>
#include <helper/HPrint.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/NewInputLine.hpp>
//#include <ui_lib/NewTable.hpp>
#include <ui_lib/SceneType.hpp>


namespace ui {
    void TestScene::Initialize(app::AppContext_ty) {
        m_line1 = std::make_shared<uil::NewInputLine>(
                1,
                GetElementPosition(0.5f, 0.1f),
                GetElementSize(0.4f, 0.08f),
                uil::Alignment::MID_MID,
                utl::usize{ 1 }
        );
        m_line1->SetOnValueChanced([](uil::NewInputLine& line) { ui::TestScene::TestLambdaValue(line); });
        m_line1->SetOnEnter([](uil::NewInputLine& line) { ui::TestScene::TestLambdaEnter(line); });
        m_line1->SetPlaceholderText("switching line");
        m_elements.push_back(m_line1);

        auto inputLine2 = std::make_shared<uil::NewInputLine>(
                2,
                GetElementPosition(0.5f, 0.2f),
                GetElementSize(0.4f, 0.08f),
                uil::Alignment::MID_MID,
                2.0
        );
        inputLine2->SetOnValueChanced([](uil::NewInputLine& line) { ui::TestScene::TestLambdaValue(line); });
        inputLine2->SetOnEnter([](uil::NewInputLine& line) { ui::TestScene::TestLambdaEnter(line); });
        inputLine2->SetPlaceholderText("double line");
        m_elements.push_back(inputLine2);

        auto inputLine3 = std::make_shared<uil::NewInputLine>(
                3,
                GetElementPosition(0.5f, 0.3f),
                GetElementSize(0.4f, 0.08f),
                uil::Alignment::MID_MID,
                "Bester Text!"
        );
        inputLine3->SetOnValueChanced([](uil::NewInputLine& line) { ui::TestScene::TestLambdaValue(line); });
        inputLine3->SetOnEnter([](uil::NewInputLine& line) { ui::TestScene::TestLambdaEnter(line); });
        inputLine3->SetPlaceholderText("string line");
        inputLine3->SetEnabled(false);
        m_elements.push_back(inputLine3);

        auto button = std::make_shared<uil::ClassicButton>(
                5,
                GetElementPosition(0.1f, 0.5f),
                GetElementSize(0.1f, 0.1f),
                uil::Alignment::MID_LEFT,
                "toggle",
                app::SoundType::CLICKED_RELEASE_STD
        );
        button->SetOnClick([this]() { this->SwitchInputLineType(); });
        m_elements.push_back(button);

        //        auto table = std::make_shared<uil::NewTable>(
        //                1,
        //                Vector2{ 0.5f, 0.5f },
        //                Vector2{ 0.8f, 0.8f },
        //                uil::Alignment::MID_MID,
        //                10,
        //                4,
        //                30.0f
        //        );
        //        m_elements.push_back(table);
        //
        //        std::vector<std::string> const headlines{ "first column", "best column" };
        //        table->setHeadlines(headlines);
        //        table->setHeadline<std::string>(utl::usize{ 4 }, "extra column");
        //        table->showHeadline(true);
        //        table->showNumbers(true);
        //        table->set_render_hovered(true);
        //        table->setValue(6, 1, PURPLE);
        //        table->update_cells();
        //
        //        auto constexpr x{ 0.005f };
        //        auto constexpr y{ 0.005f };
        //
        //        auto constexpr xs{ 0.05f };
        //        auto constexpr ys{ 0.05f };
        //
        //        auto count{ 0.0f };
        //
        //        auto insertLineBtn = std::make_shared<uil::ClassicButton>(
        //                100,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "+",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        insertLineBtn->SetOnClick([table]() {
        //            auto const result = table->insertRow(2);
        //            hlp::Print(hlp::PrintType::DEBUG, "Result new Row: {}", result);
        //            table->update_cells();
        //        });
        //        m_elements.push_back(insertLineBtn);
        //
        //        ++count;
        //
        //        auto addLineBtn = std::make_shared<uil::ClassicButton>(
        //                101,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "+",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        addLineBtn->SetOnClick([table]() {
        //            auto const result = table->appendRow();
        //            hlp::Print(hlp::PrintType::DEBUG, "Result new Row: {}", result);
        //            table->update_cells();
        //        });
        //        m_elements.push_back(addLineBtn);
        //
        //        ++count;
        //
        //        auto removeLineBtn = std::make_shared<uil::ClassicButton>(
        //                102,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "-",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        removeLineBtn->SetOnClick([table]() {
        //            table->removeRow(2);
        //            table->update_cells();
        //        });
        //        m_elements.push_back(removeLineBtn);
        //
        //        ++count;
        //
        //        auto popLineBtn = std::make_shared<uil::ClassicButton>(
        //                103,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "-",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        popLineBtn->SetOnClick([table]() {
        //            table->popRow();
        //            table->update_cells();
        //        });
        //        m_elements.push_back(popLineBtn);
        //
        //        ++count;
        //
        //        auto button = std::make_shared<uil::ClassicButton>(
        //                104,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "new",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        button->SetOnClick([table]() {
        //            table->setValue<std::string>(5, 3, "RESIZE!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!!!!!!!!!");
        //            table->update_cells();
        //        });
        //        m_elements.push_back(button);
        //
        //        ++count;
        //
        //        auto button2 = std::make_shared<uil::ClassicButton>(
        //                105,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "new+",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        button2->SetOnClick([table]() {
        //            table->setValue<std::string>(5, 2, "RESIZE!!!!!!!!!!!!!!!!!\n!!!!!!!!!!!\n!!!!!!!!");
        //            table->update_cells();
        //        });
        //        m_elements.push_back(button2);
        //
        //        ++count;
        //
        //        auto button3 = std::make_shared<uil::ClassicButton>(
        //                106,
        //                GetElementPosition(x, y + ys * count),
        //                GetElementSize(xs, ys),
        //                uil::Alignment::TOP_LEFT,
        //                "scroll",
        //                app::SoundType::CLICKED_RELEASE_STD
        //        );
        //        button3->SetOnClick([table]() {
        //            auto const scroll{ table->is_scrollable() };
        //            table->set_scrollable(not scroll);
        //            table->update_cells();
        //        });
        //        m_elements.push_back(button3);

        // to get Back No testing
        auto backBtn = std::make_shared<uil::ClassicButton>(
                1000,
                GetElementPosition(0.05f, 0.95f),
                GetElementSize(0.15f, 0.1f),
                uil::Alignment::BOTTOM_LEFT,
                "Back",
                app::SoundType::CLICKED_PRESS_STD
        );
        backBtn->SetOnClick([]() {
            eve::SwitchSceneEvent const event{ uil::SceneType::MAIN_MENU };
            app::AppContext::GetInstance().eventManager.InvokeEvent(event);
        });
        m_elements.push_back(backBtn);
    }

    TestScene::TestScene()
        : Scene{
              { 0.5f, 0.5f },
              { 1.0f, 1.0f },
              uil::Alignment::MID_MID
    } {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        Initialize(appContext);
    }

    void TestScene::SetActive(bool const active, app::AppContext_ty_c appContext) {
        Scene::SetActive(active, appContext);
    }

    void TestScene::TestLambdaValue(uil::NewInputLine& line) {
        using namespace hlp;
        if (line.IsA<std::string>()) {
            Print(PrintType::DEBUG, "value chanced | new: {}", line.Value<std::string>());
        } else if (line.IsA<utl::usize>()) {
            Print(PrintType::DEBUG, "value chanced | new: {}", line.Value<utl::usize>());
        } else if (line.IsA<double>()) {
            Print(PrintType::DEBUG, "value chanced | new: {}", line.Value<double>());
        }
    }

    void TestScene::TestLambdaEnter(uil::NewInputLine& line) {
        using namespace hlp;
        if (line.IsA<std::string>()) {
            Print(PrintType::DEBUG, "enter pressed | current: {}", line.Value<std::string>());
        } else if (line.IsA<utl::usize>()) {
            Print(PrintType::DEBUG, "enter pressed | current: {}", line.Value<utl::usize>());
        } else if (line.IsA<double>()) {
            Print(PrintType::DEBUG, "enter pressed | current: {}", line.Value<double>());
        }
    }

    void TestScene::SwitchInputLineType() {
        if (m_line1->IsA<utl::usize>()) {
            m_line1->ChangeValueType<std::string>("NewValue");
        } else {
            m_line1->ChangeValueType<utl::usize>(1);
        }
    }

    void TestScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        Scene::CheckAndUpdate(mousePosition, appContext);
    }

    void TestScene::Render(app::AppContext_ty_c appContext) {
        Scene::Render(appContext);
    }

    void TestScene::Resize(app::AppContext_ty_c appContext) {
        Scene::Resize(appContext);
    }
} // namespace ui
