//
// Purpur Tentakel
// 10.09.2022
//

#pragma once

#include "ButtonClassic.hpp"
#include "PopUp.hpp"
#include <functional>


namespace uil {
    class MessagePopUp : public PopUp {
    public:
        using callback_ty = std::function<void()>;

    private:
        callback_ty m_callback{ []() {} };

        void Initialize();

    public:
        MessagePopUp(Vector2 pos,
                     Vector2 size,
                     Alignment alignment,
                     std::string const& title,
                     std::string& subTitle,
                     app::AssetType infoTexture,
                     callback_ty callback);

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
    };
} // namespace uil
