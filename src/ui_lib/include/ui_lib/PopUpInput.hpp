//
// Purpur Tentakel
// 03.10.2022
//

#pragma once

#include "ButtonClassic.hpp"
#include "PopUp.hpp"


namespace uil {
    class PopUpInput : public PopUp {
    protected:
        bool m_shouldClose{ false };

        virtual void Initialize();

        [[nodiscard]] ClassicButton_ty InitializeAcceptButton();

        void SetShouldClose();

        virtual void SetValue() = 0;

        void CheckEnter();

        void Close(app::AppContext_ty_c appContext);

    public:
        PopUpInput(Vector2 pos,
                Vector2 size,
                   Alignment alignment,
                   std::string const& title,
                app::AssetType infoTexture
        );

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;
    };
} // namespace uil
