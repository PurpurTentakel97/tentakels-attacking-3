//
// Purpur Tentakel
// 21.11.2022
//

#pragma once

#include "PopUp.hpp"
#include <functional>


namespace uil {
    class ValidatePopUp : public PopUp {
    private:
        std::function<void(bool)> m_callback{ [](bool) {} };

        void Initialize();

        void Close();

    public:
        ValidatePopUp(
                Vector2 pos,
                Vector2 size,
                      Alignment alignment,
                      std::string const& title,
                std::string& subTitle,
                app::AssetType infoTexture,
                std::function<void(bool)> callback
        );

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
    };
} // namespace ui
