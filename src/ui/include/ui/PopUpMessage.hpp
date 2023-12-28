//
// Purpur Tentakel
// 10.09.2022
//

#pragma once
#include <functional>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/PopUp.hpp>


class MessagePopUp final : public PopUp {
private:
    std::function<void()> m_callback{ []() {} };

    void Initialize();

public:
    MessagePopUp(
            Vector2 pos,
            Vector2 size,
            Alignment alignment,
            std::string const& title,
            std::string& subTitle,
            app::AssetType infoTexture,
            std::function<void()> callback
    );

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
};
