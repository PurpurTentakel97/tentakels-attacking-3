//
// Purpur Tentakel
// 05.09.2022
//

#include "ManagerPopUp.hpp"
#include <helper/HFocusEvents.hpp>
#include <helper/HPrint.hpp>

ManagerPopUp::ManagerPopUp() {
    AppContext::GetInstance().eventManager.AddListener(this);
    Print(PrintType::INITIALIZE, "ManagerPopUp");
}

ManagerPopUp::~ManagerPopUp() {
    AppContext::GetInstance().eventManager.RemoveListener(this);
}

bool ManagerPopUp::IsActivePopUp() const {
    return !m_popUps.empty();
}

void ManagerPopUp::OnEvent(Event const& event) {

    // Message Pop Up
    if (auto const* PopUpEvent = dynamic_cast<ShowMessagePopUpEvent const*>(&event)) {
        NewMessagePopUp(PopUpEvent);
        return;
    }

    // Delete Player Pop Up
    if (auto const* PopUpEvent = dynamic_cast<ShowDeletePlayerPopUpEvent const*>(&event)) {
        NewDeletePlayerPopUp(PopUpEvent);
        return;
    }

    // Table Pop Up
    if (auto const* PopUpEvent = dynamic_cast<ShowCellPopUpEvent<std::string> const*>(&event)) {
        NewTableCellPopUp<std::string, ShowCellPopUpEvent<std::string>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<ShowCellPopUpEvent<int> const*>(&event)) {
        NewTableCellPopUp<int, ShowCellPopUpEvent<int>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<ShowCellPopUpEvent<float> const*>(&event)) {
        NewTableCellPopUp<float, ShowCellPopUpEvent<float>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<ShowCellPopUpEvent<double> const*>(&event)) {
        NewTableCellPopUp<double, ShowCellPopUpEvent<double>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<ShowCellPopUpEvent<Color> const*>(&event)) {
        NewColorCellPopUp(PopUpEvent);
        return;
    }

    // Initial Sound Pop Up
    if (auto const* PopUpEvent = dynamic_cast<ShowInitialSoundLevelPopUpEvent const*>(&event)) {
        NewSoundLevelPopUp(PopUpEvent);
        return;
    }

    // Turn Events
    if (auto const* PopUpEvent = dynamic_cast<ShowValidatePopUp const*>(&event)) {
        NewValidatePopUp(PopUpEvent);
        return;
    }

    // Fight Result
    if (auto const* PopUpEvent = dynamic_cast<ShowFightResultEvent const*>(&event)) {
        NewFightResultPopUp(PopUpEvent);
        return;
    }

    // Close Pop Up
    if (auto const* PopUpEvent = dynamic_cast<ClosePopUpEvent const*>(&event)) {
        DeleteLastPopUp(PopUpEvent->GetPop());
        return;
    }
}

void ManagerPopUp::NewMessagePopUp(ShowMessagePopUpEvent const* const event) {
    AddFocusLayer(true);

    m_popUps.push_back(std::make_unique<MessagePopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            const_cast<std::string&>(event->GetSubTitle()),
            AssetType::EXCLAMATION_MARK,
            event->GetCallback()
    ));
}

void ManagerPopUp::NewDeletePlayerPopUp(ShowDeletePlayerPopUpEvent const* const event) {
    AddFocusLayer(true);

    m_popUps.push_back(std::make_unique<DeletePlayerPopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            AssetType::QUESTION_MARK,
            event->GetOnClick()
    ));
}

void ManagerPopUp::NewValidatePopUp(ShowValidatePopUp const* const event) {
    AddFocusLayer(true);

    m_popUps.push_back(std::make_unique<ValidatePopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            const_cast<std::string&>(event->GetSubTitle()),
            AssetType::QUESTION_MARK,
            event->GetCallback()
    ));
}

void ManagerPopUp::NewColorCellPopUp(ShowCellPopUpEvent<Color> const* const event) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    NewFocusPopUpLayerEvent focusEvent;
    appContext.eventManager.InvokeEvent(focusEvent);

    m_popUps.push_back(std::make_unique<ColorCellPopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.7f, 0.7f),
            Alignment::MID_MID,
            event->GetTitle(),
            AssetType::LOGO,
            event->GetCurrentValue(),
            event->GetOnClick()
    ));
}

void ManagerPopUp::NewSoundLevelPopUp(ShowInitialSoundLevelPopUpEvent const* const event) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    NewFocusPopUpLayerEvent focusEvent;
    appContext.eventManager.InvokeEvent(focusEvent);

    m_popUps.push_back(std::make_unique<SoundLevelPopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            const_cast<std::string&>(event->GetSubTitle())
    ));
}
void ManagerPopUp::NewFightResultPopUp(ShowFightResultEvent const* const event) {
    AppContext_ty_c appContext{ AppContext::GetInstance() };
    NewFocusLayerEvent focusEvent;
    appContext.eventManager.InvokeEvent(focusEvent);

    m_popUps.push_back(std::make_unique<FightResultPopup>(
            Vector2(0.5f, 0.5f),
            Vector2(0.8f, 0.8f),
            Alignment::MID_MID,
            event->GetResult(),
            event->GetCallback()
    ));
}

void ManagerPopUp::DeleteLastPopUp(PopUp* const toDelete) {
    if (m_popUps.empty()) {
        return;
    }

    if (toDelete == m_popUps.back().get()) {

        DeleteFocusLayer(true);
        m_popUps.pop_back();

        CheckForDeleteRemainingPopUps();
    } else {
        m_toDelete.push_back(toDelete);
    }
}

void ManagerPopUp::CheckForDeleteRemainingPopUps() {
    while (true) {
        if (m_popUps.empty()) {
            m_toDelete.clear();
            return;
        }
        if (m_toDelete.empty()) {
            return;
        }

        bool found{ false };
        for (auto& p : m_toDelete) {
            if (p == m_popUps.back().get()) {
                found = true;
                DeleteFocusLayer(true);
                m_popUps.pop_back();

                m_toDelete.erase(std::remove(m_toDelete.begin(), m_toDelete.end(), p), m_toDelete.end());
                break;
            }
        }

        if (!found) {
            return;
        }
    }
}

void ManagerPopUp::CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) {
    if (!IsActivePopUp()) {
        return;
    }

    m_popUps.back()->CheckAndUpdate(mousePosition, appContext);
}

void ManagerPopUp::Render(AppContext_ty_c appContext) {
    for (auto& p : m_popUps) {
        p->Render(appContext);
    }
}

void ManagerPopUp::Resize(AppContext_ty_c appContext) {
    for (auto& e : m_popUps) {
        e->Resize(appContext);
    }
}
