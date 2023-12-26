//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include <functional>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/PopUp.hpp>

/**
 * provides a popup that shows a message
 */
class MessagePopUp final : public PopUp {
private:
    std::function<void()> m_callback{ []() {
    } }; ///< contains the callback lambda that gets called when the popup is closed

    /**
	 * initializes all ui elements.
	 */
    void Initialize();

public:
    /**
	 * ctor
	 * only initialization.
	 */
    MessagePopUp(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            std::string const& title,
            std::string& subTitle,
            AssetType infoTexture,
            std::function<void()> callback
    );

    /**
	 * popup logic.
	 */
    void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
};
