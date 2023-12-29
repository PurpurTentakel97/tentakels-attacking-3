//
// Purpur Tentakel
// 10.09.2022
//

#pragma once

#include "UIElement.hpp"
#include <memory>
#include <vector>


class PopUp : public UIElement {
protected:
    bool m_firstEnter{ false };
    bool m_shouldClose{ false };
    std::vector<std::shared_ptr<UIElement>> m_elements;

    void Initialize(std::string const& title, std::string& subTitle, app::AssetType infoTexture);

    void LateUpdate();

    Rectangle GetColliderWithMaxValues(Texture2D* texture, float maxWidth, float maxHeight) const;

public:
    PopUp(Vector2 pos,
          Vector2 size,
          Alignment alignment,
          std::string const& title,
          std::string& subTitle,
          app::AssetType infoTexture);

    void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;
};
