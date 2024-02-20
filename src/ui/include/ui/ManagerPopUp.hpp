//
// Purpur Tentakel
// 05.09.2022
//

#pragma once

#include "PopUpExtra.hpp"
#include <event/EventListener.hpp>
#include <event/EventsUI.hpp>
#include <memory>
#include <string>
#include <ui_lib/PopUpAll.hpp>
#include <vector>


namespace ui {
    class ManagerPopUp final : public eve::EventListener {
    private:
        std::vector<std::unique_ptr<uil::PopUp>> m_popUps;
        std::vector<uil::PopUp*> m_toDelete;
        uil::PopUp* m_deleteNext{ nullptr };

    public:
        ManagerPopUp();

        ~ManagerPopUp() override;

        [[nodiscard]] bool IsActivePopUp() const;

        void OnEvent(eve::Event const& event) override;

        void NewMessagePopUp(eve::ShowMessagePopUpEvent const* event);

        void NewValidatePopUp(eve::ShowValidatePopUp const* event);

        void NewColorCellPopUp(eve::ShowCellPopUpEvent<Color> const* event);

        void NewSoundLevelPopUp(eve::ShowInitialSoundLevelPopUpEvent const* event);

        void NewFightResultPopUp(eve::ShowFightResultEvent const* event);
        void NewEventResultPopUp(eve::ShowRedResultPopUp const* event);

        void NewColorPopUp(eve::ShowColorPopupEvent const* event);
        void NewStringPopUp(eve::ShowStringPopupEvent const* event);
        void NewDoublePopUp(eve::ShowDoublePopupEvent const* event);
        void NewUSizePopUp(eve::ShowUSizePopupEvent const* event);

        void DeleteLastPopUp(uil::PopUp* toDelete);

        void CheckDelete();

        void CheckForDeleteRemainingPopUps();

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext);

        void Render(app::AppContext_ty_c appContext);

        void Resize(app::AppContext_ty_c appContext);
    };
} // namespace ui
