//
// Purpur Tentakel
// 05.06.2023
//

#include "UpdateEvaluation.h"
#include "AppContext.h"
#include "event/GenerelEvents.hpp"
#include "helper/HPrint.h"
#include "logic/Player.h"
#include "logic/SpaceObject.h"
#include "ui_lib/SceneType.h"

void UpdateEvaluationScene::TestPrint(SendUpdateEvaluation const* event) const {

    /**
	 * call in OnEvent.
	 * only for debugging.
	 */

    AppContext_ty_c appContext{ AppContext::GetInstance() };

    Print(PrintType::DEBUG, "--------------------| Evaluation |--------------------");

    Print(PrintType::DEBUG, "------------------ | Merge Results |------------------");
    for (auto const& e : event->GetMergeResults()) {
        Print(PrintType::DEBUG, "{}", appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer()->GetID()).GetName());
        Print(PrintType::DEBUG,
              "origin: {} -> destination: {} -> count: {}",
              e.GetOrigin()->GetID(),
              e.GetDestination()->GetID(),
              e.GetCount());
        Print(PrintType::DEBUG, "------------------------------------------------------");
    }

    Print(PrintType::DEBUG, "------------------ | Fight Results |------------------");
    for (auto const& e : event->GetFightResults()) {
        if (not e.IsValid()) {
            Print(PrintType::DEBUG, "invalid update Evaluation");
            continue;
        }

        Print(PrintType::DEBUG, "{} vs.{}", e.GetSpaceObjects().first->GetID(), e.GetSpaceObjects().second->GetID());
        Print(PrintType::DEBUG,
              "{} vs. {}",
              appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().first->GetID()).GetName(),
              appContext.playerCollection.GetPlayerOrNpcByID(e.GetPlayer().second->GetID()).GetName());

        for (auto const& r : e.GetRounds()) {
            Print(PrintType::DEBUG, "{} | {}", r.first, r.second);
        }
        Print(PrintType::DEBUG, "------------------------------------------------------");
    }
    Print(PrintType::DEBUG, "------------------------------------------------------");
}

void UpdateEvaluationScene::DisplayMergeResult() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
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

    ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_arriving_fleet_title"),
                                       subText,
                                       [this]() { this->m_nextPopup = true; } };
    appContext.eventManager.InvokeEvent(event);
}
void UpdateEvaluationScene::DisplayFightResult() {
    AppContext_ty_c appContext{ AppContext::GetInstance() };

    ShowFightResultEvent const event{ m_fightResults.at(m_currentIndex), [this]() {
                                         this->m_nextPopup = true;
                                         ;
                                     } };
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
            AppContext_ty_c appContext{ AppContext::GetInstance() };
            if (m_popupCount == 0) {
                ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_no_evaluation_title"),
                                                   appContext.languageManager.Text("ui_popup_no_evaluation_subtitle"),
                                                   [this]() { this->HandleNextPopup(); } };
                appContext.eventManager.InvokeEvent(event);
                break;
            }
            ShowMessagePopUpEvent const event{ appContext.languageManager.Text("ui_popup_end_of_evaluation_title"),
                                               appContext.languageManager.Text("ui_popup_end_of_evaluation_subtitle"),
                                               []() {
                                                   SwitchSceneEvent const e{ SceneType::MAIN };
                                                   AppContext::GetInstance().eventManager.InvokeEvent(e);
                                               } };
            appContext.eventManager.InvokeEvent(event);
            break;
    }

    ++m_popupCount;
    ++m_currentIndex;
}

UpdateEvaluationScene::UpdateEvaluationScene() : Scene({ 0.0f, 0.0f }, { 1.0f, 1.0f }, Alignment::DEFAULT) {

    AppContext_ty appContext{ AppContext::GetInstance() };
    appContext.eventManager.AddListener(this);
    appContext.eventManager.InvokeEvent(GetUpdateEvaluation{});
}
UpdateEvaluationScene::~UpdateEvaluationScene() {
    AppContext::GetInstance().eventManager.RemoveListener(this);
}

void UpdateEvaluationScene::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    Scene::CheckAndUpdate(mousePosition, appContext);

    if (m_nextPopup) {
        m_nextPopup = false;
        HandleNextPopup();
    }
}

void UpdateEvaluationScene::OnEvent(Event const& event) {
    if (auto const* evEvent = dynamic_cast<SendUpdateEvaluation const*>(&event)) {
        m_mergeResults = evEvent->GetMergeResults();
        m_fightResults = evEvent->GetFightResults();
        AppContext_ty_c appContext{ AppContext::GetInstance() };
        ShowMessagePopUpEvent const messageEvent{ appContext.languageManager.Text("ui_popup_no_evaluation_title"),
                                                  appContext.languageManager.Text("ui_popup_start_evaluation_subtitle"),
                                                  [this]() { this->m_nextPopup = true; } };
        appContext.eventManager.InvokeEvent(messageEvent);
        // TestPrint(evEvent); // to print the incoming event to the console
    }
}
