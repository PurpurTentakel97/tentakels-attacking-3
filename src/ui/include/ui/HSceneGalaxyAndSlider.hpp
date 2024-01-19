//
// Purpur Tentakel
// 09.11.2022
//

#pragma once

#include <alias/AliasUi.hpp>
#include <ui_lib/Scene.hpp>
#include <vector>


namespace ui {
    class GalaxyScene final : public uil::Scene {
    private:
        bool m_isEnabled = true;
        uil::Line_ty m_scaleLineX;
        uil::Line_ty m_scaleLineY;
        uil::Slider_ty m_verticalSlider;
        uil::Slider_ty m_horizontalSlider;
        uil::ClassicButton_ty m_zoomInBtn;
        uil::ClassicButton_ty m_zoomOutBtn;
        UIGalaxy_ty m_galaxy;


        void Initialize(bool isShowGalaxy, bool isAcceptingInput);

        void Zoom(float scaleFactor, Vector2 referenceScale);

        void Slide(float position, bool isHorizontal);

    public:
        GalaxyScene(
                Vector2 pos,
                Vector2 size,
                uil::Alignment alignment,
                bool isShowGalaxy,
                bool isAcceptingInput = false
        );

        void SetIsScaling(bool isScaling);

        [[nodiscard]] bool IsScaling() const;

        void SetIsEnabled(bool isEnabled);

        [[nodiscard]] bool IsEnabled() const;

        [[nodiscard]] utl::RepresentationGalaxy GetGalaxy() const;

        void FilterByCurrentPlayer(app::PlayerData const& player);

        void CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) override;

        void Render(app::AppContext_ty_c appContext) override;

        void Resize(app::AppContext_ty_c appContext) override;
    };
} // namespace ui
