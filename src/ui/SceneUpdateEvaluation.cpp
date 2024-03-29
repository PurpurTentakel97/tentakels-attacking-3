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
                       appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayers().first.ID).GetName(),
                       appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayers().second.ID).GetName());

            for (auto const& r : e.GetRounds()) {
                hlp::Print(hlp::PrintType::DEBUG, "{} | {}", r.first, r.second);
            }
            hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
        }
        hlp::Print(hlp::PrintType::DEBUG, "---------------- | BlackHole Result |-------------------");
        for (auto const& b : event->Result().BlackHoles()) {
            hlp::Print(hlp::PrintType::DEBUG,
                       "Black Hole: {}, Object {} from player {} with {} ships got destroyed. New Size: {}",
                       b.BlackHole().ID,
                       b.ObjectDestroyed().ID,
                       appContext.playerCollection.GetPlayerOrNpcByID(b.Player().ID).GetName(),
                       b.ShipsDestroyed(),
                       b.BlackHole().radius);
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
                            auto const* result = dynamic_cast<utl::ResultEventPirates const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Pirate Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "-> Pirates at X: {}, Y: {} | Ships: {}",
                                       result->Position().x,
                                       result->Position().y,
                                       result->Ships());
                            break;
                        }
                        case utl::GameEventType::REVOLTS: {
                            hlp::Print(hlp::PrintType::DEBUG, "revolts event result");
                            auto const* result = dynamic_cast<utl::ResultEventRevolts const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Revolts Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "revolts on planet {} from player {} with {} ships",
                                       result->PlanetID(),
                                       result->PlayerID(),
                                       result->ShipCount());
                            break;
                        }
                        case utl::GameEventType::RENEGADE_SHIPS: {
                            hlp::Print(hlp::PrintType::DEBUG, "renegade ships event result");
                            auto const* result = dynamic_cast<utl::ResultEventRenegadeShips const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Renegade Ships Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "renegade ships at fleet {} from player {} with {} ships",
                                       result->FleetID(),
                                       result->PlayerID(),
                                       result->ShipCount());
                            break;
                        }
                        case utl::GameEventType::SUPERNOVA: {
                            hlp::Print(hlp::PrintType::DEBUG, "supernova event result");
                            auto const* result = dynamic_cast<utl::ResultEventSupernova const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Supernova Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "-> planet {} with {} ships from player {} got destroyed",
                                       result->PlanetID(),
                                       result->ShipsDestroyed(),
                                       result->PlayerID());
                            break;
                        }
                        case utl::GameEventType::ENGINE_PROBLEM: {
                            hlp::Print(hlp::PrintType::DEBUG, "Engine Problem Event Result");
                            auto const* result = dynamic_cast<utl::ResultEventEngineProblem const*>(e.get());
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
                        case utl::GameEventType::PRODUCTION_PROBLEM: {
                            hlp::Print(hlp::PrintType::DEBUG, "Production Problem Event Result");
                            auto const* result = dynamic_cast<utl::ResultEventProductionProblem const*>(e.get());
                            if (not result) {
                                hlp::Print(hlp::PrintType::ERROR,
                                           "-> nullptr while dynamic cast a Production Problem Event Result");
                                break;
                            }
                            hlp::Print(hlp::PrintType::DEBUG,
                                       "-> planet {} from player {} will not be able to move within the next {} years",
                                       result->PlanetID(),
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
        auto const playerName           = appContext.playerCollection.GetPlayerOrNpcByID(data->PlayerID()).GetName();
        auto title                      = std::string();
        auto text                       = std::string();

        switch (data->Type()) {
            case utl::GameEventType::PIRATES: {
                auto const* result = dynamic_cast<utl::ResultEventPirates const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Pirate Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_pirates_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_pirates_text", result->Ships(), result->Position().x, result->Position().y);
                break;
            }
            case utl::GameEventType::REVOLTS: {
                auto const* result = dynamic_cast<utl::ResultEventRevolts const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Revolts Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_revolts_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_revolts_text", result->ShipCount(), playerName, result->PlanetID());
                break;
            }
            case utl::GameEventType::RENEGADE_SHIPS: {
                auto const* result = dynamic_cast<utl::ResultEventRenegadeShips const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Renegade Ships Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_renegade_ships_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_renegade_ships_text", result->ShipCount(), playerName, result->FleetID());
                break;
            }
            case utl::GameEventType::SUPERNOVA: {
                auto const* result = dynamic_cast<utl::ResultEventSupernova const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Supernova Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_supernova_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_supernova_text", result->PlanetID(), result->ShipsDestroyed(), playerName);
                break;
            }
            case utl::GameEventType::ENGINE_PROBLEM: {
                auto const* result = dynamic_cast<utl::ResultEventEngineProblem const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Engine Problem Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_engine_problem_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_engine_problem_text", result->FleetID(), playerName, result->Years());
                break;
            }
            case utl::GameEventType::PRODUCTION_PROBLEM: {
                auto const* result = dynamic_cast<utl::ResultEventProductionProblem const*>(data.get());
                if (not result) {
                    hlp::Print(hlp::PrintType::ERROR, "nullptr while dynamic cast a Production Problem Event Result");
                    break;
                }
                title = appContext.languageManager.Text("evaluation_event_production_problem_title");
                text  = appContext.languageManager.Text(
                        "evaluation_event_production_problem_text", result->PlanetID(), playerName, result->Years());
                // Planet {0} from player {1} will not be able to produce for {2} years.
                break;
            }
            case utl::GameEventType::GLOBAL: std::unreachable();
        }

        auto const event = eve::ShowRedResultPopUp(title, text, [this]() { this->m_nextPopup = true; });
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::DisplayBlackHoleResult() {
        app::AppContext_ty_c appContext = app::AppContext::GetInstance();
        auto const data                 = m_result.BlackHoles().at(m_currentIndex);
        auto const playerName           = appContext.playerCollection.GetPlayerOrNpcByID(data.Player().ID).GetName();

        std::string text{};
        switch (data.ObjectDestroyed().type) {
            case utl::SpaceObjectType::TARGET_POINT: {
                // Target Point {} from player {} got destroyed. {} ships are gone.
                text = appContext.languageManager.Text("evaluation_black_hole_target_point_text",
                                                       data.ObjectDestroyed().ID,
                                                       playerName,
                                                       data.ShipsDestroyed());
                break;
            }
            case utl::SpaceObjectType::FLEET: {
                text = appContext.languageManager.Text("evaluation_black_hole_fleet_text",
                                                       data.ObjectDestroyed().ID,
                                                       playerName,
                                                       data.ShipsDestroyed());
                break;
            }
            case utl::SpaceObjectType::PLANET: {
                text = appContext.languageManager.Text("evaluation_black_hole_planet_text",
                                                       data.ObjectDestroyed().ID,
                                                       playerName,
                                                       data.ShipsDestroyed());
                break;
            }
            default: {
                text = "invalid Space Object while displaying popup";
                hlp::Print(hlp::PrintType::ERROR, "default case in SpaceObjectType while displaying black hole popup");
                break;
            }
        }

        // clang-format off
        auto const event = eve::ShowRedResultPopUp(
                appContext.languageManager.Text("evaluation_black_hole_title", data.BlackHole().ID),
                text,
                [this]() { this->m_nextPopup = true; }
        );
        // clang-format on
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
    } // namespace ui

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
                    goto black_hole;
                }
                DisplayEventResult();
                break;
            case ResultType::BLACK_HOLE:
            black_hole:
                if (m_currentIndex >= m_result.BlackHoles().size()) {
                    setNext();
                    goto merge;
                }
                DisplayBlackHoleResult();
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
