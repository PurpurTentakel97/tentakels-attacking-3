//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "PopUpAll.hpp"
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <string>
#include <vector>


class ManagerPopUp final : public EventListener {
private:
    std::vector<std::unique_ptr<PopUp>> m_popUps;
    std::vector<PopUp*> m_toDelete;

public:
    ManagerPopUp();

    ~ManagerPopUp() override;

    [[nodiscard]] bool IsActivePopUp() const;

    void OnEvent(Event const& event) override;

    void NewMessagePopUp(ShowMessagePopUpEvent const* event);

    void NewDeletePlayerPopUp(ShowDeletePlayerPopUpEvent const* event);

    void NewValidatePopUp(ShowValidatePopUp const* event);

    void NewColorCellPopUp(ShowCellPopUpEvent<Color> const* event);

    void NewSoundLevelPopUp(ShowInitialSoundLevelPopUpEvent const* event);

    void NewFightResultPopUp(ShowFightResultEvent const* event);

    template<typename T, typename eventType>
    void NewTableCellPopUp(eventType const* const event) {
        AppContext_ty_c appContext{ AppContext::GetInstance() };
        NewFocusPopUpLayerEvent const focusEvent;
        appContext.eventManager.InvokeEvent(focusEvent);

        m_popUps.push_back(std::make_unique<PrimitiveCellPopUp<T>>(
                Vector2(0.5f, 0.5f),
                Vector2(0.7f, 0.7f),
                Alignment::MID_MID,
                event->GetTitle(),
                AssetType::LOGO,
                event->GetCurrentValue(),
                event->GetOnClick()
        ));
    }

    void DeleteLastPopUp(PopUp* toDelete);

    void CheckForDeleteRemainingPopUps();

    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);

    void Render(AppContext_ty_c appContext);

    void Resize(AppContext_ty_c appContext);
};
