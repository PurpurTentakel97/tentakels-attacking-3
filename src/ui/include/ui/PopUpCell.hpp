//
// Purpur Tentakel
// 03.10.2022
//

#pragma once
#include "ui_lib/ButtonClassic.hpp"
#include "ui_lib/PopUp.hpp"

/**
 * provides the basic cell popup for editing the table.
 */
class CellPopUp : public PopUp {
protected:
	bool m_shouldClose{ false }; ///< contains if the popup should close an the end of the tick

	/**
	 * initializes all ui elements.
	 */
	virtual void Initialize();
	/**
	 * initializes the accept button.
	 */
	[[nodiscard]] ClassicButton_ty InitializeAcceptButton();

	/**
	 * sets the should close bool to true so this popup will close at the end of the tick.
	 */
	void SetShouldClose();
	/**
	 * virtual function to make sure every cell popup can set a value to the table.
	 */
	virtual void SetValue() = 0;

	/**
	 * checks if ender is pressed an sets the value if so.
	 */
	void CheckEnter();
	/**
	 * calls the close event at the end of the tick.
	 */
	void Close(AppContext_ty_c appContext);
public:
	/**
	 * ctor.
	 * only initialisation.
	 */
	CellPopUp(Vector2 pos, Vector2 size, Alignment alignment,
		std::string const& title, AssetType infoTexture);

	/**
	 * cell popup logic.
	 * gets extended by child classes.
	 */
	virtual void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
};
