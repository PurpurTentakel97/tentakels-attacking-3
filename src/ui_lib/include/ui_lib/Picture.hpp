//
// Purpur Tentakel
// 15.09.2022
//

#pragma once
#include "UIElement.hpp"

enum class AssetType;


class Picture final : public UIElement {
private:
    Texture2D* m_texture{ nullptr };
    bool m_isScaleToFit{ true };

    void ScaleToFit();

public:
    Picture(Vector2 pos, Vector2 size, Alignment alignment, AssetType assetType, bool scaleToFit = true);

    void Render(app::AppContext_ty_c appContext) override;

    void Resize(app::AppContext_ty_c appContext) override;
};
