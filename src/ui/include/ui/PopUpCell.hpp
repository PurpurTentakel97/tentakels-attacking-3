//
// Purpur Tentakel
// 03.10.2022
//

#pragma once

#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/PopUp.hpp>


class CellPopUp : public PopUp {
protected:
    bool m_shouldClose{ false };

    virtual void Initialize();

    [[nodiscard]] ClassicButton_ty InitializeAcceptButton();

    void SetShouldClose();

    virtual void SetValue() = 0;

    void CheckEnter();

    void Close(app::AppContext_ty_c appContext);

public:
    CellPopUp(Vector2 pos, Vector2 size, Alignment alignment, std::string const& title, app::AssetType infoTexture);

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
};
