//
// Purpur Tentakel
// 15.09.2022
//

#include "Picture.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>


namespace uil {
    void Picture::ScaleToFit() {

        if (not m_isScaleToFit) {
            return;
        }

        cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
        float const tempSize{ m_size.x };
        m_size.x = static_cast<float>(m_texture->width) / static_cast<float>(m_texture->height) * resolution.y
                   / resolution.x * m_size.y;
        m_pos.x -= (m_size.x - tempSize) / 2;
        UpdateCollider();
    }

    Picture::Picture(
            Vector2 const pos,
            Vector2 const size,
            Alignment const alignment,
            app::AssetType const assetType,
            bool const scaleToFit
    )
        : UIElement{ pos, size, alignment },
          m_isScaleToFit{ scaleToFit } {
        m_texture = app::AppContext::GetInstance().assetManager.GetTexture(assetType);

        ScaleToFit();
    }

    void Picture::Render(app::AppContext_ty_c) {
        DrawTexturePro(
                *m_texture,
                Rectangle(0.0f, 0.0f, static_cast<float>(m_texture->width), static_cast<float>(m_texture->height)),
                m_collider,
                Vector2(0.0f, 0.0f),
                0.0f,
                WHITE
        );
    }

    void Picture::Resize(app::AppContext_ty_c appContext) {
        UIElement::Resize(appContext);
        ScaleToFit();
    }
} // namespace uil
