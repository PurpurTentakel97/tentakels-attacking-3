//
// Purpur Tentakel
// 05.06.2023
//

#include "SceneUpdateEvaluation.hpp"
#include <app/AppContext.hpp>
#include <event/EventGeneral.hpp>
#include <helper/HPrint.hpp>
#include <logic/Player.hpp>
#include <logic/SpaceObject.hpp>
#include <ui_lib/SceneType.hpp>


namespace ui {
    void UpdateEvaluationScene::TestPrint(eve::SendUpdateEvaluation const* event) {

        /**
	 * call in OnEvent.
	 * only for debugging.
	 */

        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        hlp::Print(hlp::PrintType::DEBUG, "--------------------| Evaluation |--------------------");

        hlp::Print(hlp::PrintType::DEBUG, "------------------ | Merge Results |------------------");
        for (auto const& e : event->GetMergeResults()) {
            hlp::Print(
                    hlp::PrintType::DEBUG,
                    "{}",
                    appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer()->GetID()).GetName()
            );
            hlp::Print(
                    hlp::PrintType::DEBUG,
                    "origin: {} -> destination: {} -> count: {}",
                    e.GetOrigin()->GetID(),
                    e.GetDestination()->GetID(),
                    e.GetCount()
            );
            hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
        }

        hlp::Print(hlp::PrintType::DEBUG, "------------------ | Fight Results |------------------");
        for (auto const& e : event->GetFightResults()) {
            if (not e.IsValid()) {
                hlp::Print(hlp::PrintType::DEBUG, "invalid update Evaluation");
                continue;
            }

            hlp::Print(
                    hlp::PrintType::DEBUG,
                    "{} vs.{}",
                    e.GetSpaceObjects().first->GetID(),
                    e.GetSpaceObjects().second->GetID()
            );
            hlp::Print(
                    hlp::PrintType::DEBUG,
                    "{} vs. {}",
                    appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().first->GetID()).GetName(),
                    appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().second->GetID()).GetName()
            );

            for (auto const& r : e.GetRounds()) {
                hlp::Print(hlp::PrintType::DEBUG, "{} | {}", r.first, r.second);
            }
            hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
        }
        hlp::Print(hlp::PrintType::DEBUG, "------------------------------------------------------");
    }

    void UpdateEvaluationScene::DisplayMergeResult() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
        auto const data{ m_mergeResults.at(m_currentIndex) };
        auto const playerName{ appContext.playerCollection.GetPlayerByID(data.GetPlayer()->GetID()).GetName() };

        std::string spaceObjectText;
        if (data.GetDestination()->IsFleet()) {
            spaceObjectText = appContext.languageManager.Text("helper_fleet");
        } else if (data.GetDestination()->IsPlanet()) {
            spaceObjectText = appContext.languageManager.Text("helper_planet");
        } else if (data.GetDestination()->IsTargetPoint()) {
            spaceObjectText = appContext.languageManager.Text("helper_target_point");
        } else {
            spaceObjectText = "Invalid";
        }

        std::string const subText{ appContext.languageManager.Text(
                "ui_popup_arriving_fleet_subtitle",
                data.GetCount(),
                playerName,
                spaceObjectText,
                data.GetDestination()->GetID()
        ) };

        eve::ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_arriving_fleet_title"),
                                                subText,
                                                [this]() { this->m_nextPopup = true; } };
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::DisplayFightResult() {
        app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };

        eve::ShowFightResultEvent const event{ m_fightResults.at(m_currentIndex),
                                               [this]() { this->m_nextPopup = true; } };
        appContext.eventManager.InvokeEvent(event);
    }

    void UpdateEvaluationScene::HandleNextPopup() {

        auto const setNext{ [&]() {
            m_currentIndex = 0;
            int value = static_cast<int>(m_currentResultType);
            ++value;
            m_currentResultType = static_cast<ResultType>(value);
        } };

        switch (m_currentResultType) {
            case ResultType::MERGE:
                if (m_currentIndex >= m_mergeResults.size()) {
                    setNext();
                    goto fight;
                }
                DisplayMergeResult();
                break;
            case ResultType::FIGHT:
            fight:
                if (m_currentIndex >= m_fightResults.size()) {
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
            m_mergeResults = evEvent->GetMergeResults();
            m_fightResults = evEvent->GetFightResults();
            app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
            eve::ShowMessagePopUpEvent const messageEvent{
                appContext.languageManager.Text("ui_popup_no_evaluation_title"),
                appContext.languageManager.Text("ui_popup_start_evaluation_subtitle"),
                [this]() { this->m_nextPopup = true; }
            };
            appContext.eventManager.InvokeEvent(messageEvent);
            // TestPrint(evEvent); // to print the incoming event to the console
        }
    }
} // namespace ui
