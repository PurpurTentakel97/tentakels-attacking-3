//
// Purpur Tentakel
// 20.11.2022
//

#pragma once

#include <alias/AliasEvent.hpp>
#include <alias/AliasUi.hpp>
#include <event/EventListener.hpp>
#include <memory>
#include <ui_lib/Scene.hpp>


class ValidateGalaxyScene : public uil::Scene {
private:
    std::shared_ptr<GalaxyScene> m_galaxy;

    void Initialize();

    void InitializePlayerLegend();

    void InitializeGalaxy();

    void NewGalaxy();

public:
    ValidateGalaxyScene();
};
