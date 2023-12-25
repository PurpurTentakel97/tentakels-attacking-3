//
// Purpur Tentakel
// 15.09.2022
//

#include "Picture.h"
#include "AppContext.h"
#include <iostream>

void Picture::ScaleToFit() {

    if (not m_isScaleToFit) {
        return;
    }

    Resolution_ty_c resolution{ AppContext::GetInstance().GetResolution() };
    float const tempSize{ m_size.x };
    m_size.x = static_cast<float>(m_texture->width) / static_cast<float>(m_texture->height) * resolution.y
               / resolution.x * m_size.y;
    m_pos.x -= (m_size.x - tempSize) / 2;
    UpdateCollider();
}

Picture::Picture(Vector2 pos, Vector2 size, Alignment alignment, AssetType assetType, bool scaleToFit)
    : UIElement{ pos, size, alignment },
      m_isScaleToFit{ scaleToFit } {
    m_texture = AppContext::GetInstance().assetManager.GetTexture(assetType);

    ScaleToFit();
}

void Picture::Render(AppContext_ty_c) {
    DrawTexturePro(
            *m_texture,
            Rectangle(0.0f, 0.0f, static_cast<float>(m_texture->width), static_cast<float>(m_texture->height)),
            m_collider,
            Vector2(0.0f, 0.0f),
            0.0f,
            WHITE
    );
}

void Picture::Resize(AppContext_ty_c appContext) {
    UIElement::Resize(appContext);
    ScaleToFit();
}
