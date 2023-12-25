//
// Purpur Tentakel
// 05.09.2022
//

#pragma once
#include "event/UIEvents.hpp"
#include "AllPopUp.hpp"
#include "event/EventListener.hpp"
#include <memory>
#include <string>
#include <vector>
/**
 * manages the popups.
 * contains the popups.
 */
class PopUpManager final : public EventListener {
private:
	std::vector<std::unique_ptr<PopUp>> m_popUps; ///< contains all popups
	std::vector<PopUp*> m_toDelete; ///< contains the popups that should be deleted but not able to do so yet

public:
	/**
	 * ctor.
	 * adds this as an event listener.
	 */
	PopUpManager();
	/**
	 * removes the event listener
	 */
	~PopUpManager();

	/**
	 * returns if the it contains at least one popup.
	 */
	[[nodiscard]] bool IsActivePopUp() const;

	/**
	 * receives alle event and calls the member functions.
	 */
	void OnEvent(Event const& event) override;

	/**
	 * adds a new focus layer.
	 * generates a new message popup.
	 */
	void NewMessagePopUp(ShowMessagePopUpEvent const* event);
	/**
	 * adds a new focus layer.
	 * generates a new delete player popup.
	 */
	void NewDeletePlayerPopUp(ShowDeletePlayerPopUpEvent const* event);
	/**
	 * adds a new focus layer.
	 * generates a new validation popup.
	 */
	void NewValidatePopUp(ShowValidatePopUp const* event);
	/**
	 * adds a new focus layer.
	 * generates a new color cell (for color picker class) popup.
	 */
	void NewColorCellPopUp(ShowCellPopUpEvent<Color> const* event);
	/**
	 * adds a new focus layer.
	 * generates a new sound level popup.
	 */
	void NewSoundLevelPopUp(ShowInitialSoundLevelPopUpEvent const* event);
	/**
	 * adds a new focus layer.
	 * generates a new fight result popup.
	 */
	void NewFightResultPopUp(ShowFightResultEvent const* event);
	/**
	 * adds a new focus layer.
	 * generates a new primitive type cell (for table class) popup.
	 */
	template<typename T, typename eventType>
	void NewTableCellPopUp(eventType const* event) {
		AppContext_ty_c appContext{ AppContext::GetInstance() };
		NewFocusPopUpLayerEvent const focusEvent;
		appContext.eventManager.InvokeEvent(focusEvent);

		m_popUps.push_back(std::make_unique<PrivativeCellPopUp<T>>(
			Vector2(0.5f, 0.5f),
			Vector2(0.7f, 0.7f),
			Alignment::MID_MID,
			event->GetTitle(),
			AssetType::LOGO,
			event->GetCurrentValue(),
			event->GetOnClick()
			)
		);
	}

	/**
	 * returns if no popups are available.
	 * if the last popup is the provided popup, the popup gets deleted.
	 * else adds the popup into toDelete.
	 */
	void DeleteLastPopUp(PopUp* toDelete);
	/**
	 * checks if popups are remaining for possible deleting.
	 * checks if popups are remaining that should be deleted.
	 * deletes the popups, that are in toDelete.
	 */
	void CheckForDeleteRemainingPopUps();

	/**
	 * checks if any popup is active.
	 * calls the last popup to update.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext);
	/**
	 * calls all popups to render.
	 */
	void Render(AppContext_ty_c appContext);
	/**
	 * calls all popups to update.
	 */
	void Resize(AppContext_ty_c appContext);
};
