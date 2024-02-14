//
// Purpur Tentakel
// 05.06.2023
//

#include "SceneUpdateEvaluation.hpp"
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <ui_lib/SceneType.hpp>
#include <utils/ResultsEvents.hpp>


namespace ui {
    void UpdateEvaluationScene::TestPrint(eve::SendUpdateEvaluation const* event) {

        /**
	 * call in OnEvent.
	 * only for debugging.
	 */

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        hlp::Print(hlp::PrintType::DEBUG, "--------------------| Evaluation |--------------------");

        hlp::Print(hlp::PrintType::DEBUG, "------------------ | Merge Results |------------------");
        for (auto const& e : event->Result().Merges()) {
            hlp::Print(hlp::PrintType::DEBUG,
                       "{}",
                       appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().ID).GetName());
            hlp::Print(hlp::PrintType::DEBUG,
                       "origin: {} -> destination: {} -> count: {}",
                       e.GetOrigin().ID,
                       e.GetDestination().ID,
                       e.GetCount());
            hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
        }

        hlp::Print(hlp::PrintType::DEBUG, "------------------ | Fight Results |------------------");
        for (auto const& e : event->Result().Fights()) {
            if (not e.IsValid()) {
                hlp::Print(hlp::PrintType::DEBUG, "invalid update Evaluation");
                continue;
            }

            hlp::Print(hlp::PrintType::DEBUG, "{} vs. {}", e.GetSpaceObjects().first.ID, e.GetSpaceObjects().second.ID);
            hlp::Print(hlp::PrintType::DEBUG,
                       "{} vs. {}",
                       appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().first.ID).GetName(),
                       appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().second.ID).GetName());

            for (auto const& r : e.GetRounds()) {
                hlp::Print(hlp::PrintType::DEBUG, "{} | {}", r.first, r.second);
            }
            hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
        }
        hlp::Print(hlp::PrintType::DEBUG, "------------------ | Event Result |-------------------");
        if (event->Result().Events().empty()) {
            hlp::Print(hlp::PrintType::DEBUG, "no events this round");
        } else {
            for (auto const& e : event->Result().Events()) {
                if (not e) {
                    hlp::Print(hlp::PrintType::EXPECTED_ERROR, "result is empty");
                } else {
                    switch (e->Type()) {
                        case utl::GameEventType::PIRATES: {
                            hlp::Print(hlp::PrintType::DEBUG, "pirate event result");
                            break;
                        }
                        case utl::GameEventType::REVOLTS: {
                            hlp::Print(hlp::PrintType::DEBUG, "revolts event result");
                            break;
                        }
                        case utl::GameEventType::RENEGADE_SHIPS: {
                            hlp::Print(hlp::PrintType::DEBUG, "renegate ships event result");
                            break;
                        }
                        case utl::GameEventType::BLACK_HOLE: {
                            hlp::Print(hlp::PrintType::DEBUG, "black hole event result");
                            break;
                        }
                        case utl::GameEventType::SUPERNOVA: {
                            hlp::Print(hlp::PrintType::DEBUG, "supernova event result");
                            break;
                        }
                        case utl::GameEventType::ENGINE_PROBLEM: {
                            hlp::Print(hlp::PrintType::DEBUG, "Engine Problem Event Result");
                            [[maybe_unused]] auto const* result =
                                    dynamic_cast<utl::ResultEventEngineProblem const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Engine Problem Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "-> fleet {} from player {} will not be able to move within the next {} years",
                                       result->FleetID(),
                                       result->PlayerID(),
                                       result->Years());
                            break;
                        }
                        case utl::GameEventType::GLOBAL: std::unreachable();
                    }
                }
            }
        }
        hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
    }

    void UpdateEvaluationScene::DisplayEventResult() {
        app::AppContext_ty_c appContext = app::AppContext::GetInstance();
        auto const data                 = m_result.Events().at(m_currentIndex);
        auto const playerName           = appContext.playerCollection.GetPlayerByID(data->PlayerID()).GetName();
        auto title                      = std::string();
        auto text                       = std::string();

        switch (data->Type()) {
            case utl::GameEventType::PIRATES: break;
            case utl::GameEventType::REVOLTS: break;
            case utl::GameEventType::RENEGADE_SHIPS: break;
            case utl::GameEventType::BLACK_HOLE: break;
            case utl::GameEventType::SUPERNOVA: break;
            case utl::GameEventType::ENGINE_PROBLEM: {
                auto const* result = dynamic_cast<utl::ResultEventEngineProblem const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "-> nullptr while dynamic cast a Engine Problem Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_engine_problem_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_engine_problem_text", result->FleetID(), playerName, result->Years());
                break;
            }
            case utl::GameEventType::GLOBAL: std::unreachable();
        }

        auto const event = eve::ShowEventResultPopUp(title, text, [this]() { this->m_nextPopup = true; });
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::DisplayMergeResult() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto const data{ m_result.Merges().at(m_currentIndex) };
        auto const playerName{ appContext.playerCollection.GetPlayerByID(data.GetPlayer().ID).GetName() };

        std::string spaceObjectText;
        switch (data.GetDestination().type) {
            case utl::SpaceObjectType::PLANET:
                spaceObjectText = appContext.languageManager.Text("helper_planet");
                break;
            case utl::SpaceObjectType::TARGET_POINT:
                spaceObjectText = appContext.languageManager.Text("helper_target_point");
                break;
            case utl::SpaceObjectType::FLEET: spaceObjectText = appContext.languageManager.Text("helper_fleet"); break;
            default: spaceObjectText = "Invalid"; break;
        }

        std::string const subText{ appContext.languageManager.Text("ui_popup_arriving_fleet_subtitle",
                                                                   data.GetCount(),
                                                                   playerName,
                                                                   spaceObjectText,
                                                                   data.GetDestination().ID) };

        eve::ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_arriving_fleet_title"),
                                                subText,
                                                [this]() { this->m_nextPopup = true; } };
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::DisplayFightResult() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        eve::ShowFightResultEvent const event{ m_result.Fights().at(m_currentIndex),
                                               [this]() { this->m_nextPopup = true; } };
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::HandleNextPopup() {

        auto const setNext{ [&]() {
            m_currentIndex = 0;
            auto value     = static_cast<utl::usize>(m_currentResultType);
            ++value;
            m_currentResultType = static_cast<ResultType>(value);
        } };

        switch (m_currentResultType) {
            case ResultType::EVENT:
                if (m_currentIndex >= m_result.Events().size()) {
                    setNext();
                    goto merge;
                }
                DisplayEventResult();
                break;
            case ResultType::MERGE:
            merge:
                if (m_currentIndex >= m_result.Merges().size()) {
                    setNext();
                    goto fight;
                }
                DisplayMergeResult();
                break;
            case ResultType::FIGHT:
            fight:
                if (m_currentIndex >= m_result.Fights().size()) {
                    setNext();
                    goto last;
                }
                DisplayFightResult();
                break;
            default:
            case ResultType::LAST:
            last:
                app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
                if (m_popupCount == 0) {
                    eve::ShowMessagePopUpEvent const event{
                        appContext.languageManager.Text("ui_popup_no_evaluation_title"),
                        appContext.languageManager.Text("ui_popup_no_evaluation_subtitle"),
                        [this]() { this->HandleNextPopup(); }
                    };
                    appContext.eventManager.InvokeEvent(event);
                    break;
                }
                eve::ShowMessagePopUpEvent const event{
                    appContext.languageManager.Text("ui_popup_end_of_evaluation_title"),
                    appContext.languageManager.Text("ui_popup_end_of_evaluation_subtitle"),
                    []() {
                        eve::SwitchSceneEvent const e{ uil::SceneType::MAIN };
                        app::AppContext::GetInstance().eventManager.InvokeEvent(e);
                    }
                };
                appContext.eventManager.InvokeEvent(event);
                break;
        }

        ++m_popupCount;
        ++m_currentIndex;
    }

    UpdateEvaluationScene::UpdateEvaluationScene() : Scene({ 0.0f, 0.0f }, { 1.0f, 1.0f }, uil::Alignment::DEFAULT) {

        app::AppContext_ty appContext{ app::AppContext::GetInstance() };
        appContext.eventManager.AddListener(this);
        appContext.eventManager.InvokeEvent(eve::GetUpdateEvaluation{});
    }

    UpdateEvaluationScene::~UpdateEvaluationScene() {
        app::AppContext::GetInstance().eventManager.RemoveListener(this);
    }

    void UpdateEvaluationScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
        Scene::CheckAndUpdate(mousePosition, appContext);

        if (m_nextPopup) {
            m_nextPopup = false;
            HandleNextPopup();
        }
    }
    void UpdateEvaluationScene::OnEvent(eve::Event const& event) {
        if (auto const* evEvent = dynamic_cast<eve::SendUpdateEvaluation const*>(&event)) {
            m_result = evEvent->Result();
            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
            eve::ShowMessagePopUpEvent const messageEvent{
                appContext.languageManager.Text("ui_popup_no_evaluation_title"),
                appContext.languageManager.Text("ui_popup_start_evaluation_subtitle"),
                [this]() { this->m_nextPopup = true; }
            };
            appContext.eventManager.InvokeEvent(messageEvent);
            TestPrint(evEvent); // to print the incoming event to the console
        }
    }
} // namespace ui
