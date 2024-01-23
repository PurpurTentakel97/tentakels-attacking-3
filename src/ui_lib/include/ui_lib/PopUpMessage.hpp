//
// Purpur Tentakel
// 10.09.2022
//

#pragma once

#include "ButtonClassic.hpp"
#include "PopUp.hpp"
#include <functional>


namespace uil {
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
} // namespace ui
