//
// Purpur Tentakel
// 20.11.2022
//

#pragma once

#include <event/EventListener.hpp>
#include <memory>
#include <ui_lib/Scene.hpp>

class GalaxyScene;
class SendGalaxyPointerEvent;


class ValidateGalaxyScene : public Scene {
private:
    std::shared_ptr<GalaxyScene> m_galaxy;

    void Initialize();

    void InitializePlayerLegend();

    void InitializeGalaxy();

    void NewGalaxy();

public:
    ValidateGalaxyScene();
};
