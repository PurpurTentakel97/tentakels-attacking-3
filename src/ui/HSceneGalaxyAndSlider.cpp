//
// Purpur Tentakel
// 09.11.2022
//

#include "HSceneGalaxyAndSlider.hpp"
#include "UIGalaxy.hpp"
#include <alias/AliasCustomRaylib.hpp>
#include <app/AppContext.hpp>
#include <ui_lib/ButtonClassic.hpp>
#include <ui_lib/Line.hpp>
#include <ui_lib/Slider.hpp>

void GalaxyScene::Initialize(bool const isShowGalaxy, bool const isAcceptingInput) {

    // Galaxy
    m_galaxy = std::make_shared<UIGalaxy>(
            1000,
            GetElementPosition(1.0f, 0.0f),
            GetElementSize(0.95f, 0.92f),
            Alignment::TOP_RIGHT,
            isShowGalaxy,
            isAcceptingInput
    );
    m_galaxy->SetOnZoom([this](float scaleFactor, Vector2 referenceScale) { this->Zoom(scaleFactor, referenceScale); });
    m_galaxy->SetOnSlide([this](float position, bool isHorizontal) { this->Slide(position, isHorizontal); });
    m_elements.push_back(m_galaxy);

    // slider
    m_verticalSlider = std::make_shared<Slider>(
            GetElementPosition(0.00f, 0.46f),
            GetElementSize(0.03f, 0.5f),
            Alignment::MID_LEFT,
            false,
            m_galaxy->GetScaleFactor()
    );
    m_verticalSlider->SetOnSlide([this](float position) { this->m_galaxy->Slide(position, false); });
    m_verticalSlider->SetScrolling(true);

    m_horizontalSlider = std::make_shared<Slider>(
            GetElementPosition(0.5175f, 1.0f),
            GetElementSize(0.5f, 0.05f),
            Alignment::BOTTOM_MID,
            true,
            m_galaxy->GetScaleFactor()
    );
    m_horizontalSlider->SetOnSlide([this](float position) { this->m_galaxy->Slide(position, true); });
    m_horizontalSlider->SetScrolling(true);

    // btn
    m_zoomInBtn = std::make_shared<ClassicButton>(
            1001,
            GetElementPosition(0.091f, 0.95f),
            GetElementSize(0.05f, 0.05f),
            Alignment::TOP_LEFT,
            "+",
            app::SoundType::CLICKED_RELEASE_STD
    );
    m_zoomInBtn->SetOnPress([this]() { this->m_galaxy->Zoom(true); });
    m_elementsOutUpdates.push_back(m_zoomInBtn);

    m_zoomOutBtn = std::make_shared<ClassicButton>(
            1002,
            GetElementPosition(0.041f, 0.95f),
            GetElementSize(0.05f, 0.05f),
            Alignment::TOP_LEFT,
            "-",
            app::SoundType::CLICKED_RELEASE_STD
    );
    m_zoomOutBtn->SetOnPress([this]() { this->m_galaxy->Zoom(false); });
    m_elementsOutUpdates.push_back(m_zoomOutBtn);

    // scale
    m_scaleLineX =
            std::make_shared<Line>(GetElementPosition(0.041f, 0.94f), GetElementPosition(0.241f, 0.94f), 2.0f, WHITE);

    m_scaleLineY =
            std::make_shared<Line>(GetElementPosition(0.036f, 0.73f), GetElementPosition(0.036f, 0.93f), 2.0f, WHITE);

    m_galaxy->Zoom(false, 0);
}

void GalaxyScene::Zoom(float const scaleFactor, Vector2 const referenceScale) {

    cst::Resolution_ty_c resolution{ app::AppContext::GetInstance().GetResolution() };
    m_verticalSlider->SetAbsoluteDimension(scaleFactor);
    m_horizontalSlider->SetAbsoluteDimension(scaleFactor);

    auto const startX{ m_scaleLineX->GetStart() };
    auto endX{ m_scaleLineX->GetEnd() };
    auto const sizeX{ referenceScale.x / resolution.x };

    endX.x = startX.x + sizeX;
    m_scaleLineX->SetEnd(endX);
    m_scaleLineX->Update();

    auto startY{ m_scaleLineY->GetStart() };
    auto const endY{ m_scaleLineY->GetEnd() };
    auto const sizeY{ referenceScale.y / resolution.y };

    startY.y = endY.y - sizeY;
    m_scaleLineY->SetStart(startY);
    m_scaleLineY->Update();
}

void GalaxyScene::Slide(float const position, bool const isHorizontal) {
    if (isHorizontal) {
        m_horizontalSlider->SetButtonPosition(position);
    } else {
        m_verticalSlider->SetButtonPosition(position);
    }
}

GalaxyScene::GalaxyScene(
        Vector2 const pos,
        Vector2 const size,
        Alignment const alignment,
        bool const isShowGalaxy,
        bool const isAcceptingInput
)
    : Scene{ pos, size, alignment } {

    Initialize(isShowGalaxy, isAcceptingInput);
}

void GalaxyScene::SetIsScaling(bool const isScaling) {
    m_galaxy->SetIsScaling(isScaling);
}

bool GalaxyScene::IsScaling() const {
    return m_galaxy->IsScaling();
}

void GalaxyScene::SetIsEnabled(bool const isEnabled) {
    m_isEnabled = isEnabled;
    m_galaxy->SetEnabled(isEnabled);
    m_zoomInBtn->SetEnabled(isEnabled);
    m_zoomOutBtn->SetEnabled(isEnabled);
}

bool GalaxyScene::IsEnabled() const {
    return m_isEnabled;
}

lgk::Galaxy_ty_raw GalaxyScene::GetGalaxy() const {
    return m_galaxy->GetGalaxy();
}

void GalaxyScene::FilterByCurrentPlayer(app::PlayerData const& player) {
    m_galaxy->FilterByCurrentPlayer(player);
}

void GalaxyScene::CheckAndUpdate(Vector2 const& mousePosition, app::AppContext_ty_c appContext) {
    if (!IsActive()) {
        return;
    }

    Scene::CheckAndUpdate(mousePosition, appContext);

    if (IsScaling()) {
        m_zoomInBtn->CheckAndUpdate(mousePosition, appContext);
        m_zoomOutBtn->CheckAndUpdate(mousePosition, appContext);
    }

    if (m_galaxy->GetScaleFactor() > 1.0f) {
        m_horizontalSlider->CheckAndUpdate(mousePosition, appContext);
        m_verticalSlider->CheckAndUpdate(mousePosition, appContext);
    }
}

void GalaxyScene::Render(app::AppContext_ty_c appContext) {
    if (!IsActive()) {
        return;
    }

    Scene::Render(appContext);

    if (m_galaxy->GetScaleFactor() > 1.0f) {
        m_horizontalSlider->Render(appContext);
        m_verticalSlider->Render(appContext);
    }

    if (IsScaling()) {
        m_zoomInBtn->Render(appContext);
        m_zoomOutBtn->Render(appContext);
        m_scaleLineX->Render(appContext);
        m_scaleLineY->Render(appContext);
    }
}

void GalaxyScene::Resize(app::AppContext_ty_c appContext) {

    Scene::Resize(appContext);

    m_verticalSlider->Resize(appContext);
    m_horizontalSlider->Resize(appContext);
    m_zoomInBtn->Resize(appContext);
    m_zoomOutBtn->Resize(appContext);
    m_scaleLineX->Resize(appContext);
    m_scaleLineY->Resize(appContext);
}
