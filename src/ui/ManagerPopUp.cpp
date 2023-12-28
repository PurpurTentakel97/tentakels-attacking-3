//
// Purpur Tentakel
// 05.09.2022
//

#include "ManagerPopUp.hpp"
#include <helper/HFocusEvents.hpp>
#include <helper/HPrint.hpp>

ManagerPopUp::ManagerPopUp() {
    app::AppContext::GetInstance().eventManager.AddListener(this);
    hlp::Print(hlp::PrintType::INITIALIZE, "ManagerPopUp");
}

ManagerPopUp::~ManagerPopUp() {
    app::AppContext::GetInstance().eventManager.RemoveListener(this);
}

bool ManagerPopUp::IsActivePopUp() const {
    return !m_popUps.empty();
}

void ManagerPopUp::OnEvent(eve::Event const& event) {

    // Message Pop Up
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowMessagePopUpEvent const*>(&event)) {
        NewMessagePopUp(PopUpEvent);
        return;
    }

    // Delete Player Pop Up
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowDeletePlayerPopUpEvent const*>(&event)) {
        NewDeletePlayerPopUp(PopUpEvent);
        return;
    }

    // Table Pop Up
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowCellPopUpEvent<std::string> const*>(&event)) {
        NewTableCellPopUp<std::string, eve::ShowCellPopUpEvent<std::string>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowCellPopUpEvent<int> const*>(&event)) {
        NewTableCellPopUp<int, eve::ShowCellPopUpEvent<int>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowCellPopUpEvent<float> const*>(&event)) {
        NewTableCellPopUp<float, eve::ShowCellPopUpEvent<float>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowCellPopUpEvent<double> const*>(&event)) {
        NewTableCellPopUp<double, eve::ShowCellPopUpEvent<double>>(PopUpEvent);
        return;
    }
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowCellPopUpEvent<Color> const*>(&event)) {
        NewColorCellPopUp(PopUpEvent);
        return;
    }

    // Initial Sound Pop Up
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowInitialSoundLevelPopUpEvent const*>(&event)) {
        NewSoundLevelPopUp(PopUpEvent);
        return;
    }

    // Turn Events
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowValidatePopUp const*>(&event)) {
        NewValidatePopUp(PopUpEvent);
        return;
    }

    // Fight Result
    if (auto const* PopUpEvent = dynamic_cast<eve::ShowFightResultEvent const*>(&event)) {
        NewFightResultPopUp(PopUpEvent);
        return;
    }

    // Close Pop Up
    if (auto const* PopUpEvent = dynamic_cast<eve::ClosePopUpEvent const*>(&event)) {
        DeleteLastPopUp(PopUpEvent->GetPop());
        return;
    }
}

void ManagerPopUp::NewMessagePopUp(eve::ShowMessagePopUpEvent const* const event) {
    hlp::AddFocusLayer(true);

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

void ManagerPopUp::NewDeletePlayerPopUp(eve::ShowDeletePlayerPopUpEvent const* const event) {
    hlp::AddFocusLayer(true);

    m_popUps.push_back(std::make_unique<DeletePlayerPopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            AssetType::QUESTION_MARK,
            event->GetOnClick()
    ));
}

void ManagerPopUp::NewValidatePopUp(eve::ShowValidatePopUp const* const event) {
    hlp::AddFocusLayer(true);

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

void ManagerPopUp::NewColorCellPopUp(eve::ShowCellPopUpEvent<Color> const* const event) {
    app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
    eve::NewFocusPopUpLayerEvent focusEvent;
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

void ManagerPopUp::NewSoundLevelPopUp(eve::ShowInitialSoundLevelPopUpEvent const* const event) {
    app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
    eve::NewFocusPopUpLayerEvent focusEvent;
    appContext.eventManager.InvokeEvent(focusEvent);

    m_popUps.push_back(std::make_unique<SoundLevelPopUp>(
            Vector2(0.5f, 0.5f),
            Vector2(0.5f, 0.5f),
            Alignment::MID_MID,
            event->GetTitle(),
            const_cast<std::string&>(event->GetSubTitle())
    ));
}
void ManagerPopUp::NewFightResultPopUp(eve::ShowFightResultEvent const* const event) {
    app::AppContext_ty_c appContext{ app::AppContext::GetInstance() };
    eve::NewFocusLayerEvent focusEvent;
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

        hlp::DeleteFocusLayer(true);
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
                hlp::DeleteFocusLayer(true);
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

void ManagerPopUp::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
    if (!IsActivePopUp()) {
        return;
    }

    m_popUps.back()->CheckAndUpdate(mousePosition, appContext);
}

void ManagerPopUp::Render(app::AppContext_ty_c appContext) {
    for (auto& p : m_popUps) {
        p->Render(appContext);
    }
}

void ManagerPopUp::Resize(app::AppContext_ty_c appContext) {
    for (auto& e : m_popUps) {
        e->Resize(appContext);
    }
}
