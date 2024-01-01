//
// Purpur Tentakel
// 31.10.2022
//

#pragma once

#include <alias/AliasUi.hpp>
#include <event/EventListener.hpp>
#include <ui_lib/Scene.hpp>
#include <vector>


namespace ui {
    class NewGameParameterScene final : public uil::Scene, public eve::EventListener {
    private:
        std::shared_ptr<GameEventSettings> m_eventSettings;
        std::vector<std::shared_ptr<SliderAndInputLine>> m_slider;

        void Initialize();

        static void SetValue(utl::usize value, SliderType type);

        void SetRandom() const;

        static void NextScene();

    public:
        NewGameParameterScene();

        ~NewGameParameterScene() override;

        void OnEvent(eve::Event const& event) override;
    };
} // namespace ui
