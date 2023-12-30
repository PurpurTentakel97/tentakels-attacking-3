//
// Purpur Tentakel
// 24.08.2022
//

#pragma once

#include "SoundType.hpp"
#include <CustomRaylib.hpp>
#include <array>
#include <event/EventListener.hpp>
#include <string>
#include <unordered_map>
#include <vector>


namespace app {
    class SoundManager final : public eve::EventListener {
    private:
        std::unordered_map<SoundType, Sound> m_sounds;
        std::array<std::string, 5> m_files{
            // clang-format off
        "clicked_accepted_std.mp3",
        "clicked_press_std.mp3",
        "clicked_release_std.mp3",
        "clicked_disabled_std.mp3",
        "hovered_std.mp3",
            // clang-format on
        };

        std::vector<Sound> m_textSounds;

        void LoadSounds();

        void PlaySound(SoundType soundType) const;

        void PlayTextSound() const;

        static void MuteMasterSoundLevel(bool mute);

        static void SetMasterSoundLevel(float level);

        void OnEvent(eve::Event const& event) override;

    public:
        SoundManager();

        ~SoundManager() override;
    };
} // namespace app
