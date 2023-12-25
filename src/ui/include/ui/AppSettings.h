//
// Purpur Tentakel
// 18.07.2023
//

#pragma once
#include "Settings.h"
#include "event/EventListener.hpp"

class SliderAndInputLine;

class AppSettingsScene final : public SettingsScene, public EventListener {
private:
	std::vector<std::pair<Resolution, std::string>> m_rawResolutionEntries; ///< contains die raw resolution information
	std::shared_ptr<SliderAndInputLine> m_volume; ///< contains the volume slider
	DropDown_ty m_languageDropDown; ///< contains the language drop down
	DropDown_ty m_resolutionDropDown; ///< contains the language drop down
	CheckBox_ty m_toggleFullScreenCBM; ///< contains the full screen toggle check box
	
	/**
	 * initializes all ui elements.
	 * connects the actions.
	 */
	void Initialize();

	/**
	 * returns the strings out of the raw resolution data.
	 */
	std::vector<std::string> GetStringsFromResolutionEntries() const;
	/**
	 * returns index from resolution enum.
	 */
	int GetIndexFromResolution(Resolution resolution) const;

public:

	AppSettingsScene();
	~AppSettingsScene();

	/**
	 * updates all elements in elements.
	 */
	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	/**
	 * renders all elements in elements and elements out update.
	 */
	void Render(AppContext_ty_c appContext) override;
	/**
	 * resizes all elements in elements and elements out update.
	 */
	void Resize(AppContext_ty_c appContext) override;

	void OnEvent(Event const& event) override;
};
